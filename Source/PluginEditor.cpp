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
    
    setSize (480, 360);
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
}
