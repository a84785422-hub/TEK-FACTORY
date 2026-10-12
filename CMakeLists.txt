
cmake_minimum_required(VERSION 3.22)

project(TEK_FACTORY VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.10
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(JUCE)

juce_add_binary_data(TEKFactorySamples
    SOURCES
        Samples/KICK_2K24_01.wav
        Samples/KICK_2K24_02.wav
        Samples/KICK_2K24_03.wav
        Samples/KICK_2K24_04.wav
        Samples/KICK_2K24_05.wav
        Samples/KICK_2K24_06.wav
        Samples/KICK_2K24_07.wav
        Samples/KICK_2K24_08.wav
        Samples/KICK_2K24_09.wav
        Samples/KICK_2K24_10.wav
)

juce_add_plugin(TEK_FACTORY
    COMPANY_NAME "TEK FACTORY Audio"
    BUNDLE_ID "com.tekfactory.kickdesigner"
    PLUGIN_MANUFACTURER_CODE TKFa
    PLUGIN_CODE TK01
    FORMATS VST3
    PRODUCT_NAME "TEK FACTORY"
    DESCRIPTION "Jumpstyle and Tekstyle kick designer"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD FALSE
)

juce_generate_juce_header(TEK_FACTORY)

target_sources(TEK_FACTORY PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_include_directories(TEK_FACTORY PRIVATE Source)

target_compile_definitions(TEK_FACTORY PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(TEK_FACTORY PRIVATE
    TEKFactorySamples
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
