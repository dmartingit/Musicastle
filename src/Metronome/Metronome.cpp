#include "Metronome.h"

//--------------------------------------------------------------
CMetronome::CMetronome() 
	: m_enabled(false)
{
	// setup sound players
	m_upbeatPlayer.load("../../data/samples/metronom/metronome_upbeat.wav");
	m_downbeatPlayer.load("../../data/samples/metronom/metronome_downbeat.wav");
	m_upbeatPlayer.setVolume(0.75f);
	m_downbeatPlayer.setVolume(0.75f);
}

//--------------------------------------------------------------
void CMetronome::loop()
{
	static int metronomSoundSwitch = -1;

	if (!m_enabled) {
		return;
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
}

//--------------------------------------------------------------
void CMetronome::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

//--------------------------------------------------------------
bool CMetronome::getEnabled()
{
	return m_enabled;
}
