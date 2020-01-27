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
    
    void process (juce::dsp::ProcessContextReplacing<float>& context)
    {
        mOscillator.process (context);
    }
    
private:
    juce::dsp::Oscillator<Type> mOscillator;
    static constexpr uint8_t mTableSize { 1 << 7 };
};
