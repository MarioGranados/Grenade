#pragma once

#include <JuceHeader.h>
#include "VoiceManager.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    //====================================mystuff

private:
    //==============================================================================
    // Your private member variables go here...
    double currentSampleRate;
    float phase;
    float amplitude;
    float phaseDelta;
    float frequency;
    float modFrequency;
    float modIndex;
    float modPhase;
    float modPhaseDelta;
    
    VoiceManager manager;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
