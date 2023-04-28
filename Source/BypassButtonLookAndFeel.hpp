#pragma once
#ifndef PowerButtonLookAndFeel_hpp
#define PowerButtonLookAndFeel_hpp
#include <JuceHeader.h>

struct BypassButtonLookAndFeel : juce::LookAndFeel_V4
{
    void drawToggleButton (juce::Graphics &g,
                           juce::ToggleButton & toggleButton,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;
};

#endif
