/*
  ==============================================================================

    DrumGrid.cpp
    Created: 12 Apr 2021 3:12:12pm
    Author:  Hayden Setlik

  ==============================================================================
*/
#include "DrumGrid.h"
DrumGrid::DrumGrid(SequenceData* seq) :
sequence(seq)
{
    auto numTracks = sequence->tracks.size();
    padColors = Color::shadesBetween(UXPalette::deepViolet, UXPalette::paleViolet, numTracks);
    for(int i = 0; i < numTracks; ++i)
    {
        auto* trk = sequence->tracks[i];
        drumPads.add(new DrumPad(padColors[i], trk));
        addAndMakeVisible(drumPads.getLast());
        drumPads.getLast()->addListener(this);
    }
}

void DrumGrid::buttonClicked(juce::Button *b)
{
    auto pad = dynamic_cast<DrumPad*>(b);
    pad->toggleCurrentStep();
}
