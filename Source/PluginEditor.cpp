// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginProcessor.h"
#include "PluginEditor.h"

MyAudioProcessorEditor::MyAudioProcessorEditor(MyAudioProcessor& p)
: AudioProcessorEditor(&p), processor(p)
{
    setSize(400, 300);
    addAndMakeVisible(&delaySlider);
    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    delaySlider.setRange(0.0, 1.0);
    delaySlider.setValue(1.0);
    delaySlider.onValueChange = [this]
{
    processor.setDetuneAmount((float)delaySlider.getValue());
};
}

MyAudioProcessorEditor::~MyAudioProcessorEditor()
{
}

void MyAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::black);
    g.setFont(15.0f);
    g.drawText("Delay Amount", 0, 0, getWidth(), 30, juce::Justification::centred);
}
void MyAudioProcessorEditor::resized()
{
    delaySlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 - 75, 150, 150);
}
