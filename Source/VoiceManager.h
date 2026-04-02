/*
  ==============================================================================

    VoiceManager.h
    Created: 2 Apr 2026 2:06:02pm
    Author:  Mario Granados

  ==============================================================================
*/

#pragma once
#include <vector>
struct Voice
{
    float carrierPhase;
    float modPhase;
    float frequency;
    float modFrequency;
    float modIndex;
};

class VoiceManager
{
public:
    void setNumVoices(int n);
    void toggleVoices();
    std::vector<Voice>& getVoices() { return voices; }

private:
    std::vector<Voice> voices;
};
