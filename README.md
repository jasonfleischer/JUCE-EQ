# Simple JUCE EQ

![Screenshot](./Resources/Screenshot1.png "Sreenshot")

## Description

A Mac OS simple equalizer built with XCode and the [JUCE](https://juce.com/) framework. It was built by following this tutorial:

[Learn Modern C++ by Building an Audio Plugin (w/ JUCE Framework)](https://www.youtube.com/watch?v=i_Iq4_Kd7Rc&ab_channel=freeCodeCamp.org)

Produces a standalone product with AU and VST3 plugins.

## Instructions

1. Open <project root>/Builds/MacOX/SimpleEQ.xcodeproj
2. Choose target (such as 'SimpleEQ - Standalone Plugin') and run

If building plugins, copy product folder files (vst3, component) to the Mac-OS plugin path: /Library/Audio/Plug-Ins

## Notes

- You can get the JUCE Framework found [here](https://github.com/juce-framework/JUCE). 
- Running SimpleEQ.jucer wipes pList information. Run the following to insert missing properties:
```
python3 <project root>/Scripts/insert_plist_settings.py
```

## Credits

#### Matkat Music 
- [github](https://github.com/matkatmusic)
- [SimpleEQ project](https://github.com/matkatmusic/SimpleEQ)
- [Instagram](https://www.instagram.com/matkatmusic)

## Author

- [Jason Fleischer](https://jasonfleischer.github.io/website/)
