#include "EventManager.h"

//--------------------------------------------------------------
CEventManager::CEventManager() 
	: m_bpm(120)
{
	// setup metronom timer
	this->setBpm(120);
	startThread();
}

//--------------------------------------------------------------
void CEventManager::setBpm(int value)
{
	m_bpm = value;
	m_timer.setPeriodicEvent(this->getBpmToNano(value));
}

//--------------------------------------------------------------
void CEventManager::setInstrumentManager(std::shared_ptr<CInstrumentManager> instrumentManager)
{
	m_instrumentManager = instrumentManager;
}

//--------------------------------------------------------------
void CEventManager::setMetronome(std::shared_ptr<CMetronome> metronome)
{
	m_metronome = metronome;
}

//--------------------------------------------------------------
int CEventManager::getBpm()
{
	return m_bpm;
}

//--------------------------------------------------------------
void CEventManager::threadedFunction() {
	while (isThreadRunning()) {
		// will run each beat
		m_timer.waitNext();

		if (m_metronome == nullptr || m_instrumentManager == nullptr) {
			continue;
		}

		m_metronome->loop();
		m_instrumentManager->loop();
	};
}

//--------------------------------------------------------------
void CEventManager::setTimer(uint64_t value)
{
	m_timer.setPeriodicEvent(value);
}

//--------------------------------------------------------------
uint64_t CEventManager::getBpmToNano(int value)
{
	return uint64_t(60000000000 / value);
}