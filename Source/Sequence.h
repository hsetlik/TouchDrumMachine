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
    StepButton(StepData* stp) :
    juce::ShapeButton("stepButton", UXPalette::darkRed, UXPalette::darkRed, UXPalette::lightRed),
    step(stp)
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
        step->setHasNote(hasNote);
        if(hasNote)
            color = UXPalette::lightRed;
        else
            color = UXPalette::darkGray3;
    }
    StepData* step;
    int widthSubDivs;
    int index;
};

enum class LabelType
{
    kick1, kick2, snare, closedHat, openHat, clave, clap
};

static juce::StringArray LabelTypeStrings("kick1", "kick2", "snare", "closedHat", "openHat",  "clave", "clap");

class TrackLabelImage : public juce::Component
{
public:
    TrackLabelImage(LabelType type= LabelType::kick1) : labelType(type)
    {
         setImage(labelType);
    }
    void resized() override
    {
    }
    void paint(juce::Graphics& g) override;
    void setImage(LabelType newType);
    juce::Image image;
private:
    LabelType labelType;
};

class SequenceTrack : public juce::Component, juce::Button::Listener
{
public:
    SequenceTrack(TrackData* trk);
    void buttonClicked(juce::Button* b) override;
    void resized() override;
private:
    TrackData* track;
    TrackLabelImage label;
    juce::OwnedArray<StepButton> stepButtons;
    std::vector<juce::Rectangle<int>> buttonAreas;
};
