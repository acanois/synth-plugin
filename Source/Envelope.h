/*
  ==============================================================================

    Envelope.h
    Created: 26 Jan 2020 9:12:55pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Envelope
{
public:
    Envelope()
    {
        mAdsrParameters.attack  = 0.01f;
        mAdsrParameters.decay   = 0.1f;
        mAdsrParameters.sustain = 0.5f;
        mAdsrParameters.release = 0.5f;
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
    
    void reset()   { mAdsr.reset();   }
    void noteOn()  { mAdsr.noteOn();  }
    void noteOff() { mAdsr.noteOff(); }
    
private:
    ADSR mAdsr;
    ADSR::Parameters mAdsrParameters;
};
