#include "LoopManager.h"

//--------------------------------------------------------------
CLoopManager::CLoopManager() {
	// setup metronom timer
	startThread();
}

void CLoopManager::setTimerCalled(std::shared_ptr<bool> timerCalled)
{
	m_timerCalled = timerCalled;
}

//--------------------------------------------------------------
void CLoopManager::threadedFunction() {
	while (isThreadRunning()) {
		// will synchronize timer intervall with the metronome's one
		if (!m_timerCalled.get() || !*m_timerCalled) {
			continue;
		}

		// TODO(dmartin): add samples of main app into our map and add its cued position
	};
}