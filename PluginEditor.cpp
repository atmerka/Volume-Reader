/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VolumeReaderAudioProcessorEditor::VolumeReaderAudioProcessorEditor (VolumeReaderAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
}

VolumeReaderAudioProcessorEditor::~VolumeReaderAudioProcessorEditor()
{
}

//==============================================================================
void VolumeReaderAudioProcessorEditor::paint (Graphics& g)
{
    //background
    g.fillAll (Colours::darkgrey.withAlpha(0.7f));
    
    //layout for header
    g.setColour(Colours::black);
    g.fillRect(0, 0, getWidth(), 0.1*getHeight());
    
    g.setColour(Colours::lightgrey.withAlpha(0.5f));
    g.fillRect(5, 5, getWidth()-10, 0.1*getHeight()-10);
    
    g.setColour(Colours::black);
    g.setFont(20.0f);
    g.drawText("VOLUME READER", 0, 0, getWidth(), 0.1*getHeight(), Justification::centred);
    
    
    
    //FILE NAME
    g.setFont(14.0f);
    
    //drawing file name
    g.setColour(Colours::orange);
    g.drawText(processor.fName, 0, 0.9*getHeight(), getWidth(), 10, Justification::centred);
    
    
    
    
    //DRAWING VALUES
    g.setColour(Colours::lightblue.withAlpha(0.7f));
    
    if(processor.fileLoaded)
    {
        //new file dropped
        //get waveform from processor
        auto waveform = processor.getWaveForm();
        
        //figure out why these are representing at 3db lower than other meters
        //in the mean time return all RMS values as there value +3
        //do this for volume meter as well
        
        
        //############################ DOING RMS VALUES #################################################
        float h = 4;
        
        //LEFT CHANNEL
        //gets RMS between 0 and 1
         RMS = waveform.getRMSLevel(0, 0, waveform.getNumSamples());
        
        RMS = std::ceil(RMS*100)/100;
        
        //get RMS as a DB
         RMSDB  = Decibels::gainToDecibels(RMS,-96.0f);
        //because all other meteres represent this way
        RMSDB = RMSDB+3;
        RMSDB = std::ceil(RMSDB*100)/100;
        
        
        g.setColour(Colours::turquoise.withAlpha(0.5f));
        
        //print out the RMS level
         RMSText = (String)RMS;
        g.drawText("RMS L (0-1):", getWidth()/10, 0, getWidth()*0.5, getHeight()*0.1*(h+1), Justification::centredLeft);
        g.drawText(RMSText, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+1), Justification::centredLeft );

        
        g.setColour(Colours::gold.withAlpha(0.5f));
        
        //print out the RMS DB level
         RMSDBText = (String)RMSDB;
        g.drawText("RMS L (DB):", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+3), Justification::centredLeft);
        g.drawText(RMSDBText, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+3), Justification::centredLeft);
        
        //RIGHT CHANNEL
        //gets RMS between 0 and 1
         RMS = waveform.getRMSLevel(1, 0, waveform.getNumSamples());
        
        RMS = std::ceil(RMS*100)/100;
       
        //get RMS as a DB
         RMSDB  = Decibels::gainToDecibels(RMS,-96.0f);
        //because idfk why all other meters represent this way
        RMSDB = RMSDB+3;
        RMSDB = std::ceil(RMSDB*100)/100;
        
        
        g.setColour(Colours::turquoise.withAlpha(0.5f));
        
        //print out the RMS level
         RMSText = (String)RMS;
        g.drawText("RMS R (0-1):", getWidth()/10, 0, getWidth()*0.5, getHeight()*0.1*(h+2), Justification::centredLeft);
        g.drawText(RMSText, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+2), Justification::centredLeft);
        
        g.setColour(Colours::gold.withAlpha(0.5f));
        
        //print out the RMS DB level
         RMSDBText = (String)RMSDB;
        g.drawText("RMS R (DB):", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+4), Justification::centredLeft);
        g.drawText(RMSDBText, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+4), Justification::centredLeft);
        
        //############################################ DOING PEAK VALUES ##################################################
        peakCountL = 0;
        peakCountR = 0;
        
        
        //get peak of sample for each side
        peakL = waveform.getMagnitude(0, 0, waveform.getNumSamples());
        peakR = waveform.getMagnitude(1, 0, waveform.getNumSamples());
        
        peakL = std::ceil(peakL*100)/100;
        peakR = std::ceil(peakR*100)/100;
        
        g.setColour(Colours::lightgreen.withAlpha(0.5f));
        
        //writing L channel text
        peakTextL = (String)peakL;
        g.drawText("Peaks L (RAW):", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+5), Justification::centredLeft);
        g.drawText(peakTextL, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+5), Justification::centredLeft);
        
        g.setColour(Colours::lightgreen.withAlpha(0.5f));
        
        //writing r channel text
        peakTextR = (String) peakR;
        g.drawText("Peaks R (RAW):", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+6), Justification::centredLeft);
        g.drawText(peakTextR, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+6), Justification::centredLeft);
        
        
        
        //also display in db
        float peakDBR = Decibels::gainToDecibels(peakL, -96.0f);
        float peakDBL = Decibels::gainToDecibels(peakR, -96.0f);
        
        peakDBL = std::ceil(peakDBL*100)/100;
        peakDBR = std::ceil(peakDBR*100)/100;
        
        
        g.setColour(Colours::orangered.withAlpha(0.5f));
        
        //writing L channel text
        peakTextL = (String)peakDBL;
        g.drawText("Peaks L (DB):",getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+7), Justification::centredLeft);
        g.drawText(peakTextL, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+7), Justification::centredLeft);
        
        g.setColour(Colours::orangered.withAlpha(0.5f));
        //writing r channel text
        peakTextR = (String) peakDBR;
        g.drawText("Peaks R (DB):", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+8), Justification::centredLeft);
        g.drawText(peakTextR, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+8), Justification::centredLeft);
        
  
    //############################################ GETTING WIDENESS #######################################################
           
           widenessSumTotal = 0;
           widenessSumReal = 0;
           
           for ( int i  = 0 ; i < waveform.getNumSamples();i++)
           {
               thisL = waveform.getSample(0, i);
               thisR = waveform.getSample(1, i);
           
               
               diffTotal = thisR-thisL;
               diffTotal = std::pow(diffTotal, 2);
               diffTotal = std::sqrt(diffTotal);
               widenessSumTotal = widenessSumTotal + diffTotal;
               
               
               
               diffReal = thisR-thisL;
               diffReal = std::pow(diffReal, 2);
               diffReal = std::sqrt(diffReal);
               if(diffReal>0.15)
               {
                   diffReal = 0.15;
               }
               widenessSumReal = widenessSumReal + diffReal;
               
           }
           widenssAvgReal = widenessSumReal/waveform.getNumSamples()*100;
           
           widenssAvgTotal = widenessSumTotal/waveform.getNumSamples()*100;
        
        widenssAvgReal = std::ceil(widenssAvgReal*100)/100;
        widenssAvgTotal = std::ceil(widenssAvgTotal*100)/100;
        
           g.setColour(Colours::lightcyan.withAlpha(0.5f));
        
           //writing wideness
           widenessTextTotal = (String) widenssAvgTotal;
           g.drawText("WidenesssTotal:", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+9), Justification::centredLeft);
           g.drawText(widenessTextTotal, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+9), Justification::centredLeft);
          
           //writing wideness
           widenessTextReal = (String) widenssAvgReal;
           g.drawText("WidenesssReal:", getWidth()/10, 0, getWidth()*0.5 , getHeight()*0.1*(h+10), Justification::centredLeft);
           g.drawText(widenessTextReal, getWidth()*0.5, 0, getWidth()*0.9, getHeight()*0.1*(h+10), Justification::centredLeft);
       }
    
}



void VolumeReaderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
bool VolumeReaderAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray &files)
{
    //for the files in the file array passed
    for(auto file: files)
    {
        //if it is of these formats
        if(file.contains(".wav" )|| file.contains (".mp3")||file.contains(".aif"))
        {
            //we can load it
            return true;
        }
    }
    return false;
}

void VolumeReaderAudioProcessorEditor::filesDropped(const StringArray& files, int x, int y)
{
    //for the files in the array
    for(auto file: files)
    {
        //if it is audio (from function above)
        if(isInterestedInFileDrag(file))
        {
            //call the draw function
            //shouldBePainting = true;
            //load the file
            processor.loadFile(file);
        }
    }
    repaint();
}
