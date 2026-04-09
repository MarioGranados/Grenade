#include "MainComponent.h"
#include "VoiceManager.h"
//==============================================================================
MainComponent::MainComponent():currentSampleRate(44100.0),
phase(0.0f),
amplitude(0.2f),
phaseDelta(0.0f),
frequency(523.23f), // C5 note
modFrequency(0.0f),
modIndex(0.0f),
modPhase(0.0f),
modPhaseDelta(0.0f),
useFM(false)
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    //===========================
    
    addAndMakeVisible(volumeKnob);
    volumeKnob.setSliderStyle(juce::Slider::LinearVertical);
    volumeKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    volumeKnob.setRange(0.0, 100, 1.0);
    volumeKnob.setValue(80);
    volumeKnob.onValueChange = [this](){
        handleVolumeChange(volumeKnob.getValue());
    };
    
    addAndMakeVisible(voicesAmountSlider);
    voicesAmountSlider.setSliderStyle(juce::Slider::LinearVertical);
    voicesAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    voicesAmountSlider.setRange(1.0, 18, 1.0);
    voicesAmountSlider.setValue(1);
    voicesAmountSlider.onValueChange = [this]() {
        handleVoicesAmount(voicesAmountSlider.getValue());
    };
    
    addAndMakeVisible(modulatorKnob);
    modulatorKnob.setSliderStyle(juce::Slider::Rotary);
    modulatorKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    modulatorKnob.setRange(0.0, 50.0, 1.0);
    modulatorKnob.setValue(0);
    modulatorKnob.onValueChange = [this]() {
        manager.setModIndex(modulatorKnob.getValue());
    };
    
    addAndMakeVisible(useFmButton);
    useFmButton.setButtonText("Use FM");
    useFmButton.setClickingTogglesState(true);
    useFmButton.onClick = [this](){
        DBG("useFM is now: " + juce::String(useFM ? "true" : "false"));
        useFM = useFmButton.getToggleState();
    };
    //============================
    

    
    addAndMakeVisible(knob);
    knob.setSliderStyle(juce::Slider::Rotary);
    knob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    
    knob.setRange(0.0, 100.0, 1.0);
    knob.setValue(50);
    
    knob.onValueChange = [this](){
        float value = knob.getValue();
        DBG("Knob value: " << value);
    };
    
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 69, 20);
    slider.setRange(0.0, 100, 1.0);
    slider.setValue(0);
    
    slider.onValueChange = [this]()
    {
        float value = slider.getValue();
        DBG("Slider value: " << value);
    };
    
    addAndMakeVisible(dropdown);
    
    // add items (id must be unique)
    dropdown.addItem("Sine", 1);
    dropdown.addItem("Square", 2);
    dropdown.addItem("Saw", 3);

    // default selection
    dropdown.setSelectedId(1);
    
    dropdown.onChange = [this]()
    {
        int selected = dropdown.getSelectedId();

        DBG("Selected ID: " << selected);
    };

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
        setAudioChannels (0, 2);
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
    manager.setNumVoices(1);
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

//    std::vector<Voice>& voices = manager.getVoices();
//    
//    
//    for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan)
//    {
//        auto* channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);
//
//        for (int i = 0; i < bufferToFill.numSamples; ++i)
//        {
//            float outputSample = 0.0f;
//
//            // loop through all voices
//            for (Voice& v : voices)
//            {
//                float modulator = std::sin(v.modPhase);
//                float sample;
//                
//                if(useFM) {
//                    sample = std::sin(v.carrierPhase + manager.getModIndex() * modulator);
//                } else {
//                    sample = std::sin(v.carrierPhase);
//                }
//
//                outputSample += sample;  // sum each voice
//
//                // increment phases
//                v.carrierPhase += 2.0f * juce::MathConstants<float>::pi * v.frequency / currentSampleRate;
//                v.modPhase += 2.0f * juce::MathConstants<float>::pi * v.modFrequency / currentSampleRate;
//
//                // wrap phases
//                if (v.carrierPhase >= juce::MathConstants<float>::twoPi)
//                    v.carrierPhase -= juce::MathConstants<float>::twoPi;
//                if (v.modPhase >= juce::MathConstants<float>::twoPi)
//                    v.modPhase -= juce::MathConstants<float>::twoPi;
//            }
//
//            // scale amplitude to prevent clipping
//            channelData[i] = (outputSample / voices.size()) * amplitude;
//        }
//    }
    
    auto* buffer = bufferToFill.buffer;
    int numChannels = buffer->getNumChannels();
    int numSamples = bufferToFill.numSamples;

    std::vector<Voice>& voices = manager.getVoices();

    for (int i = 0; i < numSamples; ++i)
    {
        double outputSample = 0.0;

        // Process each voice
        for (Voice& v : voices)
        {
            double modulator = std::sin(v.modPhase);
            double sample = useFM ? std::sin(v.carrierPhase + manager.getModIndex() * modulator)
                                  : std::sin(v.carrierPhase);

            outputSample += sample;

            // increment phases (double precision)
            v.carrierPhase += 2.0 * juce::MathConstants<double>::pi * v.frequency / currentSampleRate;
            v.modPhase += 2.0 * juce::MathConstants<double>::pi * v.modFrequency / currentSampleRate;

            // wrap phases to 0..2pi
            if (v.carrierPhase >= juce::MathConstants<double>::twoPi)
                v.carrierPhase -= juce::MathConstants<double>::twoPi;
            if (v.modPhase >= juce::MathConstants<double>::twoPi)
                v.modPhase -= juce::MathConstants<double>::twoPi;
        }

        // scale amplitude by number of voices
        float finalSample = static_cast<float>((outputSample / voices.size()) * amplitude);

        // write same sample to all channels (stereo-safe)
        for (int chan = 0; chan < numChannels; ++chan)
        {
            buffer->getWritePointer(chan, bufferToFill.startSample)[i] = finalSample;
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
    useFmButton.setBounds(30, 30, 150, 30);

    slider.setBounds(30, 80, 300, 30);        // horizontal slider

    knob.setBounds(30, 130, 100, 100);        // square knob

    dropdown.setBounds(200, 30, 150, 30);

    // vertical volume slider (make it tall)
    volumeKnob.setBounds(350, 80, 50, 200);
    
    voicesAmountSlider.setBounds(250, 80, 50, 200);
    
    modulatorKnob.setBounds(400, 120, 100, 150);
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}


//================================================my stuff
//funciton here called in main component
void MainComponent::handleKnobChange(float value) {
    DBG("Value is: " << value);
    DBG("current ampl: " << getAmplitude());
    setAmplitude(value);
}

void MainComponent::handleVolumeChange(float value) {
    float normalized = value / 100.0f;
    setAmplitude(normalized);
    DBG("Value is: " << value);
}

void MainComponent::handleVoicesAmount(float value) {
    manager.setNumVoices((int)value);
    DBG("Value is: " << value);
}


void MainComponent::setAmplitude(float value) {
    amplitude = value;
}

float MainComponent::getAmplitude() {
    return amplitude;
}
