#include "BypassButtonLookAndFeel.hpp"
#include "BypassToggleButton.hpp"
#include "CustomColors.hpp"

void BypassButtonLookAndFeel::drawToggleButton(juce::Graphics &g,
                                   juce::ToggleButton &toggleButton,
                                   bool shouldDrawButtonAsHighlighted,
                                   bool shouldDrawButtonAsDown)
{
    using namespace juce;
    
    if (auto* pb = dynamic_cast<BypassToggleButton*>(&toggleButton))
    {
        
        auto bounds = toggleButton.getLocalBounds();
        
        bounds.removeFromLeft(7);
        bounds.removeFromRight(7);
        
        g.setColour(CustomColors::background);
        g.fillRoundedRectangle(bounds.getX()+1, bounds.getY()+1, bounds.getWidth()-2, bounds.getHeight()-4, (bounds.getHeight()-4)/2);
        
        g.setColour(CustomColors::text);
        g.drawRoundedRectangle(bounds.getX()+1, bounds.getY()+1, bounds.getWidth()-2, bounds.getHeight()-4, (bounds.getHeight()-4)/2, 1.f);
       
        g.drawFittedText(toggleButton.getTitle(), bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight()-3, Justification::centred, 1);
        
        g.setColour(!toggleButton.getToggleState() ? CustomColors::enabled: Colours::dimgrey );
        auto dim = bounds.getHeight()*0.35;
        g.fillEllipse(14, (bounds.getHeight()/2-(dim/2))-1, dim, dim);
        
    }
}
