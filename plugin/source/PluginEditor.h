#pragma once

#include "PluginProcessor.h"
//#include "juce_audio_devices/sources/juce_AudioTransportSource.h"
//#include "juce_audio_formats//sources/juce_AudioTransportSource.h"


//==============================================================================
class BRTChallengeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit BRTChallengeAudioProcessorEditor (BRTChallengeAudioProcessor&);
    ~BRTChallengeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton openSOFAButton;
    juce::TextButton openWavButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::Label sourceAzimuthLabel;
    juce::Slider sourceAzimuthDial;
    juce::Label sourceElevationLabel;
    juce::Slider sourceElevationDial;
    juce::Label sourceDistanceLabel;
    juce::Slider sourceDistanceDial;
    juce::OwnedArray<juce::Button> sofaFileButtons;

    std::unique_ptr<juce::FileChooser> chooser;

    juce::AudioPluginFormatManager formatManager;
//    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
//    juce::AudioTransportSource transportSource;
//    TransportState state;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BRTChallengeAudioProcessor& processorRef;
    void openSOFAButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BRTChallengeAudioProcessorEditor)
};
