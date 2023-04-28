/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomColors.hpp"

SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
peakFreqSlider(*audioProcessor.apvts.getParameter("Peak Freq"), "Hz"),
peakGainSlider(*audioProcessor.apvts.getParameter("Peak Gain"), "dB"),
peakQualitySlider(*audioProcessor.apvts.getParameter("Peak Quality"), "Q"),
lowCutFreqSlider(*audioProcessor.apvts.getParameter("LowCut Freq"), "Hz"),
highCutFreqSlider(*audioProcessor.apvts.getParameter("HighCut Freq"), "Hz"),
lowCutSlopeSlider(*audioProcessor.apvts.getParameter("LowCut Slope"), "dB/Oct"),
highCutSlopeSlider(*audioProcessor.apvts.getParameter("HighCut Slope"), "db/Oct"),

responseCurveComponent(audioProcessor),

peakFreqSliderAttachment(audioProcessor.apvts, "Peak Freq", peakFreqSlider),
peakGainSliderAttachment(audioProcessor.apvts, "Peak Gain", peakGainSlider),
peakQualitySliderAttachment(audioProcessor.apvts, "Peak Quality", peakQualitySlider),
lowCutFreqSliderAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider),
highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider),
lowCutSlopeSliderAttachment(audioProcessor.apvts, "LowCut Slope", lowCutSlopeSlider),
highCutSlopeSliderAttachment(audioProcessor.apvts, "HighCut Slope", highCutSlopeSlider),

lowcutBypassButtonAttachment(audioProcessor.apvts, "LowCut Bypassed", lowcutBypassButton),
peakBypassButtonAttachment(audioProcessor.apvts, "Peak Bypassed", peakBypassButton),
highcutBypassButtonAttachment(audioProcessor.apvts, "HighCut Bypassed", highcutBypassButton),
analyzerEnabledButtonAttachment(audioProcessor.apvts, "Analyzer Enabled", analyzerEnabledButton)
{
    peakFreqSlider.labels.add({0.f, "20"});
    peakFreqSlider.labels.add({1.f, "20k"});
    
    peakGainSlider.labels.add({0.f, "-24"});
    peakGainSlider.labels.add({1.f, "+24"});
    
    peakQualitySlider.labels.add({0.f, "0.1"});
    peakQualitySlider.labels.add({1.f, "10"});
    
    lowCutFreqSlider.labels.add({0.f, "20"});
    lowCutFreqSlider.labels.add({1.f, "20k"});
    
    highCutFreqSlider.labels.add({0.f, "20"});
    highCutFreqSlider.labels.add({1.f, "20k"});
    
    lowCutSlopeSlider.labels.add({0.0f, "12"});
    lowCutSlopeSlider.labels.add({1.f, "48"});
    
    highCutSlopeSlider.labels.add({0.0f, "12"});
    highCutSlopeSlider.labels.add({1.f, "48"});
    
    lowcutBypassButton.setTitle("Low-Cut");
    peakBypassButton.setTitle("Peak");
    highcutBypassButton.setTitle("High-Cut");
    
    for (auto* comp : getComps())
    {
        addAndMakeVisible(comp);
    }
    
    updatePeakEnabledState(peakBypassButton.getToggleState());
    auto safePtr = juce::Component::SafePointer<SimpleEQAudioProcessorEditor>(this);
    peakBypassButton.onClick = [safePtr]()
    {
        if (auto* comp = safePtr.getComponent())
        {
            auto bypassed = comp->peakBypassButton.getToggleState();
            comp->updatePeakEnabledState(bypassed);
        }
    };
    
    updateLowCutEnabledState(lowcutBypassButton.getToggleState());
    lowcutBypassButton.onClick = [safePtr]()
    {
        if (auto* comp = safePtr.getComponent())
        {
            auto bypassed = comp->lowcutBypassButton.getToggleState();
            comp->updateLowCutEnabledState(bypassed);
        }
    };
    
    updateHighCutEnabledState(highcutBypassButton.getToggleState());
    highcutBypassButton.onClick = [safePtr]()
    {
        if (auto* comp = safePtr.getComponent())
        {
            auto bypassed = comp->highcutBypassButton.getToggleState();
            comp->updateHighCutEnabledState(bypassed);
        }
    };

    responseCurveComponent.toggleAnalysisEnablement(analyzerEnabledButton.getToggleState());
    analyzerEnabledButton.onClick = [safePtr]()
    {
        if (auto* comp = safePtr.getComponent())
        {
            auto enabled = comp->analyzerEnabledButton.getToggleState();
            comp->responseCurveComponent.toggleAnalysisEnablement(enabled);
        }
    };
    setSize (580, 530);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
    peakBypassButton.setLookAndFeel(nullptr);
    highcutBypassButton.setLookAndFeel(nullptr);
    lowcutBypassButton.setLookAndFeel(nullptr);

    analyzerEnabledButton.setLookAndFeel(nullptr);
}

void SimpleEQAudioProcessorEditor::paint(juce::Graphics &g)
{
    using namespace juce;
    
    g.fillAll (Colours::black);
}

void SimpleEQAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();

    auto responseArea = bounds.removeFromTop(bounds.getHeight() * 0.47f).reduced(5);
    responseCurveComponent.setBounds(responseArea);
    
    auto analyzerEnabledArea = responseArea.removeFromBottom(35);
    analyzerEnabledArea.setWidth(80);
    analyzerEnabledArea.setX(25);
    analyzerEnabledArea.removeFromBottom(10);
    analyzerEnabledButton.setBounds(analyzerEnabledArea);
    
    bounds.removeFromTop(2);
    
    auto w = bounds.getWidth();
    auto p = 0.33;
    auto lowCutArea = bounds.removeFromLeft(w * p);
    auto highCutArea = bounds.removeFromRight(w * p);
    
    lowcutBypassButton.setBounds(lowCutArea.removeFromTop(25));
    lowCutArea.removeFromTop(10);
    lowCutFreqSlider.setBounds(lowCutArea.removeFromTop(lowCutArea.getHeight() * 0.5));
    lowCutSlopeSlider.setBounds(lowCutArea);
    
    highcutBypassButton.setBounds(highCutArea.removeFromTop(25));
    highCutArea.removeFromTop(10);
    highCutFreqSlider.setBounds(highCutArea.removeFromTop(highCutArea.getHeight() * 0.5));
    highCutSlopeSlider.setBounds(highCutArea);
    
    peakBypassButton.setBounds(bounds.removeFromTop(25));
    bounds.removeFromTop(10);
    
    auto h = bounds.getHeight();
    peakFreqSlider.setBounds(bounds.removeFromTop(h * 0.33));
    peakGainSlider.setBounds(bounds.removeFromTop(h * 0.33));
    peakQualitySlider.setBounds(bounds);
}

void SimpleEQAudioProcessorEditor::updateLowCutEnabledState(bool bypassed)
{
    lowCutFreqSlider.setEnabled( !bypassed );
    lowCutSlopeSlider.setEnabled( !bypassed );
}

void SimpleEQAudioProcessorEditor::updatePeakEnabledState(bool bypassed)
{
    peakFreqSlider.setEnabled( !bypassed );
    peakGainSlider.setEnabled( !bypassed );
    peakQualitySlider.setEnabled( !bypassed );
}
void SimpleEQAudioProcessorEditor::updateHighCutEnabledState(bool bypassed)
{
    highCutFreqSlider.setEnabled( !bypassed );
    highCutSlopeSlider.setEnabled( !bypassed );
}

std::vector<juce::Component*> SimpleEQAudioProcessorEditor::getComps()
{
    return
    {
        &peakFreqSlider,
        &peakGainSlider,
        &peakQualitySlider,
        &lowCutFreqSlider,
        &highCutFreqSlider,
        &lowCutSlopeSlider,
        &highCutSlopeSlider,
        &responseCurveComponent,
        &lowcutBypassButton,
        &peakBypassButton,
        &highcutBypassButton,
        &analyzerEnabledButton
    };
}
