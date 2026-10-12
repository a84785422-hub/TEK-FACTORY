#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class TEK_FACTORYAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    explicit TEK_FACTORYAudioProcessorEditor(TEK_FACTORYAudioProcessor&);
    ~TEK_FACTORYAudioProcessorEditor() override = default;
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    TEK_FACTORYAudioProcessor& processor;
    juce::ComboBox kickBox;
    juce::TextButton previewButton { "▶  FIRE KICK" };
    juce::Label title, subtitle, status;
    std::array<std::unique_ptr<juce::Slider>, 11> knobs;
    std::array<std::unique_ptr<juce::Label>, 11> labels;
    std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>, 11> attachments;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> kickAttachment;
    juce::LookAndFeel_V4 look;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TEK_FACTORYAudioProcessorEditor)
};
