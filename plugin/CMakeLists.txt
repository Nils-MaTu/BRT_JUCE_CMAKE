cmake_minimum_required(VERSION 3.22)

# Version is needed by JUCE.
project(AudioPlugin VERSION 0.1.0)

set(BIN_DATA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

#juce_set_aax_sdk_path($ENV{HOME}/SDKs/aax-sdk-2-5-1)

# Adds a plugin target (that's basically what the Projucer does).
juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME SonaraDSP # change this
    IS_SYNTH FALSE # may change this
    NEEDS_MIDI_INPUT FALSE # may change this
    NEEDS_MIDI_OUTPUT FALSE # may change this
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    AAX_COPY_DIR "/Applications/Plug-Ins/"
    VST3_COPY_DIR "/$ENV{HOME}/Library/Audio/Plug-Ins/VST3/"
    AU_COPY_DIR "/$ENV{HOME}/Library/Audio/Plug-Ins/Components/"
    PLUGIN_MANUFACTURER_CODE SNRA # change this
    PLUGIN_CODE BRT # change this
    FORMATS VST3 AU # may change this
    PRODUCT_NAME "BRT Challenge" # change this
)

juce_generate_juce_header(${PROJECT_NAME})

# Sets the source files of the plugin project.
target_sources(${PROJECT_NAME}
    PRIVATE
        source/PluginEditor.h
        source/PluginEditor.cpp
        source/PluginProcessor.h
        source/PluginProcessor.cpp

)

# Sets the include directories of the plugin project.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LIB_DIR}/brt/include
)

juce_add_binary_data(BinaryData SOURCES
        ${BIN_DATA_INCLUDE_DIR}/arrow.png
        ${BIN_DATA_INCLUDE_DIR}/Background.png
        ${BIN_DATA_INCLUDE_DIR}/bypass_off.png
        ${BIN_DATA_INCLUDE_DIR}/bypass_on.png
        ${BIN_DATA_INCLUDE_DIR}/fader_background.png
        ${BIN_DATA_INCLUDE_DIR}/fader_head.png
        ${BIN_DATA_INCLUDE_DIR}/head.obj
        ${BIN_DATA_INCLUDE_DIR}/logo.png
        ${BIN_DATA_INCLUDE_DIR}/Manrope-Medium.ttf
        ${BIN_DATA_INCLUDE_DIR}/Manrope-Regular.ttf
        ${BIN_DATA_INCLUDE_DIR}/Manrope-SemiBold.ttf
        ${BIN_DATA_INCLUDE_DIR}/Manrope-VariableFont_wght.ttf
        ${BIN_DATA_INCLUDE_DIR}/menuBar.png
        ${BIN_DATA_INCLUDE_DIR}/Montserrat-VariableFont_wght.ttf
        ${BIN_DATA_INCLUDE_DIR}/saveWidget.png
        ${BIN_DATA_INCLUDE_DIR}/SFPro.ttf
        ${BIN_DATA_INCLUDE_DIR}/SFProTextRegular.otf
        ${BIN_DATA_INCLUDE_DIR}/Slider_select.png
        ${BIN_DATA_INCLUDE_DIR}/Slider_unselect.png
        ${BIN_DATA_INCLUDE_DIR}/sphere.obj
        ${BIN_DATA_INCLUDE_DIR}/sphere_background_off.png
        ${BIN_DATA_INCLUDE_DIR}/sphere_background_on.png
        ${BIN_DATA_INCLUDE_DIR}/BasicFragment.glsl
        ${BIN_DATA_INCLUDE_DIR}/BasicVertex.glsl
)

# Links to all necessary dependencies. The present ones are recommended by JUCE.
# If you use one of the additional modules, like the DSP module, you need to specify it here.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        BinaryData
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_opengl
        juce::juce_audio_formats
        juce::juce_audio_devices

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        brt
)

# These definitions are recommended by JUCE.
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)



# Silences some deprecation warnings that (hopefully) will be fixed in a future release of JUCE.
if (MSVC)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING)
endif()


# In Visual Studio this command provides a nice grouping of source files in "filters".
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/..)
