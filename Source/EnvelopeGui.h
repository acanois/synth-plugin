/*
  ==============================================================================

    EnvelopeGui.h
    Created: 28 Jan 2020 3:21:37pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class EnvelopeGui : public Component,
                    Slider::Listener
{
public:
    void resized() override;
    void paint (Graphics& g) override;
    void sliderValueChanged (Slider* slider) override;
    void initControls();
    
private:
    OwnedArray<Slider> mEnvControls;
};
