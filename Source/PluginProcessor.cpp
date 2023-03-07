// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>


MyAudioProcessor::MyAudioProcessor()
{
}

MyAudioProcessor::~MyAudioProcessor()
{
}

void MyAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void MyAudioProcessor::releaseResources()
{
}

int MyAudioProcessor::getNumPrograms()
{
return 1;
}

int MyAudioProcessor::getCurrentProgram()
{
return 0;
}

void MyAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String MyAudioProcessor::getProgramName(int index)
{
return {};
}

void MyAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void MyAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void MyAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

bool MyAudioProcessor::acceptsMidi() const
{
    return false;
}

bool MyAudioProcessor::producesMidi() const
{

    return false;
}

bool MyAudioProcessor::isMidiEffect() const
{
    return false;
}

double MyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

void MyAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    int numSamples = buffer.getNumSamples();
    float detuneFactor = std::pow(2.0f, detuneAmount / 1200.0f);
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float detunedSampleIndex = sample * detuneFactor;

            int detunedIndexInt = static_cast<int>(detunedSampleIndex);
            float detunedIndexFrac = detunedSampleIndex - static_cast<float>(detunedIndexInt);

            float sample1 = channelData[juce::jlimit(0, numSamples - 1, detunedIndexInt)];
            float sample2 = channelData[juce::jlimit(0, numSamples - 1, detunedIndexInt + 1)];

            float detunedSample = (1.0f - detunedIndexFrac) * sample1 + detunedIndexFrac * sample2;

            channelData[sample] = detunedSample;
        }
    }
}

juce::AudioProcessorEditor* MyAudioProcessor::createEditor()
{
    return new MyAudioProcessorEditor (*this);
}

bool MyAudioProcessor::hasEditor() const
{
    return true;
}

void MyAudioProcessor::setDetuneAmount(float amount)
{
    detuneAmount = amount;
}

const juce::String MyAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

// this is where I'm receiving and error:

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{ return new MyAudioProcessor(); }

