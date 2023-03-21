// MAT240B by Karl Yerkes
// Code by Dariush Derakhshani

#include "PluginProcessor.h"
#include <JuceHeader.h>
#include "PluginEditor.h"

VintageVibeProcessor::VintageVibeProcessor() {}

VintageVibeProcessor::~VintageVibeProcessor() { freqShifts.clear(); }

void VintageVibeProcessor::prepareToPlay(double sampleRate,
                                         int samplesPerBlock) {
  const int totalNumInputChannels = getTotalNumInputChannels();

  freqShifts.clear();

  userDefinedFrequencyShift = 50.0f / sampleRate;

  for (int channel = 0; channel < totalNumInputChannels; ++channel) {
    freqShifts.add(new gam::FreqShift<float>(5.0f));
    gam::FreqShift<float>& freqshift = *freqShifts.getUnchecked(channel);
    freqshift.freq(5.0f / sampleRate);
  }
  onepole[0].freq(5.0f / sampleRate);
  onepole[1].freq(5.0f / sampleRate);
}

void VintageVibeProcessor::releaseResources() {}

int VintageVibeProcessor::getNumPrograms() { return 1; }

int VintageVibeProcessor::getCurrentProgram() { return 0; }

void VintageVibeProcessor::setCurrentProgram(int index) {}

const juce::String VintageVibeProcessor::getProgramName(int index) {
  return {};
}

void VintageVibeProcessor::changeProgramName(int index,
                                             const juce::String& newName) {}

void VintageVibeProcessor::getStateInformation(juce::MemoryBlock& destData) {}

void VintageVibeProcessor::setStateInformation(const void* data,
                                               int sizeInBytes) {}

bool VintageVibeProcessor::acceptsMidi() const { return false; }

bool VintageVibeProcessor::producesMidi() const { return false; }

bool VintageVibeProcessor::isMidiEffect() const { return false; }

double VintageVibeProcessor::getTailLengthSeconds() const { return 0.0; }

void VintageVibeProcessor::setGain(float amount) { gain = amount; }

void VintageVibeProcessor::setUserDefinedFrequencyShift(float amount) {
  userDefinedFrequencyShift = amount;
}

void VintageVibeProcessor::setCrackleIntensity(float intensity) {
    crackleIntensity = intensity;
}

void VintageVibeProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                        juce::MidiBuffer& midiMessages) {
  float modulatedFrequencyShiftAmount[2];
  for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
    float minFactor = 0.5f;
    float maxFactor = 1.5f;
    float randomFactor =
        juce::Random::getSystemRandom().nextFloat() * (maxFactor - minFactor) +
        minFactor;

    float modulatedFrequency = userDefinedFrequencyShift * randomFactor;
    modulatedFrequencyShiftAmount[channel] = modulatedFrequency / getSampleRate();
  }

  const int totalNumInputChannels = getTotalNumInputChannels();

  jassert(freqShifts.size() == getTotalNumInputChannels());

  for (int channel = 0; channel < totalNumInputChannels; ++channel) {
    auto* channelData = buffer.getWritePointer(channel);
    gam::FreqShift<float>& freqshift = *freqShifts.getUnchecked(channel);

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
      freqshift.freq(onepole[channel](modulatedFrequencyShiftAmount[channel]));
      const float freqshiftValue = freqshift(channelData[i]);
      channelData[i] = freqshiftValue * gain;
    }
      if (crackleIntensity > 0.0f) {
          for (int channel = 0; channel < totalNumInputChannels; ++channel) {
              auto* channelData = buffer.getWritePointer(channel);
              for (int i = 0; i < buffer.getNumSamples(); ++i) {
                  if (randomCrackle.nextFloat() < crackleIntensity) {
                      channelData[i] += (randomCrackle.nextFloat() * 2.0f - 1.0f) / 2.0f * gain;
                  }
              }
          }
      }

  }
}

juce::AudioProcessorEditor* VintageVibeProcessor::createEditor() {
  return new VintageVibeEditor(*this);
}

bool VintageVibeProcessor::hasEditor() const { return true; }

const juce::String VintageVibeProcessor::getName() const {
  return JucePlugin_Name;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new VintageVibeProcessor();
}
