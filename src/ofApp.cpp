#include "ofApp.h"

#include <chrono>

//--------------------------------------------------------------
void ofApp::setup() {
	// initialize members
	m_arduinoManager.connect();
	m_instrumentManager = std::make_shared<CInstrumentManager>();
	m_metronome = std::make_shared<CMetronome>();
	m_eventManager.setInstrumentManager(m_instrumentManager);
	m_eventManager.setMetronome(m_metronome);

	// initialize debug instruments and samples
	this->initInstruments();

	m_btnAddInstrument.addListener(this, &ofApp::addInstrumentBtnPressed);
	m_btnRemoveInstrument.addListener(this, &ofApp::removeInstrumentBtnPressed);
	m_instrumentIdx.addListener(this, &ofApp::updateMenuTitle);
	m_btnAddSample.addListener(this, &ofApp::addSampleBtnPressed);
	m_btnRemoveSample.addListener(this, &ofApp::removeSampleBtnPressed);
	m_metronomeEnabled.addListener(this, &ofApp::updateMetronomeEnabled);
	m_beat.addListener(this, &ofApp::updateBeat);
	m_bpm.addListener(this, &ofApp::updateBpm);
	m_record.addListener(this, &ofApp::recordBtnPressed);
	m_btnClearLoop.addListener(this, &ofApp::clearLoopBtnPressed);

	// initialize menu
	m_gui.setup("Musicastle");
	m_gui.add(m_btnAddInstrument.setup("Add Instrument"));
	m_gui.add(m_btnRemoveInstrument.setup("Remove Instrument"));
	m_gui.add(m_instrumentIdx.set("Selected Instrument", 0, 0, m_instrumentManager->getInstrumentSize() - 1));
	m_gui.add(m_btnAddSample.setup("Add Sample"));
	m_gui.add(m_btnRemoveSample.setup("Remove Sample"));
	m_gui.add(m_sampleIdx.set("Selected Sample", 0, 0, m_instrumentManager->getInstrument(0).m_samples.size() - 1));
	m_gui.add(m_metronomeEnabled.set("Metronom", m_metronome->getEnabled()));
	m_gui.add(m_beat.set("Beat", m_metronome->getBeat(), 1, 8));
	m_gui.add(m_bpm.set("Bpm", m_eventManager.getBpm(), 1, 500));
	m_gui.add(m_record.set("Record", m_instrumentManager->getInstrument(0).getRecord()));
	m_gui.add(m_btnClearLoop.setup("Clear Loop"));
	m_gui.add(m_changeSampleShortcut.set("Change Sample Shortcut", false));
}

//--------------------------------------------------------------
void ofApp::exit() {
	m_btnAddSample.removeListener(this, &ofApp::addSampleBtnPressed);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofBackground(255, 255, 255);

	// update arduino
	this->m_arduinoManager.loop();
	this->updateArduinoAnalogInput();

	// update the sound playing system
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {
	auto& samplePlayer = m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samples;
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
		if (sample.m_player.isPlaying()) ofSetHexColor(0xFF0000);
		else ofSetHexColor(0x000000);
		ofDrawBitmapString("Sample", (widthDiv * i) + 50, 50);

		ofSetHexColor(0x000000);
		tmpStr = "click to play\nShortcut: ";
		tmpStr.append(std::to_string(sample.getShortcut()));
		ofDrawBitmapString(tmpStr, (widthDiv * i) + 20, ofGetHeight() - 50);
	}

	// draw gui last so it is topmost
	m_gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (m_changeSampleShortcut.get()) {
		m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samples.at(m_sampleIdx.get()).setShortcut(key);
		m_changeSampleShortcut.set(false);
		return;
	}

	for (auto i = 0; i < m_instrumentManager->getInstrumentSize(); ++i) {
		auto& instrument = m_instrumentManager->getInstrument(i);
		for (auto j = 0; j < instrument.m_samples.size(); ++j) {
			if (key == instrument.m_samples.at(j).getShortcut()) {
				instrument.play(j);
				this->m_arduinoManager.setLED(true);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	this->m_arduinoManager.setLED(false);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	auto& instrument = m_instrumentManager->getInstrument(m_instrumentIdx.get());
	auto& samples = instrument.m_samples;
	if (samples.empty()) {
		return;
	}

	float widthStep = ofGetWidth() / samples.size();
	for (auto i = 0; i < samples.size(); ++i) {
		if (x >= (widthStep * i) && x < (widthStep * (i + 1))) {
			instrument.play(i);
			this->m_arduinoManager.setLED(true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	this->m_arduinoManager.setLED(false);
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
		m_sampleIdx.setMax(m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samples.size() - 1);
	}
}

//--------------------------------------------------------------
void ofApp::removeSampleBtnPressed() {
	if (!m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samples.empty()) {
		m_instrumentManager->getInstrument(m_instrumentIdx.get()).removeSample(m_sampleIdx.get());
		m_sampleIdx.setMax(m_instrumentManager->getInstrument(m_instrumentIdx.get()).m_samples.size() - 1);
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
void ofApp::updateBeat(int& beat)
{
	m_metronome->setBeat(beat);
}

//--------------------------------------------------------------
void ofApp::updateMenuTitle(int& idx)
{
	m_gui.setName(m_instrumentManager->getInstrument(m_instrumentIdx.get()).getName());
}

//--------------------------------------------------------------
void ofApp::recordBtnPressed(bool& record)
{
	m_instrumentManager->getInstrument(m_instrumentIdx.get()).setRecord(record);
}

//--------------------------------------------------------------
void ofApp::clearLoopBtnPressed()
{
	m_instrumentManager->getInstrument(m_instrumentIdx.get()).clearTimes();
}

//--------------------------------------------------------------
void ofApp::updateArduinoAnalogInput()
{
	// control volume
	static int lastVolume = this->m_arduinoManager.getAnalog(15);
	auto volume = this->m_arduinoManager.getAnalog(15);
	if (lastVolume != volume) {
		auto mappedVolume = ofMap(volume, 0, 1023, 0, 1);
		for (auto i = 0; i < m_instrumentManager->getInstrumentSize(); ++i) {
			auto& instrument = m_instrumentManager->getInstrument(i);
			for (auto j = 0; j < instrument.m_samples.size(); ++j) {
				instrument.m_samples[j].m_player.setVolume(mappedVolume);
			}
		}
		lastVolume = volume;
	}

	// play arduino sample
	auto now = std::chrono::high_resolution_clock::now();
	static auto difTime = now;
	if (this->m_arduinoManager.getAnalog(14) == 1023 && std::chrono::duration_cast<std::chrono::milliseconds>(now - difTime).count() > 150) {
		difTime = now;
		auto instrument = m_instrumentManager->getInstrument(m_instrumentIdx);

		if (instrument.m_samples.size() > 0) {
			instrument.play(0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::initInstruments()
{
	std::map<std::string, int> m_samples = {
		{"../../data/samples/piano/c.wav", OF_KEY_UP },
		{ "../../data/samples/piano/d.wav", OF_KEY_LEFT },
		{ "../../data/samples/piano/e.wav", OF_KEY_DOWN },
		{ "../../data/samples/piano/f.wav", OF_KEY_RIGHT }
	};

	m_instrumentManager->addInstrument("Piano");

	for (const auto sample : m_samples) {
		m_instrumentManager->getInstrument("Piano").addSample(sample.first, sample.second);
	}
}
