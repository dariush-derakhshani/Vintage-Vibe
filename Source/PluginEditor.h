// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MyAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MyAudioProcessorEditor(MyAudioProcessor&);
    ~MyAudioProcessorEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    MyAudioProcessor& processor;
    juce::Slider delaySlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyAudioProcessorEditor)
};
