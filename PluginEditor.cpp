// MAT240B 2023 Final Project
// Instructor: Karl Yerkes
// Inspiration Juan Gil <https://juangil.com/>
// by Dariush Derakhshani

#include "PluginEditor.h"

VibratoAudioProcessorEditor::VibratoAudioProcessorEditor (VibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    rateSlider.setSliderStyle (juce::Slider::Rotary);
    rateSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible (&rateSlider);
    rateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "rate", rateSlider);
    
    depthSlider.setSliderStyle (juce::Slider::Rotary);
    depthSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible (&depthSlider);
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "depth", depthSlider);

    dryWetSlider.setSliderStyle (juce::Slider::Rotary);
    dryWetSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible (&dryWetSlider);
    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "drywet", dryWetSlider);

    feedbackSlider.setSliderStyle (juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible (&feedbackSlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "feedback", feedbackSlider);
}
VibratoAudioProcessorEditor::~VibratoAudioProcessorEditor()
{
}

void VibratoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawText ("Vibrato", getLocalBounds(), juce::Justification::centred, true);
}

void VibratoAudioProcessorEditor::resized()
{
    const auto padding = 10;
    const auto sliderWidth = (getWidth() - 3 * padding) / 2;
    const auto sliderHeight = getHeight() / 2;

    rateSlider.setBounds (padding, padding, sliderWidth, sliderHeight);
    depthSlider.setBounds (2 * padding + sliderWidth, padding, sliderWidth, sliderHeight);
    dryWetSlider.setBounds (padding, 2 * padding + sliderHeight, sliderWidth, sliderHeight);
    feedbackSlider.setBounds (2 * padding + sliderWidth, 2 * padding + sliderHeight, sliderWidth, sliderHeight);
}
void VibratoAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &rateSlider)
        processor.setParameterNotifyingHost (VibratoAudioProcessor::rateParam, (float) slider->getValue());
    else if (slider == &depthSlider)
        processor.setParameterNotifyingHost (VibratoAudioProcessor::depthParam, (float) slider->getValue());
    else if (slider == &dryWetSlider)
        processor.setParameterNotifyingHost (VibratoAudioProcessor::dryWetParam, (float) slider->getValue());
    else if (slider == &feedbackSlider)
        processor.setParameterNotifyingHost (VibratoAudioProcessor::feedbackParam, (float) slider->getValue());
}

void VibratoAudioProcessorEditor::timerCallback()
{
    rateSlider.setValue (processor.getParameter (VibratoAudioProcessor::rateParam), juce::dontSendNotification);
    depthSlider.setValue (processor.getParameter (VibratoAudioProcessor::depthParam), juce::dontSendNotification);
    dryWetSlider.setValue (processor.getParameter (VibratoAudioProcessor::dryWetParam), juce::dontSendNotification);
    feedbackSlider.setValue (processor.getParameter (VibratoAudioProcessor::feedbackParam), juce::dontSendNotification);
}
VibratoAudioProcessorEditor::VibratoAudioProcessorEditor (VibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);

    addAndMakeVisible (rateSlider);
    rateSlider.setSliderStyle (juce::Slider::Rotary);
    rateSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 25);
    rateSlider.addListener (this);

    addAndMakeVisible (depthSlider);
    depthSlider.setSliderStyle (juce::Slider::Rotary);
    depthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 25);
    depthSlider.addListener (this);

    addAndMakeVisible (dryWetSlider);
    dryWetSlider.setSliderStyle (juce::Slider::Rotary);
    dryWetSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 25);
    dryWetSlider.addListener (this);

    addAndMakeVisible (feedbackSlider);
    feedbackSlider.setSliderStyle (juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 25);
    feedbackSlider.addListener (this);

    startTimerHz (30);
}

void VibratoAudioProcessorEditor::sliderDragStarted (juce::Slider* slider)
{
    processor.beginParameterChange();
}

void VibratoAudioProcessorEditor::sliderDragEnded (juce::Slider* slider)
{
    processor.endParameterChange();
}
