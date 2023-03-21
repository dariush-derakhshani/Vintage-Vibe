cmake_minimum_required(VERSION 3.12)

project(Vintage-Vibe VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(JUCE) # Assuming JUCE folder is in the root folder of your project

juce_add_plugin(Vintage-Vibe
    COMPANY_NAME "Dariush Derakhshani"
    PLUGIN_CODE VnVi
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS VST3 AU Standalone
    ProductName "Vintage Vibe"
)

target_compile_definitions(Vintage-Vibe PUBLIC
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0)

target_include_directories(Vintage-Vibe PUBLIC Gamma)
target_link_directories(Vintage-Vibe PUBLIC Gamma/build/lib)
#target_link_libraries(Vintage-Vibe Gamma)


target_sources(Vintage-Vibe PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    # Add any other source files here
)

target_include_directories(Vintage-Vibe PRIVATE
    Source
)

target_link_libraries(Vintage-Vibe
    PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        Gamma
)

juce_generate_juce_header(Vintage-Vibe)