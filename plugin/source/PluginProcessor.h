#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <BRTLibrary.h>


//==============================================================================
class BRTChallengeAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BRTChallengeAudioProcessor();
    ~BRTChallengeAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    void setupBRT(int sampleRate, int bufferSize);
    bool LoadSOFAFile(const juce::File& file);
    void LoadSource(const juce::String& name, float azimuth, float elevation, float distance);
    //==========================================================================
    Common::CGlobalParameters globalParameters;                                   // Global BRT parameters
    BRTBase::CBRTManager brtManager;                                              // BRT global manager interface
    std::shared_ptr<BRTListenerModel::CListenerHRTFbasedModel> listener;          // Pointer to listener model
    std::shared_ptr<BRTSourceModel::CSourceSimpleModel> source1BRT;               // Pointer to audio source model
    BRTReaders::CSOFAReader sofaReader;                                           // SOFA reader provided by BRT Library
    std::vector<std::shared_ptr<BRTServices::CHRTF>> HRTF_list;                   // List of HRTFs loaded
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BRTChallengeAudioProcessor)
};
