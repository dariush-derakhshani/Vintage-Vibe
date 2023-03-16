// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginEditor.h"

VintageVibeEditor::VintageVibeEditor(VintageVibeProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 200);
    
    titleLabel.setText("Vintage Vibe", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);
    
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(1.0);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);
    addAndMakeVisible(gainLabel);
    
    frequencyShiftSlider.setRange(-100.0, 100.0);
    frequencyShiftSlider.setValue(0.0);
    addAndMakeVisible(frequencyShiftSlider);
    frequencyShiftSlider.addListener(this);
    
    detuneLabel.setText("Detune", juce::dontSendNotification);
    detuneLabel.attachToComponent(&frequencyShiftSlider, true);
    addAndMakeVisible(detuneLabel);
    
    startTimer(10);
}

VintageVibeEditor::~VintageVibeEditor()
{
}

void VintageVibeEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff323e44));
}

void VintageVibeEditor::resized()
{
    gainSlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 10, 200, 20);
    frequencyShiftSlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 40, 200, 20);
    titleLabel.setBounds(0, 10, getWidth(), 40);

}

void VintageVibeEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.setGain(static_cast<float>(gainSlider.getValue()));
    }
    
    if (slider == &frequencyShiftSlider)
    {
        audioProcessor.setFrequencyShiftAmount((float)slider->getValue());
    }
}

void VintageVibeEditor::timerCallback()
{
    float userFrequency = static_cast<float>(frequencyShiftSlider.getValue());

    float minFactor = 0.5f;
    float maxFactor = 1.5f;
    float randomFactor = juce::Random::getSystemRandom().nextFloat() * (maxFactor - minFactor) + minFactor;

    float modulatedFrequency = userFrequency * randomFactor;

    audioProcessor.setFrequencyShiftAmount(modulatedFrequency);
}

