/*
  ==============================================================================

    VoiceManager.cpp
    Created: 2 Apr 2026 2:06:02pm
    Author:  Mario Granados

  ==============================================================================
*/

#include "VoiceManager.h"
#include <cmath>

void VoiceManager::setNumVoices(int n)
{
    voices.clear();
    for (int i = 0; i < n; ++i)
    {
        Voice v;
        v.carrierPhase = 0.0f;
        v.modPhase = 0.0f;
        v.frequency = 440.0f + i * 5.0f;
        v.modFrequency = 220.0f;
        v.modIndex = 50.0f;
        voices.push_back(v);
    }
}

