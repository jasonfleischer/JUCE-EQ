#pragma once
#ifndef LookAndFeel_hpp
#define LookAndFeel_hpp

#include <JuceHeader.h>

struct AnalyzerButtonLookAndFeel : juce::LookAndFeel_V4
{
    void drawToggleButton (juce::Graphics &g,
                           juce::ToggleButton & toggleButton,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;
};

#endif
