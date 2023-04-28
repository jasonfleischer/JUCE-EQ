#pragma once
#ifndef RotarySliderLookAndFeel_hpp
#define RotarySliderLookAndFeel_hpp

#include <JuceHeader.h>

struct RotarySliderLookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
    
};

#endif
