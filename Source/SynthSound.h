/*
  ==============================================================================

    SynthSound.h
    Created: 9 Jan 2020 6:13:55pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound  : public SynthesiserSound
{
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
