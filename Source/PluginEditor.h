// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MyAudioProcessorEditor : public juce::AudioProcessorEditor,
                               public juce::Slider::Listener
{
public:
    MyAudioProcessorEditor (MyAudioProcessor&);
    ~MyAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged (juce::Slider* slider) override;

private:
    MyAudioProcessor& processor;

    juce::Slider detuneSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyAudioProcessorEditor)
};
