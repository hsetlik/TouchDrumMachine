/*
  ==============================================================================

    RgbColor.h
    Created: 6 Feb 2021 4:10:08pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct Color
{
    //fourth argument sets alpha, fully opaque by default
    static juce::Colour RGBColor(int r, int g, int b, int a = 255)
    {
        return(juce::Colour(juce::uint8(r), juce::uint8(g), juce::uint8(b), juce::uint8(a)));
    }
    
    static juce::Colour blendRGB(juce::Colour colorA, juce::Colour colorB, float ratio)
    {
        auto fRed = lerp(colorA.getFloatRed(), colorB.getFloatRed(), ratio);
        auto fGreen = lerp(colorA.getFloatGreen(), colorB.getFloatGreen(), ratio);
        auto fBlue = lerp(colorA.getFloatBlue(), colorB.getFloatBlue(), ratio);
        auto fAlpha = lerp(colorA.getFloatAlpha(), colorB.getFloatAlpha(), ratio);
        return juce::Colour(fRed, fGreen, fBlue, fAlpha);
    }
    static juce::Colour blendHSB(juce::Colour a, juce::Colour b, float ratio)
    {
        auto fHue = lerp(a.getHue(), b.getHue(), ratio);
        auto fSat = lerp(a.getSaturation(), b.getSaturation(), ratio);
        auto fBrt = lerp(a.getBrightness(), b.getBrightness(), ratio);
        auto fAlpha = lerp(a.getFloatAlpha(), b.getFloatAlpha(), ratio);
        return juce::Colour(fHue, fSat, fBrt, fAlpha);
    }
    static juce::Colour complement(juce::Colour start)
    {
        auto fHue = start.getHue();
        auto fSat = start.getSaturationHSL();
        auto fLgt = start.getLightness();
        auto dHueStart = fabs(1.0f - fHue);
        return juce::Colour(dHueStart, fSat, fLgt, 1.0f);
    }
    static juce::Colour desaturated(juce::Colour input, float amt)
    {
        return juce::Colour(input.getHue(), input.getSaturation() * amt, input.getBrightness(), input.getFloatAlpha());
    }
    static std::vector<juce::Colour> shadesBetween(juce::Colour a, juce::Colour b, int numShades)
    {
        
        std::vector<juce::Colour> output;
        output.push_back(a);
        auto inc = 1.0f / (float) numShades;
        for(int i = 1; i < (numShades - 1); ++i)
        {
            output.push_back(blendHSB(a, b, inc * i));
        }
        output.push_back(b);
        return output;
    }
private:
    static int lerp(int a, int b, float ratio)
    {
        return (a * (1.0f - ratio)) + (b * ratio);
    }
    static float lerp(float a, float b, float ratio)
    {
        return (a * (1.0f - ratio)) + (b * ratio);
    }
};

namespace UXPalette
{
static juce::Colour deepViolet = Color::RGBColor(51, 0, 153);
static juce::Colour paleViolet = Color::desaturated(deepViolet, 0.2f);
static juce::Colour deepRed = Color::RGBColor(230, 44, 11);
static juce::Colour paleRed = Color::desaturated(deepRed, 0.2f);

};
