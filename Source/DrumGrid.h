/*
  ==============================================================================

    DrumGrid.h
    Created: 12 Apr 2021 3:12:12pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "RgbColor.h"
#include "AppProcessor.h"

class DrumPad : public juce::ShapeButton
{
public:
    DrumPad(juce::Colour col, TrackData* trk) :
    juce::ShapeButton("drumPad", col, col, col),
    color(col),
    track(trk)
    {
        highlightColor = Color::blendHSB(color, juce::Colours::white, 0.65f);
    }
    void paintButton(juce::Graphics& g, bool mouseOver, bool isMouseDown) override
    {
        if(isMouseDown)
            g.setColour(highlightColor);
        else
            g.setColour(color);
        g.fillRect(getBounds().reduced(6));
    }
    void toggleCurrentStep()
    {
        if(track != nullptr)
            track->toggleNote(track->getCurrentStep());
    }
private:
    juce::Colour color;
    juce::Colour highlightColor;
    TrackData* track;
};

class DrumGrid : public juce::Component, juce::Button::Listener
{
public:
    DrumGrid(SequenceData* seq);
    void buttonClicked(juce::Button* b) override;
    void resized() override;
    void paint(juce::Graphics& g) override;
private:
    std::vector<juce::Colour> padColors;
    juce::OwnedArray<DrumPad> drumPads;
    SequenceData* sequence;
};



