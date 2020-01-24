/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TaveWableAudioProcessor::TaveWableAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mSynth.clearVoices();
    mSynth.clearSounds();
    
    mMonoSound = new SynthSound();
    mMonoVoice = new SynthVoice();
    
    mSynth.addSound(mMonoSound);
    mSynth.addVoice(mMonoVoice);
}

TaveWableAudioProcessor::~TaveWableAudioProcessor()
{
    DBG ("Cleaning up");
    if (mMonoVoice != nullptr)
    {
        DBG ("Deleting sounds and voices");
        delete mMonoVoice;
        mMonoVoice = nullptr;
    }
}

//==============================================================================
const String TaveWableAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TaveWableAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TaveWableAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TaveWableAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TaveWableAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TaveWableAudioProcessor::getNumPrograms()
{
    return 1;
}

int TaveWableAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TaveWableAudioProcessor::setCurrentProgram (int index) {}

const String TaveWableAudioProcessor::getProgramName (int index)
{
    return {};
}

void TaveWableAudioProcessor::changeProgramName (int index, const String& newName) {}

//==============================================================================
void TaveWableAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused (samplesPerBlock);
    mSpec.sampleRate = sampleRate;
    mSpec.maximumBlockSize = samplesPerBlock;
    mSpec.numChannels = getTotalNumOutputChannels();
    mSynth.setCurrentPlaybackSampleRate (sampleRate);
    midiMessageCollector.reset (sampleRate);
    mMonoVoice->reset();
    mMonoVoice->prepare (mSpec);
}

void TaveWableAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TaveWableAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TaveWableAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    midiMessageCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    buffer.clear();
    mSynth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool TaveWableAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TaveWableAudioProcessor::createEditor()
{
    return new TaveWableAudioProcessorEditor (*this);
}

//==============================================================================
void TaveWableAudioProcessor::getStateInformation (MemoryBlock& destData) {}
void TaveWableAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TaveWableAudioProcessor();
}
