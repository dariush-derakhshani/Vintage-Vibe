// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>
#include "BrownianMotion.h"



VintageVibeProcessor::VintageVibeProcessor()
{

}

VintageVibeProcessor::~VintageVibeProcessor()
{
    freqShifts.clear();
}

void VintageVibeProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    const int totalNumInputChannels = getTotalNumInputChannels();

    freqShifts.clear();
    brownianMotions.clear();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        freqShifts.add(new gam::FreqShift<float>(50.0f));
        brownianMotions.add(new BrownianMotion(40.0f, 60.0f, 0.5f, 50.0f));
        gam::FreqShift<float>& freqshift = *freqShifts.getUnchecked(channel);
        freqshift.freq(50.0f / sampleRate);
    }
}

void VintageVibeProcessor::releaseResources()
{
}

int VintageVibeProcessor::getNumPrograms()
{
return 1;
}

int VintageVibeProcessor::getCurrentProgram()
{
return 0;
}

void VintageVibeProcessor::setCurrentProgram(int index)
{
}

const juce::String VintageVibeProcessor::getProgramName(int index)
{
return {};
}

void VintageVibeProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void VintageVibeProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void VintageVibeProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

bool VintageVibeProcessor::acceptsMidi() const
{
    return false;
}

bool VintageVibeProcessor::producesMidi() const
{

    return false;
}

bool VintageVibeProcessor::isMidiEffect() const
{
    return false;
}

double VintageVibeProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

void VintageVibeProcessor::setGain(float amount)
{
    gain = amount;
}

void VintageVibeProcessor::setFrequencyShiftAmount(float amount)
{
    frequencyShiftAmount = amount / getSampleRate();

    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        float brownianMotionValue = brownianMotions[channel]->getNextValue();
        float modulatedFrequencyShiftAmount = frequencyShiftAmount * brownianMotionValue / 50.0f;
        gam::FreqShift<float>& freqshift = *freqShifts.getUnchecked(channel);
        freqshift.freq(modulatedFrequencyShiftAmount);
    }
}



void VintageVibeProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const int totalNumInputChannels = getTotalNumInputChannels();

    jassert(freqShifts.size() == getTotalNumInputChannels());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        gam::FreqShift<float>& freqshift = *freqShifts.getUnchecked(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            const float freqshiftValue = freqshift(channelData[i]);
            channelData[i] = freqshiftValue * gain;
        }
    }
}

juce::AudioProcessorEditor* VintageVibeProcessor::createEditor()
{
    return new VintageVibeEditor (*this);
}

bool VintageVibeProcessor::hasEditor() const
{
    return true;
}

const juce::String VintageVibeProcessor::getName() const
{
    return JucePlugin_Name;
}

// this is where I'm receiving and error:

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{ return new VintageVibeProcessor(); }
