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
    
    midGain.setSliderStyle(juce::Slider::LinearBarVertical);
    midGain.setRange(-144, +12, 0.5);
    midGain.setTextValueSuffix(" dB");
    midGain.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 40, 30);
    
    sideGain.setSliderStyle(juce::Slider::LinearBarVertical);
    sideGain.setRange(-144, +12, 0.5);
    sideGain.setTextValueSuffix(" dB");
    sideGain.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 40, 30);
    
    addAndMakeVisible(&midGain);
    midGain.addListener(this);
    audioProcessor.midGainVal = juce::Decibels::decibelsToGain((float)midGain.getValue());
    midGain.setValue(juce::Decibels::gainToDecibels(audioProcessor.midGainVal));
    midGain.onValueChange  = [this] {audioProcessor.midGainVal = juce::Decibels::decibelsToGain((float)midGain.getValue());};
 
    addAndMakeVisible(&sideGain);
    sideGain.addListener(this);
    audioProcessor.sideGainVal = juce::Decibels::decibelsToGain((float)sideGain.getValue());
    sideGain.setValue(juce::Decibels::gainToDecibels(audioProcessor.sideGainVal));
    sideGain.onValueChange  = [this] {audioProcessor.sideGainVal = juce::Decibels::decibelsToGain((float)sideGain.getValue());};
/*
    addAndMakeVisible(midLabel);
    midLabel.setText("Mid Gain", juce::dontSendNotification);
    midLabel.attachToComponent(&midGain, true);
    
    addAndMakeVisible(sideLabel);
    sideLabel.setText("Side Gain", juce::dontSendNotification);
    sideLabel.attachToComponent(&sideGain, true);
 */
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
    midGain.setBounds(50, 50, 40, 500);
    sideGain.setBounds(100, 50, 40, 500);
/*  midLabel.setBounds (50, 580, 40, 20);
    sideLabel.setBounds (100, 580, 40, 20);*/
}

double getValueFromText(const juce::String& text)
{
    auto minusInfinitydB = -144.0;
    auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();
    return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB
                                                : decibelText.getDoubleValue();
}

juce::String getTextFromValue (double value)
{
    return juce::Decibels::toString (value);
}
