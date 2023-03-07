// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>

class MyAudioProcessor  : public juce::AudioProcessor
{
public:
    MyAudioProcessor();
    ~MyAudioProcessor() override;
    
    static juce::AudioProcessor* createPluginFilter();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setDetuneAmount(float amount);
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

private:
    float detuneAmount = 0.0f;
};
