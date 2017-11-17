#include "Metronom.h"

//--------------------------------------------------------------
CMetronom::CMetronom() : m_bpm(120), m_enabled(false) {
	// setup sound players
	m_upbeatPlayer.load("../../data/samples/metronom/metronome_upbeat.wav");
	m_downbeatPlayer.load("../../data/samples/metronom/metronome_downbeat.wav");
	m_upbeatPlayer.setVolume(0.75f);
	m_downbeatPlayer.setVolume(0.75f);


	// setup metronom timer
	m_timer.setPeriodicEvent(500000000); // this is 0.5 second in nanoseconds --> 120 BPM
	startThread();
}

//--------------------------------------------------------------
void CMetronom::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

//--------------------------------------------------------------
void CMetronom::setBpm(int value)
{
	m_bpm = value;
	m_timer.setPeriodicEvent(this->getBpmToNano(value));
}

//--------------------------------------------------------------
int CMetronom::getBpm()
{
	return m_bpm;
}

//--------------------------------------------------------------
bool CMetronom::getEnabled()
{
	return m_enabled;
}

//--------------------------------------------------------------
void CMetronom::threadedFunction() {
	static int metronomSoundSwitch = -1;

	while (isThreadRunning()) {
		m_timer.waitNext();

		// will run each beat
		if (!m_enabled) {
			continue;
		}

		++metronomSoundSwitch;

		if (metronomSoundSwitch < 1) {
			m_upbeatPlayer.play();
		}
		else if (metronomSoundSwitch < 4) {
			m_downbeatPlayer.play();
		}
		else {
			m_upbeatPlayer.play();
			metronomSoundSwitch = 0;
		}
	};
}

//--------------------------------------------------------------
void CMetronom::setTimer(uint64_t value)
{
	m_timer.setPeriodicEvent(value);
}

//--------------------------------------------------------------
uint64_t CMetronom::getBpmToNano(int value)
{
	return uint64_t(60000000000 / value);
}
