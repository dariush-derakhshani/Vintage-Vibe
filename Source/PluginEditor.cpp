// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginEditor.h"

//==============================================================================
MyAudioProcessorEditor::MyAudioProcessorEditor (MyAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Add the detune slider to the editor
    addAndMakeVisible (detuneSlider);
    detuneSlider.setRange (-12.0f, 12.0f);
    detuneSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 20);
    detuneSlider.addListener (this);

    // Set the size of the editor
    setSize (400, 300);
}

MyAudioProcessorEditor::~MyAudioProcessorEditor()
{
}

void MyAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    // Draw the title of the editor
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawText ("Vintage Vibe", getLocalBounds(),
                juce::Justification::centred, true);
}

void MyAudioProcessorEditor::resized()
{
    // Set the position and size of the detune slider
    detuneSlider.setBounds (getWidth() / 2 - 100, getHeight() / 2 - 50,
                            200, 100);
}

void MyAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    // Update the detune amount based on the value of the detune slider
    if (slider == &detuneSlider)
    {
        processor.setDetuneAmount(slider->getValue());
    }
}
