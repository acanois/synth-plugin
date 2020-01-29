/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "EnvelopeGui.h"

//==============================================================================
/**
*/
class TaveWableAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TaveWableAudioProcessorEditor (TaveWableAudioProcessor&);
    ~TaveWableAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    TaveWableAudioProcessor& processor;
    
    MidiKeyboardState mKeyboardState;
    MidiKeyboardComponent mKeyboardComponent
    {
        mKeyboardState,
        MidiKeyboardComponent::horizontalKeyboard
    };
    
    OwnedArray<Slider> mEnvControls;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TaveWableAudioProcessorEditor)
};
