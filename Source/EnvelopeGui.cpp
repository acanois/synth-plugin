/*
  ==============================================================================

    EnvelopeGui.cpp
    Created: 28 Jan 2020 3:21:37pm
    Author:  David Richter

  ==============================================================================
*/

#include "EnvelopeGui.h"

EnvelopeGui::EnvelopeGui (TaveWableAudioProcessor& p)
: processor (p)
{
    sliderBounds.setBounds (0, 100, 100, 100);
    mComponentBounds.setBounds (0, 0, (sliderBounds.getWidth() * 4), (sliderBounds.getHeight()));
    initControls (p);
}

EnvelopeGui::~EnvelopeGui()
{
    
}

void EnvelopeGui::sliderValueChanged (Slider *slider)
{
    
}

void EnvelopeGui::initControls(TaveWableAudioProcessor& p)
{
    std::array<std::string, 4> paramNames = { "attack", "decay", "sustain", "release" };
    
    for (auto paramName : paramNames)
    {
        auto* envControl = new Slider (Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
        auto* envAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTree(), paramName, *envControl);
        mEnvControls.add (envControl);
        mEnvAttachments.add (envAttachment);
        addAndMakeVisible (envControl);
    }
}

void EnvelopeGui::resized()
{
    int xPos = mComponentBounds.getX();
    for (Slider* control : mEnvControls)
    {
        control->setBounds (xPos, mComponentBounds.getY(), sliderBounds.getWidth(), sliderBounds.getHeight());
        xPos += (sliderBounds.getX() + sliderBounds.getWidth() + 10);
    }
}

void EnvelopeGui::paint (Graphics &g)
{
    g.fillAll (Colours::black);
}
