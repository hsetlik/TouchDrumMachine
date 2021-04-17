/*
  ==============================================================================

    AppWindow.cpp
    Created: 12 Apr 2021 3:12:27pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "AppWindow.h"
DrumGridView::DrumGridView(ProcessorClock* clock) :
SequenceView(clock, this),
sequence(clock->getSequence()),
grid(sequence)
{
    
}
