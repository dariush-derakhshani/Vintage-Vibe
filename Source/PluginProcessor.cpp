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

void MyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Save sample rate and samples per block for later use
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;

    // Initialize the delay buffer size based on the maximum delay time
    int maxDelayTimeInSamples = (int)(maxDelayTime * sampleRate);
    delayBuffer.setSize(2, maxDelayTimeInSamples);
    delayBuffer.clear();
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

void MyAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    float detuneFactor = std::pow(2.0f, detuneAmount / 1200.0f);
    float delayTime = 1.0f / detuneFactor;
    int delayBufferSize = (int)(delayTime * getSampleRate());

    if (delayBuffer.getNumChannels() != numChannels || delayBuffer.getNumSamples() < delayBufferSize)
    {
        delayBuffer.setSize(numChannels, delayBufferSize, true, true, true);
        delayBuffer.clear();
    }

    int writePos = 0;

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        float* delayBufferData = delayBuffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float currentSample = channelData[sample];

            float delayedSample = delayBufferData[(writePos + delayBufferSize - 1) % delayBufferSize];

            delayBufferData[writePos] = currentSample;

            writePos = (writePos + 1) % delayBufferSize;

            channelData[sample] = currentSample + delayedSample;
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

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{ return new MyAudioProcessor(); }
