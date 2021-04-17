/*
  ==============================================================================

    Sequence.h
    Created: 12 Apr 2021 3:12:02pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "RgbColor.h"
#include "AppProcessor.h"

class StepButton : public juce::ShapeButton
{
public:
    StepButton() :
    juce::ShapeButton("stepButton", UXPalette::darkRed, UXPalette::darkRed, UXPalette::lightRed)
    {
        setClickingTogglesState(true);
    }
    void paintButton(juce::Graphics& g, bool mouseOver, bool isMouseDown) override
    {
        g.setColour(color);
        g.fillRect(getBounds());
    }
    juce::Colour color = UXPalette::darkGray3;
    bool hasNote = false;
    void toggle()
    {
        hasNote = !hasNote;
        if(hasNote)
            color = UXPalette::lightRed;
        else
            color = UXPalette::darkGray3;
    }
};

class TrackLabelImage : public juce::Component
{
public:
    TrackLabelImage(juce::Image& img);
    void resized() override;
    void paint(juce::Graphics& g) override;
};

class SequenceTrack : public juce::Component
{
public:
    SequenceTrack(TrackData* trk);
private:
    TrackData* track;
    TrackLabelImage label;
    juce::OwnedArray<StepButton> stepButtons;
    
};
