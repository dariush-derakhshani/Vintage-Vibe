// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#pragma once

#include <JuceHeader.h>
#include <Gamma/Effects.h>

using namespace gam;

class VintageVibeProcessor  : public juce::AudioProcessor
{
public:
    VintageVibeProcessor();
    ~VintageVibeProcessor() override;
    
    static juce::AudioProcessor* createPluginFilter();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    
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
    
    void setGain(float amount);
    void setFrequencyShiftAmount(float amount);
    void setUserDefinedFrequencyShift(float amount);
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    const juce::String getName() const override;
    
private:
    juce::OwnedArray<gam::FreqShift<>> freqShifts;
    gam::OnePole<> onepole[2];
    float gain = 1.0f;
    float frequencyShiftAmount = 0.0f;
    float userDefinedFrequencyShift = 0.0f;
    void randomFrequencyShift();
};
