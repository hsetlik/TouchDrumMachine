/*
  ==============================================================================

    AppWindow.h
    Created: 12 Apr 2021 3:12:27pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "AppProcessor.h"
#include "DrumGrid.h"

class SequenceView
{
public:
    SequenceView(ProcessorClock* clock, juce::Component* comp) :
    pClock(clock),
    sequence(pClock->getSequence()),
    pComponent(comp)
    {
        
    }
    juce::Component* getComponent() { return pComponent; }
private:
    ProcessorClock* pClock;
    SequenceData* sequence;
    juce::Component* pComponent;
};

class DrumGridView : public juce::Component, SequenceView
{
public:
    DrumGridView(ProcessorClock* clock);
private:
    SequenceData* sequence;
    DrumGrid grid;
    
};

