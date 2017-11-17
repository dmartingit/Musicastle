#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void exit();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void addSampleBtnPressed();
	void removeSampleBtnPressed();

	std::vector<ofSoundPlayer> m_vecSoundPlayer;

	ofxPanel m_gui;
	ofParameter<int> m_sampleId;
	ofxButton m_btnAddSample;
	ofxButton m_btnRemoveSample;
};

