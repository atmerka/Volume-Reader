/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VolumeReaderAudioProcessor::VolumeReaderAudioProcessor()
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
    //******************REMEMBER ME!!!**********************
    myFormatManager.registerBasicFormats();
}

VolumeReaderAudioProcessor::~VolumeReaderAudioProcessor()
{
    myFormatReader = nullptr;
}

//==============================================================================
const String VolumeReaderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VolumeReaderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VolumeReaderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VolumeReaderAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VolumeReaderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VolumeReaderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VolumeReaderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VolumeReaderAudioProcessor::setCurrentProgram (int index)
{
}

const String VolumeReaderAudioProcessor::getProgramName (int index)
{
    return {};
}

void VolumeReaderAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VolumeReaderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void VolumeReaderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VolumeReaderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VolumeReaderAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

  
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool VolumeReaderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VolumeReaderAudioProcessor::createEditor()
{
    return new VolumeReaderAudioProcessorEditor (*this);
}

//==============================================================================
void VolumeReaderAudioProcessor::getStateInformation (MemoryBlock& destData)
{
   
}

void VolumeReaderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}

void VolumeReaderAudioProcessor::loadFile(const juce::String &path)
{
    //make file from the string "path"
    auto file = File (path);
    
    
     fName = String(  file.getFileName());
    
    //read it
    myFormatReader = myFormatManager.createReaderFor(file);
    
    //what is the lenght of the in coming file?
    auto sampleLength = static_cast<int>(myFormatReader->lengthInSamples);
    
    //set legnth of my waveform to be the lenght of the incoming file
    myWaveForm.setSize(2, sampleLength);
    
   //my wave form, start sample, cast as an integer the length in samples, start sample, left channel, right channel
    myFormatReader->read(&myWaveForm, 0, sampleLength, 0, true, true);
   
    
    fileLoaded = true;
    
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VolumeReaderAudioProcessor();
}
