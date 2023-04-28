#include "BypassToggleButton.hpp"

BypassToggleButton::BypassToggleButton()
{
    setLookAndFeel(&lnf);
}

BypassToggleButton::~BypassToggleButton()
{
    setLookAndFeel(nullptr);
}
