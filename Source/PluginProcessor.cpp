#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SampleList.h"

using APVTS = juce::AudioProcessorValueTreeState;

TEK_FACTORYAudioProcessor::TEK_FACTORYAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
#else
    : parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    loadSamples();
}

APVTS::ParameterLayout TEK_FACTORYAudioProcessor::createParameterLayout() {
    APVTS::ParameterLayout p;
    juce::StringArray choices;
    for (const auto& k : embeddedKicks) choices.add(k.name);
    p.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"kick", 1}, "Kick", choices, 0));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"pitch", 1}, "Pitch", juce::NormalisableRange<float>(-24.0f, 24.0f, 0.01f), 0.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"low", 1}, "Low", juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"mid", 1}, "Mid", juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"high", 1}, "High", juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"drive", 1}, "Drive", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 42.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"clip", 1}, "Clip", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 18.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"sub", 1}, "Sub", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 50.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"crush", 1}, "Crush", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 0.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"punch", 1}, "Punch", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 50.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"length", 1}, "Length", juce::NormalisableRange<float>(25.0f, 150.0f, 0.1f), 100.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"output", 1}, "Output", juce::NormalisableRange<float>(-24.0f, 6.0f, 0.1f), -3.0f));
    return p;
}

void TEK_FACTORYAudioProcessor::loadSamples() {
    for (int i = 0; i < embeddedKickCount && i < (int)samples.size(); ++i) {
        juce::MemoryInputStream stream(embeddedKicks[i].data, (size_t)embeddedKicks[i].size, false);
        std::unique_ptr<juce::AudioFormatReader> reader(juce::WavAudioFormat().createReaderFor(&stream, false));
        if (reader) {
            auto length = (int)reader->lengthInSamples;
            samples[(size_t)i].audio.setSize((int)reader->numChannels, length);
            reader->read(&samples[(size_t)i].audio, 0, length, 0, true, true);
        }
    }
}

void TEK_FACTORYAudioProcessor::prepareToPlay(double sampleRate, int) {
    currentSampleRate = sampleRate;
    updateFilters();
    for (auto& channel : filterState) channel.fill(0.0f);
}
void TEK_FACTORYAudioProcessor::releaseResources() {}
bool TEK_FACTORYAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono() || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
void TEK_FACTORYAudioProcessor::updateFilters() {
    const auto low = parameters.getRawParameterValue("low")->load();
    const auto mid = parameters.getRawParameterValue("mid")->load();
    const auto high = parameters.getRawParameterValue("high")->load();
    for (int ch=0; ch<2; ++ch) {
        eqFilters[ch][0].coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(currentSampleRate, 120.0, 0.707, juce::Decibels::decibelsToGain(low));
        eqFilters[ch][1].coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(currentSampleRate, 950.0, 0.8, juce::Decibels::decibelsToGain(mid));
        eqFilters[ch][2].coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(currentSampleRate, 6200.0, 0.707, juce::Decibels::decibelsToGain(high));
    }
}
void TEK_FACTORYAudioProcessor::triggerPreview() {
    activeSample = juce::jlimit(0, 29, (int)parameters.getRawParameterValue("kick")->load());
    playhead = 0.0;
}
void TEK_FACTORYAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) {
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    const int selected = juce::jlimit(0, 29, (int)parameters.getRawParameterValue("kick")->load());
    const float pitch = parameters.getRawParameterValue("pitch")->load();
    const float drive = parameters.getRawParameterValue("drive")->load() / 100.0f;
    const float clip = parameters.getRawParameterValue("clip")->load() / 100.0f;
    const float sub = parameters.getRawParameterValue("sub")->load() / 100.0f;
    const float crush = parameters.getRawParameterValue("crush")->load() / 100.0f;
    const float punch = parameters.getRawParameterValue("punch")->load() / 100.0f;
    const float length = parameters.getRawParameterValue("length")->load() / 100.0f;
    const float outGain = juce::Decibels::decibelsToGain(parameters.getRawParameterValue("output")->load());
    auto& sample = samples[(size_t)selected].audio;
    const double rate = std::pow(2.0, (double)pitch / 12.0) * (44100.0 / currentSampleRate);
    for (const auto metadata : midi) {
        const auto msg = metadata.getMessage();
        if (msg.isNoteOn()) { activeSample = selected; playhead = 0.0; }
        else if (msg.isAllNotesOff() || msg.isAllSoundOff()) playhead = -1.0;
    }
    // Update EQ coefficients from automation; lightweight and stable for a first version.
    static int refreshCounter = 0;
    if ((++refreshCounter % 128) == 0) updateFilters();
    if (playhead < 0.0 || sample.getNumSamples() == 0) return;
    auto& src = samples[(size_t)activeSample].audio;
    if (src.getNumSamples() == 0) return;
    const int n = buffer.getNumSamples();
    const int outCh = buffer.getNumChannels();
    for (int i=0; i<n; ++i) {
        if (playhead >= src.getNumSamples()) { playhead = -1.0; break; }
        const int idx = juce::jlimit(0, src.getNumSamples()-1, (int)playhead);
        const int next = juce::jmin(idx+1, src.getNumSamples()-1);
        const float frac = (float)(playhead - idx);
        float mono = 0.0f;
        for (int sc=0; sc<src.getNumChannels(); ++sc) mono += src.getSample(sc,idx) + (src.getSample(sc,next)-src.getSample(sc,idx))*frac;
        mono /= (float)src.getNumChannels();
        // punch shapes the attack; drive and clip provide the aggressive character.
        const float attack = std::exp(-(float)playhead / (float)currentSampleRate * (8.0f - punch*7.0f));
        mono *= (1.0f + punch*0.75f*attack) * (0.65f + sub*0.7f);
        mono = std::tanh(mono * (1.0f + drive*14.0f));
        if (crush > 0.001f) {
            const float steps = 256.0f - crush*248.0f;
            mono = std::round(mono*steps)/steps;
        }
        if (clip > 0.001f) { const float ceiling = 1.0f - clip*0.72f; mono = juce::jlimit(-ceiling, ceiling, mono) / std::max(0.28f, ceiling); }
        for (int ch=0; ch<outCh; ++ch) {
            float v = mono;
            v = eqFilters[juce::jmin(ch,1)][0].processSample(v);
            v = eqFilters[juce::jmin(ch,1)][1].processSample(v);
            v = eqFilters[juce::jmin(ch,1)][2].processSample(v);
            buffer.setSample(ch, i, v*outGain);
        }
        playhead += rate * length;
    }
}
juce::AudioProcessorEditor* TEK_FACTORYAudioProcessor::createEditor() { return new TEK_FACTORYAudioProcessorEditor(*this); }
void TEK_FACTORYAudioProcessor::getStateInformation(juce::MemoryBlock& dest) { auto state=parameters.copyState(); std::unique_ptr<juce::XmlElement> xml(state.createXml()); copyXmlToBinary(*xml,dest); }
void TEK_FACTORYAudioProcessor::setStateInformation(const void* data, int size) { std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data,size)); if (xml && xml->hasTagName(parameters.state.getType())) parameters.replaceState(juce::ValueTree::fromXml(*xml)); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new TEK_FACTORYAudioProcessor(); }
