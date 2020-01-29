/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TaveWableAudioProcessorEditor::TaveWableAudioProcessorEditor (TaveWableAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible (mKeyboardComponent);
    mKeyboardComponent.setMidiChannel (2);
    mKeyboardState.addListener (&processor.getMidiMessageCollector());
    
    for (int i = 0; i < 4; ++i)
    {
        auto* envControl = new Slider (Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
        mEnvControls.add (envControl);
        addAndMakeVisible (envControl);
    }
    
    setSize (720, 550);
}

TaveWableAudioProcessorEditor::~TaveWableAudioProcessorEditor()
{
    mKeyboardState.removeListener (&processor.getMidiMessageCollector());
}

//==============================================================================
void TaveWableAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void TaveWableAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    
    Rectangle<int> componentBounds;
    componentBounds.setBounds (100, 100, 100, 100);
    mKeyboardComponent.setBounds (area.removeFromBottom (80).reduced (8));
    
    Rectangle<int> sliderBounds;
    sliderBounds.setBounds (100, 100, 100, 100);
    int xPos = sliderBounds.getX();
    
    for (Slider* control : mEnvControls)
    {
        control->setBounds (xPos, sliderBounds.getY(), sliderBounds.getWidth(), sliderBounds.getHeight());
        xPos += (sliderBounds.getX() + 10);
    }
    
}
