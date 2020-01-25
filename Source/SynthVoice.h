/*
  ==============================================================================

    SynthVoice.h
    Created: 9 Jan 2020 6:13:40pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthVoice  : public SynthesiserVoice
{
public:
    SynthVoice()
    {
        initVoice();
        initEnv();
    }
    
    ~SynthVoice() {}
    
    void initVoice()
    {
        mOscillator.initialise ([] (float phase) { return std::sin (phase) * 0.3f; }, mTableSize);
//        mOscillator.initialise ([] (float phase) {
//            auto sum = 0;
//            // Starts at 1 or it trips a jassert
//            for (auto i = 1; i < 10; ++i)
//                // Sinc Function
//                sum += std::sin(((2 * i) - 1) * phase) / (((2 * i) - 1));
//            return ((4.0 / float_Pi) * sum);
//        }, mTableSize);
    }
    
    void initEnv()
    {
        mAdsrParameters.attack  = 0.001f;
        mAdsrParameters.decay   = 0.01f;
        mAdsrParameters.sustain = 0.5f;
        mAdsrParameters.release = 1.f;
        mAdsr.setParameters (mAdsrParameters);
    }
    
    void setEnvParameters (float* attack, float* decay, float* sustain, float* release)
    {
        mAdsrParameters.attack  = *attack;
        mAdsrParameters.decay   = *decay;
        mAdsrParameters.sustain = *sustain;
        mAdsrParameters.release = *release;
        mAdsr.setParameters (mAdsrParameters);
    }
    
    bool canPlaySound (SynthesiserSound* synthSound) override
    {
         return dynamic_cast<SynthSound*>(synthSound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override
    {
        mFreq = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        mVel = velocity;
        mOscillator.setFrequency (mFreq);
        mAdsr.noteOn();
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        mAdsr.noteOff();
        allowTailOff = true;
        if (velocity == 0) clearCurrentNote();
    }
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
        mOscillator.setFrequency (mFreq);
        
        auto block = mTempBlock.getSubBlock (0, numSamples);
        block.clear();
        
        if (mAdsr.isActive())
        {
            juce::dsp::ProcessContextReplacing<float> context (block);
            mOscillator.process (context);
            juce::dsp::AudioBlock<float> (outputBuffer)
                .getSubBlock (startSample, numSamples)
                .clear()
                .add (mTempBlock);
            
            mAdsr.applyEnvelopeToBuffer (outputBuffer, startSample, numSamples);
        }
        else
        {
            clearCurrentNote();
            mAdsr.reset();
        }
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override {}
    void controllerMoved (int controllerNumber, int newControllerValue) override {}
    
    //==============================================================================
    void prepare (juce::dsp::ProcessSpec& spec)
    {
        mTempBlock = juce::dsp::AudioBlock<float> (mHeapBlock, spec.numChannels, spec.maximumBlockSize);
        mOscillator.prepare (spec);
    }
    
    void reset()
    {
        mOscillator.reset();
    }
    
private:
    juce::HeapBlock<char> mHeapBlock;
    
    juce::dsp::Oscillator<float> mOscillator;
    juce::dsp::AudioBlock<float> mTempBlock;
    
    ADSR mAdsr;
    ADSR::Parameters mAdsrParameters;
    
    static constexpr uint8_t mTableSize { 1 << 7 };
    float mFreq { 440.f };
    float mVel  { 0.f   };
    double mSampleRate { 44100 };
};
