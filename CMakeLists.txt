
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
        Samples/K24_01_SUB_CRUSH.wav
        Samples/K24_02_ACID_BITE.wav
        Samples/K24_03_METAL_EDGE.wav
        Samples/K24_04_DARK_RUMBLE.wav
        Samples/K24_05_HARD_CLIP.wav
        Samples/K24_06_NASAL_FURY.wav
        Samples/K24_07_TIGHT_PUNCH.wav
        Samples/K24_08_BITROT.wav
        Samples/K24_09_WIDE_GRIT.wav
        Samples/K24_10_TERROR_TAIL.wav
        Samples/POTO_01_SUB_CRUSH.wav
        Samples/POTO_02_ACID_BITE.wav
        Samples/POTO_03_METAL_EDGE.wav
        Samples/POTO_04_DARK_RUMBLE.wav
        Samples/POTO_05_HARD_CLIP.wav
        Samples/POTO_06_NASAL_FURY.wav
        Samples/POTO_07_TIGHT_PUNCH.wav
        Samples/POTO_08_BITROT.wav
        Samples/POTO_09_WIDE_GRIT.wav
        Samples/POTO_10_TERROR_TAIL.wav
        Samples/TAP_01_SUB_CRUSH.wav
        Samples/TAP_02_ACID_BITE.wav
        Samples/TAP_03_METAL_EDGE.wav
        Samples/TAP_04_DARK_RUMBLE.wav
        Samples/TAP_05_HARD_CLIP.wav
        Samples/TAP_06_NASAL_FURY.wav
        Samples/TAP_07_TIGHT_PUNCH.wav
        Samples/TAP_08_BITROT.wav
        Samples/TAP_09_WIDE_GRIT.wav
        Samples/TAP_10_TERROR_TAIL.wav
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
    VST3_CAN_REPLACE_VST2 FALSE
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
