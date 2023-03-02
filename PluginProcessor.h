// MAT240B 2023 Final Project
// Instructor: Karl Yerkes
// Inspiration Juan Gil <https://juangil.com/>
// by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>

class VibratoAudioProcessor  : public juce::AudioProcessor
{
public:
    VibratoAudioProcessor();
    ~VibratoAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void beginParameterChange();
    void endParameterChange();

private:
    juce::AudioParameterFloat* rateParam;
    juce::AudioParameterFloat* depthParam;
    juce::AudioParameterFloat* dryWetParam;
    juce::AudioParameterFloat* feedbackParam;

    juce::dsp::Oscillator<float> lfo;
    juce::dsp::Gain<float> gain;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine;

    juce::AudioBuffer<float> delayBuffer;

    juce::CriticalSection parameterLock;

    bool parametersChanged;
};
