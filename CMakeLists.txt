cmake_minimum_required(VERSION 3.12)

project(Vintage-Vibe VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(JUCE) # Assuming JUCE folder is in the root folder of your project

# Gamma library
set(GAMMA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Gamma") # Set the path to the Gamma folder
add_subdirectory(${GAMMA_ROOT}) # Add Gamma as a subdirectory

juce_add_plugin(Vintage-Vibe
    COMPANY_NAME "Dariush Derakhshani"
    PLUGIN_CODE VnVi
    FORMATS VST3 AU
    ProductName "Vintage Vibe"
)

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

target_link_libraries(Vintage-Vibe PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_plugin_client
    juce::juce_dsp
    juce::juce_gui_extra
    Gamma # Link the Gamma library
)

juce_generate_juce_header(Vintage-Vibe)
