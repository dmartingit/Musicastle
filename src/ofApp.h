#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "Metronome\Metronome.h"
#include "InstrumentManager\InstrumentManager.h"
#include "EventManager\EventManager.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void exit();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:
	void addInstrumentBtnPressed();
	void removeInstrumentBtnPressed();
	void addSampleBtnPressed();
	void removeSampleBtnPressed();
	void updateMetronomeEnabled(bool& enabled);
	void updateBpm(int& bpm);
	void updateMenuTitle(int& idx);
	void recordBtnPressed(bool& record);
	void clearLoopBtnPressed();

	void initInstruments();

private:
	ofxPanel m_gui;
	ofxButton m_btnAddInstrument;
	ofxButton m_btnRemoveInstrument;
	ofParameter<int> m_instrumentIdx;
	ofxButton m_btnAddSample;
	ofxButton m_btnRemoveSample;
	ofParameter<int> m_sampleIdx;
	ofParameter<bool> m_metronomeEnabled;
	ofParameter<int> m_bpm;
	ofParameter<bool> m_record;
	ofxButton m_btnClearLoop;
	ofParameter<bool> m_changeSampleShortcut;
	std::shared_ptr<CMetronome> m_metronome;
	std::shared_ptr<CInstrumentManager> m_instrumentManager;
	CEventManager m_eventManager;
};

