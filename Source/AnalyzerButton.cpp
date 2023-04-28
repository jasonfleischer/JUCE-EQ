#include "AnalyzerButton.hpp"

AnalyzerButton::AnalyzerButton()
{
    setLookAndFeel(&lnf);
}

AnalyzerButton::~AnalyzerButton()
{
    setLookAndFeel(nullptr);
}
