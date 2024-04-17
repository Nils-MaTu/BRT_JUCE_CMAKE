#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BRTChallengeAudioProcessorEditor::BRTChallengeAudioProcessorEditor (BRTChallengeAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

BRTChallengeAudioProcessorEditor::~BRTChallengeAudioProcessorEditor()
{
}

//==============================================================================
void BRTChallengeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void BRTChallengeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

// Open a SOFA file using a file chooser
void BRTChallengeAudioProcessorEditor::openSOFAButtonClicked()
{
//    chooser = std::make_unique<juce::FileChooser> ("Select a SOFA file to load...",
//                                                   juce::File{},
//                                                   "*.sofa");                     // Filter for SOFA files
//    auto chooserFlags = juce::FileBrowserComponent::openMode
//                        | juce::FileBrowserComponent::canSelectFiles;
//
//    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)     // Launch the file chooser
//    {
//        auto file = fc.getResult();
//
//        if (file != juce::File{})
//        {
//            // Load the SOFA file
//            if (LoadSOFAFile(file)) {
//
//                juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon, "Success", "SOFA file loaded successfully", "OK");
//                sourceAzimuthDial.setEnabled(true);
//                sourceElevationDial.setEnabled(true);
//                sourceDistanceDial.setEnabled(true);
//
//                // Create a new ToggleButton for the new SOFA file
//                ToggleButton* sofaFileButton = new ToggleButton(file.getFileNameWithoutExtension());
//                sofaFileButton->setRadioGroupId(1);
//                sofaFileButtons.add(sofaFileButton);
//                addAndMakeVisible(sofaFileButton);
//                sofaFileButton->addListener(this);
//                sofaFileButton->setToggleState(true, juce::NotificationType::dontSendNotification);
//
//                // Call resized() to update the layout
//                resized();
//
//                // Set the listener HRTF to the last loaded HRTF
//                listener->SetHRTF(HRTF_list.back());
//            }
//        }
//    });
}

