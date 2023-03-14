// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>


VintageVibeProcessor::VintageVibeProcessor()
{
    const int totalNumInputChannels = getTotalNumInputChannels();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        onePoleFilters.add(new gam::OnePole<float>(50.0f, gam::LOW_PASS, 0.3f));
    }

}

VintageVibeProcessor::~VintageVibeProcessor()
{
    onePoleFilters.clear();
}

void VintageVibeProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    const int totalNumInputChannels = getTotalNumInputChannels();

    onePoleFilters.clear();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        onePoleFilters.add(new gam::OnePole<float>(50.0f, gam::LOW_PASS, 0.3f));
        gam::OnePole<float>& filter = *onePoleFilters.getUnchecked(channel);
        filter.freq(50.0f / sampleRate);
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

void VintageVibeProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const int totalNumInputChannels = getTotalNumInputChannels();

    jassert(onePoleFilters.size() == getTotalNumInputChannels());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        gam::OnePole<float>& filter = *onePoleFilters.getUnchecked(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            const float filteredValue = filter(channelData[i]);
            channelData[i] = filteredValue;
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
