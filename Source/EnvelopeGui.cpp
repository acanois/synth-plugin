/*
  ==============================================================================

    EnvelopeGui.cpp
    Created: 28 Jan 2020 3:21:37pm
    Author:  David Richter

  ==============================================================================
*/

#include "EnvelopeGui.h"

void EnvelopeGui::sliderValueChanged (Slider *slider)
{
    
}

void EnvelopeGui::initControls()
{
    for (int i = 0; i < 4; ++i)
    {
        auto* envControl = new Slider (Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
        mEnvControls.add (envControl);
        addAndMakeVisible (envControl);
    }
}

void EnvelopeGui::resized()
{
    Rectangle<int> sliderBounds;
    sliderBounds.setBounds (100, 100, 100, 100);
    int xPos = sliderBounds.getX();
    
    for (Slider* control : mEnvControls)
    {
        control->setBounds (xPos, sliderBounds.getY(), sliderBounds.getWidth(), sliderBounds.getHeight());
        xPos += (sliderBounds.getX() + 10);
    }
}

void EnvelopeGui::paint (Graphics &g)
{
    g.fillAll (Colours::white);
}
