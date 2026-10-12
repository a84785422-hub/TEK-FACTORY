#pragma once
#include <JuceHeader.h>
#include <array>

class TEK_FACTORYAudioProcessor : public juce::AudioProcessor {
public:
    TEK_FACTORYAudioProcessor();
    ~TEK_FACTORYAudioProcessor() override = default;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 3.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;
    juce::AudioProcessorValueTreeState parameters;
    void triggerPreview();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
private:
    struct Sample { juce::AudioBuffer<float> audio; };
    std::array<Sample, 30> samples;
    int activeSample = 0;
    double playhead = -1.0;
    double playbackRate = 1.0;
    double currentSampleRate = 44100.0;
    std::array<std::array<float, 3>, 2> filterState{};
    juce::dsp::IIR::Filter<float> eqFilters[2][3];
    void loadSamples();
    void updateFilters();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TEK_FACTORYAudioProcessor)
};
