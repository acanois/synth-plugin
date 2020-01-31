/*
  ==============================================================================

    EnvelopeGui.h
    Created: 28 Jan 2020 3:21:37pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class EnvelopeGui : public Component,
                    Slider::Listener
{
public:
    EnvelopeGui (TaveWableAudioProcessor& p);
    ~EnvelopeGui();
    
    void resized() override;
    void paint (Graphics& g) override;
    void sliderValueChanged (Slider* slider) override;
    void initControls();
    
    int getComponentHeight() { return mComponentBounds.getHeight(); }
    
private:
    OwnedArray<Slider> mEnvControls;
    Rectangle<int> mComponentBounds;
    Rectangle<int> sliderBounds;
    
    TaveWableAudioProcessor& processor;
};
