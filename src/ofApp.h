#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "Metronom/Metronom.h"

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
	void updateMetronomEnabled(bool& enabled);
	void updateMetronomBpm(int& bpm);

private:
	std::vector<ofSoundPlayer> m_vecSoundPlayer;

	ofxPanel m_gui;
	ofParameter<int> m_sampleId;
	ofParameter<bool> m_metronomEnabled;
	ofParameter<int> m_metronomBpm;
	ofxButton m_btnAddSample;
	ofxButton m_btnRemoveSample;
	CMetronom m_metronom;
};

