#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
	// use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.

	noteC.load( "../../data/samples/piano/c.wav" );
	noteD.load( "../../data/samples/piano/d.wav" );
	noteE.load( "../../data/samples/piano/e.wav" );
	noteF.load( "../../data/samples/piano/f.wav" );
	noteC.setVolume( 0.75f );
	noteD.setVolume( 0.75f );
	noteE.setVolume( 0.75f );
	noteF.setVolume( 0.75f );
	font.load( "../../data/fonts/Sudbury_Basin_3D.ttf", 32 );
	noteC.setMultiPlay( true );
	noteD.setMultiPlay( true );
	noteE.setMultiPlay( true );
	noteF.setMultiPlay( true );
}

//--------------------------------------------------------------
void ofApp::update() {

	ofBackground( 255, 255, 255 );

	// update the sound playing system:
	ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw() {

	// draw the background colors:
	float widthDiv = ofGetWidth() / 4.0f;
	ofSetHexColor( 0xeeeeee );
	ofDrawRectangle( 0, 0, widthDiv, ofGetHeight() );
	ofSetHexColor( 0xffffff );
	ofDrawRectangle( widthDiv, 0, widthDiv, ofGetHeight() );
	ofSetHexColor( 0xeeeeee );
	ofDrawRectangle( widthDiv * 2, 0, widthDiv, ofGetHeight() );
	ofSetHexColor( 0xffffff );
	ofDrawRectangle( widthDiv * 3, 0, widthDiv, ofGetHeight() );

	//---------------------------------- noteC:
	if ( noteC.isPlaying() ) ofSetHexColor( 0xFF0000 );
	else ofSetHexColor( 0x000000 );
	font.drawString( "C !!", 50, 50 );

	ofSetHexColor( 0x000000 );
	string tempStr = "click to play (Up Arrow)\npan: " + ofToString( noteC.getPan() );
	ofDrawBitmapString( tempStr, 20, ofGetHeight() - 50 );

	//---------------------------------- noteD:
	if ( noteD.isPlaying() ) ofSetHexColor( 0xFF0000 );
	else ofSetHexColor( 0x000000 );
	font.drawString( "D !!", widthDiv + 50, 50 );

	ofSetHexColor( 0x000000 );
	tempStr = "click to play (Left Arrow)\npan: " + ofToString( noteD.getPan() );
	ofDrawBitmapString( tempStr, widthDiv + 20, ofGetHeight() - 50 );

	//---------------------------------- noteE:
	if ( noteE.isPlaying() ) ofSetHexColor( 0xFF0000 );
	else ofSetHexColor( 0x000000 );
	font.drawString( "E !!", widthDiv * 2 + 50, 50 );

	ofSetHexColor( 0x000000 );
	tempStr = "click to play (Down Arrow)\npan: " + ofToString( noteE.getPan() );
	ofDrawBitmapString( tempStr, widthDiv * 2 + 20, ofGetHeight() - 50 );

	//---------------------------------- noteF:
	if ( noteF.isPlaying() ) ofSetHexColor( 0xFF0000 );
	else ofSetHexColor( 0x000000 );
	font.drawString( "F !!", widthDiv * 3 + 50, 50 );

	ofSetHexColor( 0x000000 );
	tempStr = "click to play (Right Arrow)\npan: " + ofToString( noteF.getPan() );
	ofDrawBitmapString( tempStr, widthDiv * 3 + 20, ofGetHeight() - 50 );

}

//--------------------------------------------------------------
void ofApp::keyPressed( int key ) {

	switch ( key )
	{
	case OF_KEY_UP:
		noteC.play();
		break;
	case OF_KEY_LEFT:
		noteD.play();
		break;
	case OF_KEY_DOWN:
		noteE.play();
		break;
	case OF_KEY_RIGHT:
		noteF.play();
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased( int key ) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved( int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged( int x, int y, int button ) {

}

//--------------------------------------------------------------
void ofApp::mousePressed( int x, int y, int button ) {
	float widthStep = ofGetWidth() / 4.0f;
	if ( x < widthStep ) {
		noteC.play();
		noteC.setPan( ofMap( x, 0, widthStep, -1, 1, true ) );
	}
	else if ( x >= widthStep && x < widthStep * 2 ) {
		noteD.play();
		noteD.setPan( ofMap( x, widthStep, widthStep * 2, -1, 1, true ) );
	}
	else if ( x >= widthStep * 2 && x < widthStep * 3 ) {
		noteE.play();
		noteE.setPan( ofMap( x, widthStep * 2, widthStep * 3, -1, 1, true ) );
	}
	else {
		noteF.play();
		noteF.setPan( ofMap( x, widthStep * 3, widthStep * 4, -1, 1, true ) );
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased( int x, int y, int button ) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered( int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseExited( int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::windowResized( int w, int h ) {

}

//--------------------------------------------------------------
void ofApp::gotMessage( ofMessage msg ) {

}

//--------------------------------------------------------------
void ofApp::dragEvent( ofDragInfo dragInfo ) {

}
