#pragma once
#ifndef AnalyzerButton_hpp
#define AnalyzerButton_hpp

#include <JuceHeader.h>
#include "AnalyzerButtonLookAndFeel.hpp"

struct AnalyzerButton : juce::ToggleButton
{
    AnalyzerButton();
    ~AnalyzerButton();

private:
    AnalyzerButtonLookAndFeel lnf;
};

#endif
