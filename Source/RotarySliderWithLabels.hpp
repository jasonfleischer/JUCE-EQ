#pragma once
#ifndef RotarySliderWithLabels_hpp
#define RotarySliderWithLabels_hpp

#include <JuceHeader.h>
#include "RotarySliderLookAndFeel.hpp"

struct RotarySliderWithLabels : juce::Slider
{
    struct LabelPos
    {
        float pos;
        juce::String label;
    };
    
    RotarySliderWithLabels(juce::RangedAudioParameter& rap, const juce::String& unitSuffix);
    ~RotarySliderWithLabels();
    void paint(juce::Graphics& g) override;
    
    juce::Rectangle<int> getSliderBounds() const;
    juce::String getDisplayString() const;
    juce::Array<LabelPos> labels;
    const int minMaxTextHeight;
    const int dialTextHeight;
    
private:
    
    RotarySliderLookAndFeel lnf;
    juce::RangedAudioParameter* param;
    juce::String suffix;
};

#endif
