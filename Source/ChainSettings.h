#pragma once
#ifndef ChainSettings_h
#define ChainSettings_h

struct ChainSettings
{
    float peakFreq { 0 }, peakGainInDecibels{ 0 }, peakQuality {1.f};
    float lowCutFreq { 0 }, highCutFreq { 0 };
    
    Slope lowCutSlope { Slope::Slope_12 }, highCutSlope { Slope::Slope_12 };
    
    bool lowCutBypassed { false }, peakBypassed { false }, highCutBypassed { false };
};

#endif
