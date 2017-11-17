#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	std::vector<std::string> m_samples = {
		"../../data/samples/piano/c.wav",
		"../../data/samples/piano/d.wav",
		"../../data/samples/piano/e.wav",
		"../../data/samples/piano/f.wav"
	};

	for (const auto sample : m_samples) {
		ofSoundPlayer player;
		player.load(sample);
		player.setVolume(0.75f);
		player.setMultiPlay(true);
		m_vecSoundPlayer.push_back(player);
	}

	m_btnAddSample.addListener(this, &ofApp::addSampleBtnPressed);
	m_btnRemoveSample.addListener(this, &ofApp::removeSampleBtnPressed);
	m_metronomEnabled.addListener(this, &ofApp::updateMetronomEnabled);
	m_metronomBpm.addListener(this, &ofApp::updateMetronomBpm);

	m_gui.setup("Musicastle");
	m_gui.add(m_sampleId.set("Selected Sample", 0, 0, m_vecSoundPlayer.size() - 1));
	m_gui.add(m_btnAddSample.setup("Add Sample"));
	m_gui.add(m_btnRemoveSample.setup("Remove Sample"));
	m_gui.add(m_metronomEnabled.set("Metronom", m_metronom.getEnabled()));
	m_gui.add(m_metronomBpm.set("Metronom Bpm", m_metronom.getBpm(), 1, 500));
}

//--------------------------------------------------------------
void ofApp::exit() {
	m_btnAddSample.removeListener(this, &ofApp::addSampleBtnPressed);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofBackground(255, 255, 255);

	// update the sound playing system:
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (m_vecSoundPlayer.empty()) {
		m_gui.draw();
		return;
	}

	float widthDiv = ofGetWidth() / m_vecSoundPlayer.size();
	std::string tmpStr;
	for (auto i = 0; i < m_vecSoundPlayer.size(); ++i) {
		// draw the background colors:
		if (((i + 1) % 2) == 0) {
			ofSetHexColor(0xeeeeee);
		}
		else {
			ofSetHexColor(0xffffff);
		}

		ofDrawRectangle(widthDiv * i, 0, widthDiv, ofGetHeight());

		// draw the sample area
		const auto sample = m_vecSoundPlayer.at(i);
		if (sample.isPlaying()) ofSetHexColor(0xFF0000);
		else ofSetHexColor(0x000000);
		ofDrawBitmapString("Sample", (widthDiv * i) + 50, 50);

		ofSetHexColor(0x000000);
		tmpStr = "click to play (Left Arrow)\npan: " + ofToString(sample.getPan());
		ofDrawBitmapString(tmpStr, (widthDiv * i) + 20, ofGetHeight() - 50);
	}

	// draw gui last so it is topmost
	m_gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case OF_KEY_UP:
		if (m_vecSoundPlayer.size() > 0) {
			m_vecSoundPlayer.at(0).play();
		}
		break;
	case OF_KEY_LEFT:
		if (m_vecSoundPlayer.size() > 1) {
			m_vecSoundPlayer.at(1).play();
		}
		break;
	case OF_KEY_DOWN:
		if (m_vecSoundPlayer.size() > 2) {
			m_vecSoundPlayer.at(2).play();
		}
		break;
	case OF_KEY_RIGHT:
		if (m_vecSoundPlayer.size() > 3) {
			m_vecSoundPlayer.at(3).play();
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (m_vecSoundPlayer.empty()) {
		return;
	}

	float widthStep = ofGetWidth() / m_vecSoundPlayer.size();
	for (auto i = 0; i < m_vecSoundPlayer.size(); ++i) {
		if (x >= (widthStep * i) && x < (widthStep * (i + 1))) {
			auto sample = m_vecSoundPlayer.at(i);
			sample.play();
			sample.setPan(ofMap(x, (widthStep * i), (widthStep * (i + 1)), -1, 1, true));
		}
	}
}

//--------------------------------------------------------------
void ofApp::addSampleBtnPressed() {
	ofFileDialogResult result = ofSystemLoadDialog("Load Sample");
	if (result.bSuccess) {
		ofSoundPlayer player;
		player.load(result.getPath());
		player.setVolume(0.75f);
		player.setMultiPlay(true);
		m_vecSoundPlayer.push_back(player);

		// update the sample id range
		m_sampleId.setMax(m_vecSoundPlayer.size() - 1);
	}
}

//--------------------------------------------------------------
void ofApp::removeSampleBtnPressed() {
	if (!m_vecSoundPlayer.empty()) {
		m_vecSoundPlayer.erase(m_vecSoundPlayer.begin() + m_sampleId.get());

		// update the sample id range
		m_sampleId.setMax(m_vecSoundPlayer.size() - 1);
		m_sampleId.set(0);
	}
}

//--------------------------------------------------------------
void ofApp::updateMetronomEnabled(bool& enabled)
{
	m_metronom.setEnabled(enabled);
}

//--------------------------------------------------------------
void ofApp::updateMetronomBpm(int & bpm)
{
	m_metronom.setBpm(bpm);
}
