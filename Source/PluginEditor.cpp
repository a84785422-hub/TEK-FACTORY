#include "PluginEditor.h"
#include "SampleList.h"

TEK_FACTORYAudioProcessorEditor::TEK_FACTORYAudioProcessorEditor(TEK_FACTORYAudioProcessor& p) : AudioProcessorEditor(&p), processor(p) {
    look.setColour(juce::ResizableWindow::backgroundColourId, juce::Colour(0xff09090d));
    look.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xffb84cff));
    look.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff292333));
    look.setColour(juce::Slider::thumbColourId, juce::Colour(0xff8cff00));
    look.setColour(juce::Label::textColourId, juce::Colour(0xffd9d3e4));
    look.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xff17151f));
    look.setColour(juce::ComboBox::textColourId, juce::Colour(0xfff4f0ff));
    look.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xff8cff00));
    setLookAndFeel(&look);
    title.setText("TEK FACTORY", juce::dontSendNotification);
    title.setFont(juce::Font(juce::FontOptions(31.0f, juce::Font::bold)));
    title.setColour(juce::Label::textColourId, juce::Colour(0xfff8f4ff));
    addAndMakeVisible(title);
    subtitle.setText("JUMPSTYLE / TEKSTYLE KICK LAB     •     V1.0", juce::dontSendNotification);
    subtitle.setFont(juce::Font(juce::FontOptions(11.0f, juce::Font::bold)));
    subtitle.setColour(juce::Label::textColourId, juce::Colour(0xff8cff00));
    addAndMakeVisible(subtitle);
    for (int i=0;i<embeddedKickCount;++i) kickBox.addItem(juce::String(i+1).paddedLeft('0',2)+"  /  "+embeddedKicks[i].name, i+1);
    addAndMakeVisible(kickBox);
    kickAttachment=std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.parameters,"kick",kickBox);
    previewButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff8cff00));
    previewButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xff09090d));
    previewButton.setClickingTogglesState(false);
    previewButton.onClick=[this]{ processor.triggerPreview(); };
    addAndMakeVisible(previewButton);
    status.setText("30 BUILT-IN KICKS   //   MANUAL SOUND DESIGN",juce::dontSendNotification);
    status.setColour(juce::Label::textColourId,juce::Colour(0xffb84cff));
    status.setFont(juce::Font(juce::FontOptions(10.0f,juce::Font::bold)));
    addAndMakeVisible(status);
    const char* ids[]={"pitch","low","mid","high","drive","clip","sub","crush","punch","length","output"};
    const char* names[]={"PITCH","LOW","MID","HIGH","DRIVE","CLIP","SUB","CRUSH","PUNCH","LENGTH","OUTPUT"};
    for (int i=0;i<11;++i) {
        knobs[(size_t)i]=std::make_unique<juce::Slider>();
        auto& s=*knobs[(size_t)i]; s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,64,18); s.setColour(juce::Slider::textBoxTextColourId,juce::Colour(0xfff5f0ff)); s.setColour(juce::Slider::textBoxBackgroundColourId,juce::Colour(0xff17151f)); s.setNumDecimalPlacesToDisplay(1);
        addAndMakeVisible(s);
        labels[(size_t)i] = std::make_unique<juce::Label>();
        addAndMakeVisible(*labels[(size_t)i]);
        labels[(size_t)i]=std::make_unique<juce::Label>(); labels[(size_t)i]->setText(names[i],juce::dontSendNotification); labels[(size_t)i]->setJustificationType(juce::Justification::centred); labels[(size_t)i]->setFont(juce::Font(juce::FontOptions(11.0f,juce::Font::bold))); labels[(size_t)i]->setColour(juce::Label::textColourId,(i==4||i==5||i==7)?juce::Colour(0xff8cff00):juce::Colour(0xffb84cff)); addAndMakeVisible(*labels[(size_t)i]);
        attachments[(size_t)i]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters,ids[i],s);
    }
    setSize(900, 570);
}
void TEK_FACTORYAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour(0xff09090d));
    g.setGradientFill(juce::ColourGradient(juce::Colour(0xff21102f),0,0,juce::Colour(0xff09090d),(float)getWidth(),(float)getHeight(),false));
    g.fillRect(0,0,getWidth(),120);
    g.setColour(juce::Colour(0xffb84cff)); g.fillRect(0,119,getWidth(),2);
    g.setColour(juce::Colour(0xff8cff00)); g.fillRoundedRectangle(22.0f,143.0f,(float)getWidth()-44.0f,72.0f,9.0f);
    g.setColour(juce::Colour(0xff15131b)); g.fillRoundedRectangle(24.0f,145.0f,(float)getWidth()-48.0f,68.0f,8.0f);
    g.setColour(juce::Colour(0xff292333));
    for(int i=0;i<11;++i) { int col=i%6; int row=i/6; float x=22.0f+col*145.0f; float y=237.0f+row*154.0f; g.drawRoundedRectangle(x,y,133.0f,143.0f,8.0f,1.0f); }
    g.setColour(juce::Colour(0xff8cff00)); g.setFont(juce::Font(juce::FontOptions(10.0f,juce::Font::bold))); g.drawText("SIGNAL CHAIN   /   SAMPLE → PITCH → DRIVE → EQ → CLIP",24,getHeight()-22,getWidth()-48,14,juce::Justification::centredLeft);
}
void TEK_FACTORYAudioProcessorEditor::resized() {
    title.setBounds(24,14,350,45); subtitle.setBounds(27,62,450,20);
    kickBox.setBounds(36,160,555,38); previewButton.setBounds(640,157,220,44); status.setBounds(36,196,800,16);
    for(int i=0;i<11;++i){int col=i%6;int row=i/6;int x=22+col*145;int y=238+row*154;labels[(size_t)i]->setBounds(x+4,y+8,125,20);knobs[(size_t)i]->setBounds(x+7,y+28,119,108);}
}
