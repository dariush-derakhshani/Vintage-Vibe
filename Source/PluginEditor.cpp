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
    gainSlider.setTextValueSuffix("x");
    gainSlider.setNumDecimalPlacesToDisplay(2);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);
    addAndMakeVisible(gainLabel);
    
    frequencyShiftSlider.setRange(-100.0, 100.0);
    frequencyShiftSlider.setValue(0.0);
    frequencyShiftSlider.setTextValueSuffix("Hz");
    frequencyShiftSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(frequencyShiftSlider);
    frequencyShiftSlider.addListener(this);
    
    detuneLabel.setText("Detune", juce::dontSendNotification);
    detuneLabel.attachToComponent(&frequencyShiftSlider, true);
    addAndMakeVisible(detuneLabel);
    
    crackleIntensitySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    crackleIntensitySlider.setRange(0.0, 1.0);
    crackleIntensitySlider.setValue(normalizeCrackleIntensity(0.0));
    crackleIntensitySlider.setNumDecimalPlacesToDisplay(2);
    crackleIntensitySlider.addListener(this);
    addAndMakeVisible(crackleIntensitySlider);

    crackleIntensityLabel.setText("Crackle", juce::dontSendNotification);
    crackleIntensityLabel.attachToComponent(&crackleIntensitySlider, true);
    addAndMakeVisible(crackleIntensityLabel);
}

float VintageVibeEditor::normalizeCrackleIntensity(float value) {
    return value * 1000.0f;
}

float VintageVibeEditor::denormalizeCrackleIntensity(float value) {
    return value / 1000.0f;
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
    crackleIntensitySlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 + 20, 200, 20);

}

void VintageVibeEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.setGain(static_cast<float>(gainSlider.getValue()));
    }
    
    if (slider == &frequencyShiftSlider)
    {
        audioProcessor.setUserDefinedFrequencyShift((float)slider->getValue());
    }
    
    if (slider == &crackleIntensitySlider) {
        float denormalizedValue = denormalizeCrackleIntensity(static_cast<float>(crackleIntensitySlider.getValue()));
        audioProcessor.setCrackleIntensity(denormalizedValue);
    }

}
