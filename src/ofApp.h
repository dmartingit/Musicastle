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

	void loadSampleBtnPressed();

	std::vector<std::string> m_samples;
	std::vector<ofSoundPlayer> m_vecSoundPlayer;

	ofxPanel m_gui;
	ofxButton m_btnLoadSample;
};

