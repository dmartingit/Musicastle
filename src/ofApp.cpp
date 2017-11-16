#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
	// use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.

	m_samples = {
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

	font.load("../../data/fonts/Sudbury_Basin_3D.ttf", 32);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofBackground(255, 255, 255);

	// update the sound playing system:
	ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw() {

	float widthDiv = ofGetWidth() / m_samples.size();
	string tmpStr;
	for (auto i = 0; i < m_samples.size(); ++i) {
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
		font.drawString("Sample !!", (widthDiv * i) + 50, 50);

		ofSetHexColor(0x000000);
		tmpStr = "click to play (Left Arrow)\npan: " + ofToString(sample.getPan());
		ofDrawBitmapString(tmpStr, (widthDiv * i) + 20, ofGetHeight() - 50);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key)
	{
	case OF_KEY_UP:
		m_vecSoundPlayer.at(0).play();
		break;
	case OF_KEY_LEFT:
		m_vecSoundPlayer.at(1).play();
		break;
	case OF_KEY_DOWN:
		m_vecSoundPlayer.at(2).play();
		break;
	case OF_KEY_RIGHT:
		m_vecSoundPlayer.at(3).play();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	float widthStep = ofGetWidth() / m_samples.size();
	for (auto i = 0; i < m_samples.size(); ++i) {
		if (x >= (widthStep * i) && x < (widthStep * (i + 1))) {
			auto sample = m_vecSoundPlayer.at(i);
			sample.play();
			sample.setPan(ofMap(x, (widthStep * i), (widthStep * (i + 1)), -1, 1, true));
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
