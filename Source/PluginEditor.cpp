// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginEditor.h"

VintageVibeEditor::VintageVibeEditor(VintageVibeProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 200);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(1.0);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    frequencyShiftSlider.setRange(0.0, 100.0);
    frequencyShiftSlider.setValue(0.0);
    addAndMakeVisible(frequencyShiftSlider);
    frequencyShiftSlider.addListener(this);

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
    frequencyShiftSlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 40, 200, 20);
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
