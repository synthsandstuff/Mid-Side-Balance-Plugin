/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidSideAudioProcessorEditor::MidSideAudioProcessorEditor (MidSideAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (200, 600);
    
    midgainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    midgainSlider.setRange(-100.0f, +12.0f, 0.5f);
    midgainSlider.setTextValueSuffix(" dB");
    midgainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 40, 30);
    
    sidegainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    sidegainSlider.setRange(-100.0f, +12.0f, 0.5f);
    sidegainSlider.setTextValueSuffix(" dB");
    sidegainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 40, 30);
    
    addAndMakeVisible(&midgainSlider);
    midgainSlider.addListener(this);
    midgainSlider.setValue(juce::Decibels::gainToDecibels(audioProcessor.midGain->get()));
    midgainSlider.onValueChange  = [this] {audioProcessor.midGain->operator=(juce::Decibels::decibelsToGain((float)midgainSlider.getValue()));};
    
    addAndMakeVisible(&sidegainSlider);
    sidegainSlider.addListener(this);
    sidegainSlider.setValue(juce::Decibels::gainToDecibels(audioProcessor.sideGain->get()));
    sidegainSlider.onValueChange  = [this] {audioProcessor.sideGain->operator=(juce::Decibels::decibelsToGain((float)sidegainSlider.getValue()));};
    
    addAndMakeVisible(midLabel);
    midLabel.setText("Mid Gain", juce::dontSendNotification);
    midLabel.setJustificationType(juce::Justification::centred);
    midLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    
    addAndMakeVisible(sideLabel);
    sideLabel.setText("Side Gain", juce::dontSendNotification);
    sideLabel.setJustificationType(juce::Justification::centred);
    midLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
}

MidSideAudioProcessorEditor::~MidSideAudioProcessorEditor()
{
    
}

//==============================================================================
void MidSideAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Mid Side Gain", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void MidSideAudioProcessorEditor::resized()
{
    midgainSlider.setBounds(50, 50, 40, 500);
    sidegainSlider.setBounds(100, 50, 40, 500);
    midLabel.setBounds (50, 600, getWidth()/2, 20);
    sideLabel.setBounds (100, 600, getWidth()/2, 20);
}
