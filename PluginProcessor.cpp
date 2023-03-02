// MAT240B 2023 Final Project
// Instructor: Karl Yerkes
// Inspiration Juan Gil <https://juangil.com/>
// by Dariush Derakhshani

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoAudioProcessor::VibratoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                      .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                      .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                      )
#endif
{
    // Set default values for parameters
    dryWetParam = 0.5f;
    depthParam = 0.5f;
    rateParam = 1.0f;
    feedbackParam = 0.0f;

    // Create a timer to update the LFO phase
    lfoTimer = new juce::Timer();
    lfoTimer->startTimerHz(50);
    lfoTimer->addTimerListener(this);
}

VibratoAudioProcessor::~VibratoAudioProcessor()
{
    // Stop the LFO timer
    if (lfoTimer != nullptr)
    {
        lfoTimer->stopTimer();
        lfoTimer = nullptr;
    }
}
void VibratoAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Set the sample rate for the LFO
    lfo.setSampleRate(sampleRate);

    // Set the size of the delay buffer
    delayBuffer.setSize(getTotalNumInputChannels(), static_cast<int>(sampleRate * maxDelayTimeSeconds));

    // Clear the delay buffer
    delayBuffer.clear();

    // Initialize the LFO phase to 0
    lfoPhase = 0.0f;

    // Reset the write position of the delay buffer
    writePosition = 0;
}

void VibratoAudioProcessor::releaseResources()
{
    // No-op
}

void VibratoAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer&)
{
    // Get the number of input and output channels
    const int numInputChannels = buffer.getNumChannels();
    const int numOutputChannels = getTotalNumOutputChannels();

    // Get the current parameter values
    const float dryWet = dryWetParam.load();
    const float depth = depthParam.load();
    const float rate = rateParam.load();
    const float feedback = feedbackParam.load();
    // Iterate over each sample in the buffer
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        // Calculate the LFO phase for this sample
        const float lfoPhaseSample = lfoPhase + (rate * lfo.getSample());

        // Wrap the LFO phase to the range [0, 1)
        const float wrappedLfoPhase = std::fmodf(lfoPhaseSample, 1.0f);

        // Calculate the depth for this sample
        const float depthSample = depth * lfo.getSample();

        // Iterate over each channel in the buffer
        for (int channel = 0; channel < numInputChannels; ++channel)
        {
            // Get a pointer to the input and output buffers for this channel
            const float* inputBuffer = buffer.getReadPointer(channel);
            float* outputBuffer = buffer.getWritePointer(channel);

            // Get a pointer to the delay buffer for this channel
            float* delayBufferChannel = delayBuffer.getWritePointer(channel);

            // Calculate the delayed sample for this channel
            const int delaySamples = static_cast<int>(depthSample * maxDelayTimeSeconds * getSampleRate());
            const int readPosition = (writePosition - delaySamples + maxDelayTimeSamples) % maxDelayTimeSamples;
            const float delayedSample = delayBufferChannel[readPosition];

            // Calculate the output sample for this channel
            const float inputSample = inputBuffer[sample];
            const float outputSample = dryWet * inputSample + (1.0f - dryWet) * delayedSample;

            // Write the output sample to the output buffer and the delay buffer
            outputBuffer[sample] = outputSample;
            delayBufferChannel[writePosition] = inputSample + feedback * delayedSample;
        }
        // Update the LFO phase for the next sample
        lfoPhase = wrappedLfoPhase;

        // Increment the write position of the delay buffer
        writePosition = (writePosition + 1) % maxDelayTimeSamples;
    }
}

bool VibratoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Only allow mono or stereo input and output
    const AudioChannelSet& inputChannelSet = layouts.getChannelSet(true, 0);
    const AudioChannelSet& outputChannelSet = layouts.getChannelSet(false, 0);

    if (inputChannelSet != AudioChannelSet::mono() && inputChannelSet != AudioChannelSet::stereo())
        return false;

    if (outputChannelSet != AudioChannelSet::mono() && outputChannelSet != AudioChannelSet::stereo())
        return false;

    return true;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratoAudioProcessor();
}
