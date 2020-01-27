/*
  ==============================================================================

    OpOscillator.h
    Created: 26 Jan 2020 9:12:38pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

template <typename Type>
class OpOscillator
{
public:
    OpOscillator()
    {
        initOscillator();
    }
    
    ~OpOscillator() {}
    
    void initOscillator()
    {
        mOscillator.initialise([] (Type phase) {
            return std::sin (phase);
        }, mTableSize);
    }
    
    void prepare (juce::dsp::ProcessSpec& spec)
    {
        auto tempBlock = juce::dsp::AudioBlock<Type> (mHeapBlock, spec.numChannels, spec.maximumBlockSize);
        mOscillator.prepare (spec);
    }
    
    void reset()
    {
        mOscillator.reset();
    }
    
    void setFrequency (float frequency)
    {
        mOscillator.setFrequency (frequency);
    }
    
    void process(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
        setFrequency (mFrequency);
        
        auto block = mHeapBlock.getSubBlock (0, numSamples);
        block.clear();
        
        juce::dsp::ProcessContextReplacing<float> context (block);
        mOscillator.process (context);
        juce::dsp::AudioBlock<float> (outputBuffer)
            .getSubBlock (startSample, numSamples)
            .clear()
            .add (mHeapBlock);
    }
    
private:
    juce::HeapBlock<Type> mHeapBlock;
    juce::dsp::Oscillator<Type> mOscillator;
    
    Type mFrequency { 440.f };
    
    static constexpr uint8_t mTableSize { 1 << 7 };
};
