#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	m_instrumentManager = std::make_shared<CInstrumentManager>();
	m_metronome = std::make_shared<CMetronome>();
	m_eventManager.setInstrumentManager(m_instrumentManager);
	m_eventManager.setMetronome(m_metronome);

	// initialize debug instruments and samples
	this->initInstruments();

	m_btnAddInstrument.addListener(this, &ofApp::addInstrumentBtnPressed);
	m_btnRemoveInstrument.addListener(this, &ofApp::removeInstrumentBtnPressed);
	m_btnAddSample.addListener(this, &ofApp::addSampleBtnPressed);
	m_btnRemoveSample.addListener(this, &ofApp::removeSampleBtnPressed);
	m_metronomeEnabled.addListener(this, &ofApp::updateMetronomeEnabled);
	m_instrumentIdx.addListener(this, &ofApp::updateMenuTitle);
	m_bpm.addListener(this, &ofApp::updateBpm);

	// initialize menu
	m_gui.setup("Musicastle");
	m_gui.add(m_btnAddInstrument.setup("Add Instrument"));
	m_gui.add(m_btnRemoveInstrument.setup("Remove Instrument"));
	m_gui.add(m_instrumentIdx.set("Selected Instrument", 0, 0, m_instrumentManager->getInstrumentSize() - 1));
	m_gui.add(m_btnAddSample.setup("Add Sample"));
	m_gui.add(m_btnRemoveSample.setup("Remove Sample"));
	m_gui.add(m_sampleIdx.set("Selected Sample", 0, 0, m_instrumentManager->getInstrument(0).m_samplePlayer.size() - 1));
	m_gui.add(m_metronomeEnabled.set("Metronom", m_metronome->getEnabled()));
	m_gui.add(m_bpm.set("Bpm", m_eventManager.getBpm(), 1, 500));
}

//--------------------------------------------------------------
void ofApp::exit() {
	m_btnAddSample.removeListener(this, &ofApp::addSampleBtnPressed);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofBackground(255, 255, 255);

	// update the sound playing system
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {
	auto samplePlayer = m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samplePlayer;
	if (samplePlayer.empty()) {
		m_gui.draw();
		return;
	}

	float widthDiv = ofGetWidth() / samplePlayer.size();
	std::string tmpStr;
	for (auto i = 0; i < samplePlayer.size(); ++i) {
		// draw the background colors:
		if (((i + 1) % 2) == 0) {
			ofSetHexColor(0xeeeeee);
		}
		else {
			ofSetHexColor(0xffffff);
		}

		ofDrawRectangle(widthDiv * i, 0, widthDiv, ofGetHeight());

		// draw the sample area
		const auto sample = samplePlayer.at(i);
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
	auto instrument = m_instrumentManager->getInstrument(m_instrumentIdx.get());
	switch (key)
	{
	case OF_KEY_UP:
		instrument.play(0);
		break;
	case OF_KEY_LEFT:
		instrument.play(1);
		break;
	case OF_KEY_DOWN:
		instrument.play(2);
		break;
	case OF_KEY_RIGHT:
		instrument.play(3);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	auto samplePlayer = m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samplePlayer;
	if (samplePlayer.empty()) {
		return;
	}

	float widthStep = ofGetWidth() / samplePlayer.size();
	for (auto i = 0; i < samplePlayer.size(); ++i) {
		if (x >= (widthStep * i) && x < (widthStep * (i + 1))) {
			auto sample = samplePlayer.at(i);
			sample.play();
			sample.setPan(ofMap(x, (widthStep * i), (widthStep * (i + 1)), -1, 1, true));
		}
	}
}

//--------------------------------------------------------------
void ofApp::addInstrumentBtnPressed()
{
	auto name = ofSystemTextBoxDialog("Instrument:");
	m_instrumentManager->addInstrument(name);
	m_instrumentIdx.setMax(m_instrumentManager->getInstrumentSize() - 1);
}

//--------------------------------------------------------------
void ofApp::removeInstrumentBtnPressed()
{
	m_instrumentManager->removeInstrument(m_instrumentIdx.get());
	m_instrumentIdx.setMax(m_instrumentManager->getInstrumentSize() - 1);
	m_instrumentIdx.set(0);
}

//--------------------------------------------------------------
void ofApp::addSampleBtnPressed() {
	ofFileDialogResult result = ofSystemLoadDialog("Load Sample");
	if (result.bSuccess) {
		m_instrumentManager->getInstrument(m_instrumentIdx.get()).addSample(result.getPath());
		m_sampleIdx.setMax(m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samplePlayer.size() - 1);
	}
}

//--------------------------------------------------------------
void ofApp::removeSampleBtnPressed() {
	if (!m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samplePlayer.empty()) {
		m_instrumentManager->getInstrument(m_instrumentIdx.get()).removeSample(m_sampleIdx.get());
		m_sampleIdx.setMax(m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samplePlayer.size() - 1);
		m_sampleIdx.set(0);
	}
}

//--------------------------------------------------------------
void ofApp::updateMetronomeEnabled(bool& enabled)
{
	m_metronome->setEnabled(enabled);
}

//--------------------------------------------------------------
void ofApp::updateBpm(int& bpm)
{
	m_eventManager.setBpm(bpm);
}

//--------------------------------------------------------------
void ofApp::updateMenuTitle(int & idx)
{
	m_gui.setName(m_instrumentManager->getInstrument(m_instrumentIdx.get()).getName());
}

//--------------------------------------------------------------
void ofApp::initInstruments()
{
	std::vector<std::string> m_samples = {
		"../../data/samples/piano/c.wav",
		"../../data/samples/piano/d.wav",
		"../../data/samples/piano/e.wav",
		"../../data/samples/piano/f.wav"
	};

	m_instrumentManager->addInstrument("Piano");

	for (const auto sample : m_samples) {
		m_instrumentManager->getInstrument("Piano").addSample(sample);
	}
}
