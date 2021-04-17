/*
  ==============================================================================

    Sequence.cpp
    Created: 12 Apr 2021 3:12:02pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "Sequence.h"

void TrackLabelImage::setImage(LabelType newType)
{
    labelType = newType;
    switch(labelType)
    {
        case LabelType::kick1:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::kick10_5x_png, BinaryData::kick10_5x_pngSize);
            break;
        }
        case LabelType::kick2:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::kick20_5x_png, BinaryData::kick20_5x_pngSize);
            break;
        }
        case LabelType::snare:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::snare0_5x_png, BinaryData::snare0_5x_pngSize);
            break;
        }
        case LabelType::closedHat:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::closedHat0_5x_png, BinaryData::closedHat0_5x_pngSize);
            break;
        }
        case LabelType::openHat:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::openHat0_5x_png, BinaryData::openHat0_5x_pngSize);
            break;
        }
        case LabelType::clave:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::clave0_5x_png, BinaryData::clave0_5x_pngSize);
            break;
        }
        case LabelType::clap:
        {
            image = juce::ImageCache::getFromMemory(BinaryData::clap0_5x_png, BinaryData::clap0_5x_pngSize);
            break;
        }
    }
}

void TrackLabelImage::paint(juce::Graphics &g)
{
    auto fBounds = getBounds().toFloat();
    g.drawImage(image, fBounds);
}

SequenceTrack::SequenceTrack(TrackData* trk) : track(trk)
{
    auto numSteps = track->steps.size();
    for(int i = 0; i < numSteps; ++i)
    {
        stepButtons.add(new StepButton(track->steps[i]));
        auto stepLength = track->steps[i]->getLengthSubdivs();
        stepButtons.getLast()->widthSubDivs = stepLength;
        stepButtons.getLast()->index = i;
        addAndMakeVisible(stepButtons.getLast());
        stepButtons.getLast()->addListener(this);
    }
    addAndMakeVisible(&label);
}
void SequenceTrack::buttonClicked(juce::Button *b)
{
    auto step = dynamic_cast<StepButton*>(b);
    track->toggleNote(step->index);
    step->toggle();
}

void SequenceTrack::resized()
{
    buttonAreas.clear();
    auto labelWidth = getWidth() / 12;
    label.setBounds(0, 0, labelWidth, getHeight());
    auto dX = (getWidth() - labelWidth) / track->lengthSubdivs.load();
    int leftEdge = labelWidth;
    for(auto button : stepButtons)
    {
        auto rect = juce::Rectangle<int>(leftEdge, 0, dX * button->widthSubDivs, getHeight());
        buttonAreas.push_back(rect.reduced(5));
        button->setBounds(rect.reduced(5));
        leftEdge += dX * button->widthSubDivs;
    }
}
