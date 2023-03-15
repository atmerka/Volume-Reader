/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VolumeReaderAudioProcessorEditor  : public AudioProcessorEditor, public FileDragAndDropTarget
{
public:
    VolumeReaderAudioProcessorEditor (VolumeReaderAudioProcessor&);
    ~VolumeReaderAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag (const StringArray& files) override;
    
    void filesDropped (const StringArray& files, int x, int y) override;

private:
  
    
    //array to hold values to draw waveform
    std::vector<float> myAudioPoints;
    
    //values to read
    float RMS;
    String RMSText;
    float RMSDB;
    String RMSDBText;
    
    int peakCountL;
    int peakCountR;
    
    float time;
    
    float peakL;
    float peakR;
    String peakTextL;
    String peakTextR;
    
    
    //values for wideness
    float thisL;
    float thisR;
    float diffTotal;
    float diffReal;
    float widenessSumTotal;
    float widenssAvgTotal;
    String widenessTextTotal;
    float widenessSumReal;
    float widenssAvgReal;
    String widenessTextReal;
    
    
    
    
    VolumeReaderAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeReaderAudioProcessorEditor)
};
