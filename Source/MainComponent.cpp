#include "MainComponent.h"
#include "VoiceManager.h"
//==============================================================================
MainComponent::MainComponent():currentSampleRate(44100.0),
phase(0.0f),
amplitude(0.2f),
phaseDelta(0.0f),
frequency(440.0f),
modFrequency(220.0f),
modIndex(50.0f),
modPhase(0.0f),
modPhaseDelta(0.0f)
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    phaseDelta = (2.0f * juce::MathConstants<float>::pi * frequency) / currentSampleRate;
    modPhaseDelta = (2.0f * juce::MathConstants<float>::pi * modFrequency) / currentSampleRate;

    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
    

//    for (auto chan = 0; chan < bufferToFill.buffer->getNumChannels(); chan++)
//    {
//        auto* channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);
//
//        for (int i = 0; i < bufferToFill.numSamples; ++i)
//        {
//            float modulator = std::sin(modPhase);
//
//            // FM happens here ↓
//            float sample = std::sin(phase + modIndex * modulator);
//
//            channelData[i] = amplitude * sample;
//
//            // increment phases
//            phase += phaseDelta;
//            modPhase += modPhaseDelta;
//
//            // wrap both
//            if (phase >= juce::MathConstants<float>::twoPi)
//                phase -= juce::MathConstants<float>::twoPi;
//
//            if (modPhase >= juce::MathConstants<float>::twoPi)
//                modPhase -= juce::MathConstants<float>::twoPi;
//        }
//    }
    VoiceManager manager;
    manager.setNumVoices(12);
    std::vector<Voice>& voices = manager.getVoices();
    
    for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan)
    {
        auto* channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);

        for (int i = 0; i < bufferToFill.numSamples; ++i)
        {
            float outputSample = 0.0f;

            // loop through all voices
            for (Voice& v : voices)
            {
                float modulator = std::sin(v.modPhase);
                float sample = std::sin(v.carrierPhase + v.modIndex * modulator);

                outputSample += sample;  // sum each voice

                // increment phases
                v.carrierPhase += 2.0f * juce::MathConstants<float>::pi * v.frequency / currentSampleRate;
                v.modPhase += 2.0f * juce::MathConstants<float>::pi * v.modFrequency / currentSampleRate;

                // wrap phases
                if (v.carrierPhase >= juce::MathConstants<float>::twoPi)
                    v.carrierPhase -= juce::MathConstants<float>::twoPi;
                if (v.modPhase >= juce::MathConstants<float>::twoPi)
                    v.modPhase -= juce::MathConstants<float>::twoPi;
            }

            // scale amplitude to prevent clipping
            channelData[i] = (outputSample / voices.size()) * amplitude;
        }
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}


//================================================my stuff
//funciton here called in main component
