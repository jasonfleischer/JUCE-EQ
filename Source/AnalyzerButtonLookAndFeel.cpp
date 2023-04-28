#include "AnalyzerButtonLookAndFeel.hpp"
#include "CustomColors.hpp"
#include "AnalyzerButton.hpp"

void AnalyzerButtonLookAndFeel::drawToggleButton(juce::Graphics &g,
                                   juce::ToggleButton &toggleButton,
                                   bool shouldDrawButtonAsHighlighted,
                                   bool shouldDrawButtonAsDown)
{
    using namespace juce;
    
    if (auto* analyzerButton = dynamic_cast<AnalyzerButton*>(&toggleButton))
    {
        auto bounds = toggleButton.getLocalBounds();
        
        g.setColour(CustomColors::background);
        g.fillRoundedRectangle(bounds.getX()+1, bounds.getY()+1, bounds.getWidth()-2, bounds.getHeight()-4, (bounds.getHeight()-4)/2);
        
        g.setColour(CustomColors::text);
        g.drawRoundedRectangle(bounds.getX()+1, bounds.getY()+1, bounds.getWidth()-2, bounds.getHeight()-4, (bounds.getHeight()-4)/2, 1.f);
       
        g.drawFittedText("Analyer", bounds.getX()+14, bounds.getY(), bounds.getWidth()-14, bounds.getHeight()-3, Justification::centred, 1);
        
        g.setColour(toggleButton.getToggleState() ? CustomColors::enabled: Colours::dimgrey );
        auto dim = bounds.getHeight()*0.35;
        g.fillEllipse(7, (bounds.getHeight()/2-(dim/2))-1, dim, dim);
    }
}
