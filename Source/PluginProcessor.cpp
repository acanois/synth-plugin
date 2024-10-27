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
                       ),
#endif
mValueTree (*this, nullptr, "ParameterState", {
    std::make_unique<AudioParameterFloat> (juce::ParameterID {"attack", 1}, "Attack", NormalisableRange<float> (0.01f, 3.0f, 0.001f), mAttack.get()),
    std::make_unique<AudioParameterFloat> (juce::ParameterID {"decay", 1}, "Decay", NormalisableRange<float> (0.01f, 3.0f, 0.001f), mDecay.get()),
    std::make_unique<AudioParameterFloat> (juce::ParameterID {"sustain", 1}, "Sustain", NormalisableRange<float> (0.0f, 1.0f, 0.001f), mSustain.get()),
    std::make_unique<AudioParameterFloat> (juce::ParameterID {"release", 1}, "Release", NormalisableRange<float> (0.01f, 5.0f, 0.001f), mRelease.get())
})
{
    mValueTree.addParameterListener ("attack", this);
    mValueTree.addParameterListener ("decay", this);
    mValueTree.addParameterListener ("sustain", this);
    mValueTree.addParameterListener ("release", this);
    
    mSynth.clearVoices();
    mSynth.clearSounds();
    
    mMonoSound = new SynthSound();
    mMonoVoice = new SynthVoice();
    
    mSynth.addSound (mMonoSound);
    mSynth.addVoice (mMonoVoice);
}

TaveWableAudioProcessor::~TaveWableAudioProcessor()
{
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

void TaveWableAudioProcessor::parameterChanged (const String& parameterID, float newValue)
{
    if (parameterID == "attack")  mAttack.set  (newValue);
    if (parameterID == "decay")   mDecay.set   (newValue);
    if (parameterID == "sustain") mSustain.set (newValue);
    if (parameterID == "release") mRelease.set (newValue);
}

void TaveWableAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    midiMessageCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mMonoVoice->setEnvParameters (mAttack.get(), mDecay.get(), mSustain.get(), mRelease.get());
    
    buffer.clear();
    mSynth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool TaveWableAudioProcessor::hasEditor() const
{
    return true;
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
