#pragma once
#ifndef PowerButton_hpp
#define PowerButton_hpp

#include <JuceHeader.h>
#include "BypassButtonLookAndFeel.hpp"

struct BypassToggleButton : juce::ToggleButton {
    
    BypassToggleButton();
    ~BypassToggleButton();
    
private:
    BypassButtonLookAndFeel lnf;
};

#endif
