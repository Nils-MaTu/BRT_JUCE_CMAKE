#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BRTChallengeAudioProcessor::BRTChallengeAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
}

BRTChallengeAudioProcessor::~BRTChallengeAudioProcessor()
{
}

//==============================================================================
const juce::String BRTChallengeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BRTChallengeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BRTChallengeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BRTChallengeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BRTChallengeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BRTChallengeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BRTChallengeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BRTChallengeAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String BRTChallengeAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void BRTChallengeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void BRTChallengeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);

//    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
//    globalParameters.SetSampleRate(sampleRate);
//    globalParameters.SetBufferSize(samplesPerBlockExpected);
}

void BRTChallengeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool BRTChallengeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void BRTChallengeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    // If we still haven't loaded a file, simply clear the buffer

//        if (readerSource.get() == nullptr)
//        {
//            buffer.clear();
//            return;
//        }
//
//        // Obtener las muestras de audio del transportSource
//        juce::AudioBuffer<float> audioInputBuffer(1, buffer.getNumSamples()); // Buffer mono para las muestras de audio
//        juce::AudioSourceChannelInfo audioBufferToFill(&audioInputBuffer, 0, buffer.getNumSamples());
//        transportSource.getNextAudioBlock(audioBufferToFill);
//
//        // Prepare the input buffer for source 1
//        CMonoBuffer<float> source1Buffer(buffer.numSamples);
//        for (int i = 0; i < bufferToFill.numSamples; i++) {
//			source1Buffer[i] = audioInputBuffer.getSample(0, i);
//		}
//		// Pass the input buffer to the BRT Library source
//		source1BRT->SetBuffer(source1Buffer);
//
//       // Binaural processing
//        brtManager.ProcessAll(); // Process all sources
//
//        //// Get output stereo buffer
//        Common::CEarPair<CMonoBuffer<float>> outputBuffer;
//        listener->GetBuffers(outputBuffer.left, outputBuffer.right);
//
//
//        // Left output buffer is expected to be in channel 0
//        float* const leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//        float* const rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
//        for (int i = 0; i < bufferToFill.numSamples; i++) {
//            leftBuffer[i] = outputBuffer.left[i];
//            rightBuffer[i] = outputBuffer.right[i];
//
//            // For test purposes just copy the sambples from source1Buffer to the output buffers
//            // leftBuffer[i] = source1Buffer[i];
//            // rightBuffer[i] = source1Buffer[i];
//        }

}

//==============================================================================
bool BRTChallengeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BRTChallengeAudioProcessor::createEditor()
{
    return new BRTChallengeAudioProcessorEditor (*this);
}

//==============================================================================
void BRTChallengeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void BRTChallengeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BRTChallengeAudioProcessor();
}

void BRTChallengeAudioProcessor::setupBRT(int sampleRate, int bufferSize)
{
    // Global parameters
    globalParameters.SetSampleRate(sampleRate);
    globalParameters.SetBufferSize(bufferSize);

    // Listener creation
    brtManager.BeginSetup();
    listener = brtManager.CreateListener<BRTListenerModel::CListenerHRTFbasedModel>("listener1");
    brtManager.EndSetup();

    // Place the listener in (0,0,0)
    Common::CTransform listenerPosition = Common::CTransform();
    listenerPosition.SetPosition(Common::CVector3(0, 0, 0));
    listener->SetListenerTransform(listenerPosition);
}

bool BRTChallengeAudioProcessor::LoadSOFAFile(const juce::File& file) {
    bool result = false;
    std::shared_ptr<BRTServices::CHRTF> hrtf = std::make_shared<BRTServices::CHRTF>();

    // Try to get sample rate in SOFA
    int sampleRateInSOFAFile = sofaReader.GetSampleRateFromSofa(file.getFullPathName().toStdString());
    if (sampleRateInSOFAFile == -1) {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, "Error", "The SOFA file does not contain a valid sample rate", "OK");
        result = false;
    }
    else {
        // Make sure sample rate is same as selected in app.
        if (sampleRateInSOFAFile != globalParameters.GetSampleRate()) {
            juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, "Error", "The SOFA file sample rate does not match the selected sample rate", "OK");
            result = false;
        }
        else {
            // Load SOFA file
//            result = sofaReader.ReadHRTFFromSofa(file.getFullPathName().toStdString(), hrtf, HRTFRESAMPLINGSTEP, "NearestPoint");
            if (result) {
                HRTF_list.push_back(hrtf);
            }
            else {
                juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, "Error", "Error loading SOFA file", "OK");
            }
        }
    }
    return result;
}

// Load a source in the BRT Library
void BRTChallengeAudioProcessor::LoadSource(const juce::String& name, float azimuth, float elevation, float distance) {
    // Create a source
    brtManager.BeginSetup();
    source1BRT = brtManager.CreateSoundSource<BRTSourceModel::CSourceSimpleModel>(name.toStdString());
    listener->ConnectSoundSource(source1BRT);
    brtManager.EndSetup();

    // Set the source position
    Common::CVector3 listenerPosition = listener->GetListenerTransform().GetPosition();
    Common::CTransform sourceTransform;
    Common::CVector3 sourcePosition = Common::CVector3(distance * std::cos(azimuth) * std::cos(elevation) + listenerPosition.x,
                                                       distance * std::sin(azimuth) * std::cos(elevation) + listenerPosition.y,
                                                       distance * std::sin(elevation) + listenerPosition.z);
    sourceTransform.SetPosition(sourcePosition);
    source1BRT->SetSourceTransform(sourceTransform);
}

