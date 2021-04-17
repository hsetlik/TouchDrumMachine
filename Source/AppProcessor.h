/*
  ==============================================================================

    AppProcessor.h
    Created: 12 Apr 2021 3:13:55pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#define MAX_SUBDIV 60 //max resolution in subdivisions of a quarter note
#define DEFAULT_TEMPO 120
#define DEFAULT_LENGTH 16
#define DEFAULT_TRACKS 8
#define GRID_WIDTH 4


struct StepData
{
public:
    StepData(int start, int length) : startSubdiv(start), lengthSubdivs(length), hasNote(false)
    {
    }
    int getStartSubdiv() {return startSubdiv.load();}
    int getLengthSubdivs() {return lengthSubdivs.load();}
    bool getHasNote()
    {
        if(hasNote.load() > 0)
            return true;
        return false;
    }
    void setHasNote(bool shouldHaveNote)
    {
        hasNote = (shouldHaveNote) ? 1 : 0;
    }
private:
    std::atomic<int> startSubdiv;
    std::atomic<int> lengthSubdivs;
    std::atomic<int> hasNote;
};

class TrackData
{
public:
    TrackData(int idx, int length) : index(idx), lengthSubdivs(length), currentSubdiv(0)
    {
        int numSteps = lengthSubdivs.load() / MAX_SUBDIV;
        for(int i = 0; i < numSteps; ++i)
        {
            steps.add(new StepData(i * MAX_SUBDIV, MAX_SUBDIV));
        }
    }
    void advanceTo(int subdiv)
    {
        currentSubdiv = subdiv;
        for(auto s : steps)
        {
            if(s->getStartSubdiv() <= currentSubdiv && s->getStartSubdiv() + s->getLengthSubdivs() > currentSubdiv)
            {
                currentStep = s;
                break;
            }
        }
    }
    StepData* getCurrentStep()
    {
        return currentStep.load();
    }
    void toggleNote(StepData* step)
    {
        step->setHasNote(!step->getHasNote());
    }
    void toggleNote(int index)
    {
        auto* step = steps[index];
        step->setHasNote(!step->getHasNote());
    }
    juce::OwnedArray<StepData> steps;
    std::atomic<StepData*> currentStep;
    int index;
    std::atomic<int> lengthSubdivs;
    int currentSubdiv;
};

class SequenceData
{
public:
    SequenceData(int t=DEFAULT_TEMPO, int l = 16)
    {
        currentSubdiv = 0;
        for(int i = 0; i < DEFAULT_TRACKS; ++i)
        {
            tracks.add(new TrackData(i, DEFAULT_LENGTH * MAX_SUBDIV));
        }
        subdivLength = DEFAULT_LENGTH * MAX_SUBDIV;
    }
    int subdivLength;
    void advanceTo(int newSubdiv)
    {
        currentSubdiv = newSubdiv;
        for(auto t : tracks)
            t->advanceTo(newSubdiv);
    }
    std::atomic<int> currentSubdiv;
    bool isPlaying;
    juce::OwnedArray<TrackData> tracks;
};

class ProcessorClock
{
public:
    ProcessorClock(SequenceData* sData) : sequence(sData)
    {
        
    }
    void setSequenceLength(int lengthInFullBeats)
    {
        sequenceLength = lengthInFullBeats * MAX_SUBDIV;
    }
    void setSampleRate(double rate)
    {
        sampleRate = rate;
        findSamplesPerSubdiv();
    }
    void setProjectTempo(int tempo)
    {
        projectTempo = tempo;
        findSamplesPerSubdiv();
    }
    void advanceBySamples(int samples)
    {
        sampleInSequence += samples;
        if(sampleInSequence.load() > (samplesPerSubdiv.load() * sequenceLength.load()))
            sampleInSequence -= (samplesPerSubdiv.load() * sequenceLength.load());
        if(sequence->isPlaying)
            sequence->currentSubdiv = currentSubdiv();
    }
    int currentSubdiv()
    {
        return ceil(sampleInSequence.load() / samplesPerSubdiv.load());
    }
    SequenceData* getSequence()
    {
        return sequence;
    }
private:
    void findSamplesPerSubdiv()
    {
        auto secondsPerBeat = 1.0f / (projectTempo.load() * 60);
        samplesPerSubdiv = (secondsPerBeat / (float)MAX_SUBDIV) * sampleRate.load();
    }
    std::atomic<double> sampleRate;
    std::atomic<int> projectTempo;
    std::atomic<int> samplesPerSubdiv;
    std::atomic<int> sequenceLength;
    std::atomic<unsigned long> sampleInSequence;
    SequenceData* sequence;
};
