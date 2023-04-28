#include "RotarySliderLookAndFeel.hpp"
#include "CustomColors.hpp"
#include "RotarySliderWithLabels.hpp"

void RotarySliderLookAndFeel::drawRotarySlider(juce::Graphics & g,
                                   int x,
                                   int y,
                                   int width,
                                   int height,
                                   float sliderPosProportional,
                                   float rotaryStartAngle,
                                   float rotaryEndAngle,
                                   juce::Slider & slider)
{
    using namespace juce;
    
    if (auto* rswl = dynamic_cast<RotarySliderWithLabels*>(&slider))
    {
        jassert(rotaryStartAngle < rotaryEndAngle);
        
        auto bounds = Rectangle<float>(x, y, width, height);
        auto enabled = slider.isEnabled();
        auto sliderAngRad = jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);
        auto outerArcWidth = 3.0f;
        auto color = enabled ? CustomColors::text : CustomColors::disabled;
        
        {
            auto ellipseBounds = bounds.reduced(8);
            g.setColour(color);
            g.drawEllipse(ellipseBounds, 2.f);
        }
        
        {
            Path fillerArc;
            PathStrokeType pst(outerArcWidth, PathStrokeType::JointStyle::curved, PathStrokeType::EndCapStyle::rounded);

            auto size = jmin(bounds.getWidth(), bounds.getHeight());
            auto radius = size/2;
            auto r = bounds.withSizeKeepingCentre(size, size).toFloat();

            fillerArc.addCentredArc(r.getCentreX(), r.getCentreY(), radius, radius, 0.f, sliderAngRad, rotaryEndAngle, true);
            g.setColour(Colours::darkgrey);
            g.strokePath(fillerArc, pst);
        }
        
        {
            Path coloredArc;
            PathStrokeType pst(outerArcWidth, PathStrokeType::JointStyle::curved, PathStrokeType::EndCapStyle::rounded);
            
            auto size = jmin(bounds.getWidth(), bounds.getHeight());
            auto radius = size/2;
            auto r = bounds.withSizeKeepingCentre(size, size).toFloat();

            coloredArc.addCentredArc(r.getCentreX(), r.getCentreY(), radius, radius, 0.f, rotaryStartAngle, sliderAngRad, true);
            g.setColour(color);
            g.strokePath(coloredArc, pst);
        }
        
        {
            auto dotBounds = bounds.reduced(16);
            auto center = dotBounds.getCentre();
            auto dotSize = 4;
            
            Path dotPath;
            PathStrokeType pst(2.5f, PathStrokeType::JointStyle::curved);
            
            Rectangle<float> r;
            r.setLeft(center.getX() - dotSize/2);
            r.setRight(center.getX() + dotSize/2);
            r.setTop(dotBounds.getY());
            r.setBottom(dotBounds.getY() + dotSize);
            
            dotPath.addRoundedRectangle(r, dotSize/2.f);
            dotPath.applyTransform(AffineTransform().rotated(sliderAngRad, center.getX(), center.getY()));
            g.setColour(color);
            g.fillPath(dotPath);
        }
        
        {
            auto textBounds = bounds;
            g.setFont(rswl->dialTextHeight);
            auto text = rswl->getDisplayString();
            auto strWidth = g.getCurrentFont().getStringWidth(text);
            
            Rectangle<float> r;
            r.setSize(strWidth, rswl->dialTextHeight);
            r.setCentre(textBounds.getCentreX(), textBounds.getHeight()+7);
            
            g.setColour(color);
            g.drawFittedText(text, r.toNearestInt(), juce::Justification::centred, 1);
        }
    }
}
