#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "Metronome\Metronome.h"
#include "LoopManager\LoopManager.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void exit();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:
	void addSampleBtnPressed();
	void removeSampleBtnPressed();
	void updateMetronomeEnabled(bool& enabled);
	void updateMetronomeBpm(int& bpm);

private:
	std::vector<ofSoundPlayer> m_vecSoundPlayer;

	ofxPanel m_gui;
	ofParameter<int> m_sampleId;
	ofParameter<bool> m_metronomeEnabled;
	ofParameter<int> m_metronomeBpm;
	ofxButton m_btnAddSample;
	ofxButton m_btnRemoveSample;
	CMetronome m_metronome;
	CLoopManager m_loopManager;
};

