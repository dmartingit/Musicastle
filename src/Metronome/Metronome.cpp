#include "Metronome.h"

//--------------------------------------------------------------
CMetronome::CMetronome() : m_bpm(120), m_enabled(false), m_timerCalled(std::make_shared<bool>(false)) {
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
void CMetronome::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

//--------------------------------------------------------------
void CMetronome::setBpm(int value)
{
	m_bpm = value;
	m_timer.setPeriodicEvent(this->getBpmToNano(value));
}

//--------------------------------------------------------------
int CMetronome::getBpm()
{
	return m_bpm;
}

//--------------------------------------------------------------
bool CMetronome::getEnabled()
{
	return m_enabled;
}

std::shared_ptr<bool> CMetronome::getTimerCalled()
{
	return m_timerCalled;
}

//--------------------------------------------------------------
void CMetronome::threadedFunction() {
	static int metronomSoundSwitch = -1;

	while (isThreadRunning()) {
		if (m_timerCalled) {
			*m_timerCalled = false;
		}
		m_timer.waitNext();
		if (m_timerCalled) {
			*m_timerCalled = true;
		}

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
void CMetronome::setTimer(uint64_t value)
{
	m_timer.setPeriodicEvent(value);
}

//--------------------------------------------------------------
uint64_t CMetronome::getBpmToNano(int value)
{
	return uint64_t(60000000000 / value);
}
