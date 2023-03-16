// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VintageVibeEditor : public juce::AudioProcessorEditor, public juce::Timer, public juce::Slider::Listener
{
public:
    VintageVibeEditor(VintageVibeProcessor&);
    ~VintageVibeEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VintageVibeProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::Slider frequencyShiftSlider;
    juce::Label gainLabel;
    juce::Label detuneLabel;
    juce::Label titleLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VintageVibeEditor)
};
