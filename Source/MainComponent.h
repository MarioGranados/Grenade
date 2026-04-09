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
    
    bool useFM;
    
    VoiceManager manager;
    
    //examples
    
    juce::Slider slider;
    juce::Slider knob;
    //examples end
    
    //=======================main
    juce::Slider attackKnob;
    juce::Slider releaseKnob;
    juce::Slider sustainKnob;
    juce::Slider decayKnob;
    juce::Slider volumeKnob;
    
    juce::Slider modulatorKnob;
    
    juce::ToggleButton useFmButton;

    
    //=======================main ends
    
    //===========FX
    juce::Slider voicesAmountSlider;
    
    juce::Slider reverbDecayKnob;
    juce::Slider reverbMixKnob;
    juce::ToggleButton reverbButton;
    
    juce::Slider distortionKnob;
    juce::ToggleButton distButton;
    
    juce::Slider chorusKnob;
    juce::ToggleButton chorusButton; // enables fx;
    
    juce::ToggleButton pluckedButton;
    //===============Fx end
    
    //========================second oscilator
    
    juce::ComboBox dropdown;
    
    
    //=====functions
    void handleKnobChange(float value);
    void handleVolumeChange(float value);
    
    //====voices
    void handleVoicesAmount(float value);
    
    float getAmplitude();
    void setAmplitude(float amplitude);
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
