// MAT240B 2023 Final Project
// Instructor: Karl Yerkes
// Inspiration Juan Gil <https://juangil.com/>
// by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VibratoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VibratoAudioProcessorEditor (VibratoAudioProcessor&);
    ~VibratoAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    VibratoAudioProcessor& audioProcessor;

    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider dryWetSlider;
    juce::Slider feedbackSlider;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> rateAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoAudioProcessorEditor)
};

