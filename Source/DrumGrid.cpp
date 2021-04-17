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
    padColors = Color::shadesBetween(UXPalette::deepViolet, UXPalette::paleViolet, GRID_WIDTH * GRID_WIDTH);
    for(int i = 0; i < numTracks; ++i)
    {
        auto* trk = sequence->tracks[i];
        drumPads.add(new DrumPad(padColors[i], trk));
        addAndMakeVisible(drumPads.getLast());
        drumPads.getLast()->addListener(this);
    }
    if(numTracks < (GRID_WIDTH * GRID_WIDTH))
    {
        for(int i = numTracks; i < GRID_WIDTH * GRID_WIDTH; ++i)
        {
            drumPads.add(new DrumPad(padColors[i], nullptr));
            addAndMakeVisible(drumPads.getLast());
        }
    }
        
}
void DrumGrid::resized()
{
    auto dX = getWidth() / GRID_WIDTH;
    auto idx = 0;
    for(int x = 0; x < GRID_WIDTH; ++x)
    {
        for(int y = 0; y < GRID_WIDTH; ++y)
        {
            drumPads[idx]->setBounds(x * dX, y * dX, dX, dX);
            ++idx;
        }
    }
}
void DrumGrid::paint(juce::Graphics &g)
{
    
}
void DrumGrid::buttonClicked(juce::Button *b)
{
    auto pad = dynamic_cast<DrumPad*>(b);
    pad->toggleCurrentStep();
}
