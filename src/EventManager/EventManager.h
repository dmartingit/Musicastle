#pragma once
#include "ofMain.h"

#include "..\InstrumentManager\InstrumentManager.h"
#include "..\Metronome\Metronome.h"

class CEventManager : public ofThread {
public:
	CEventManager();

	void setBpm(int value);
	void setInstrumentManager(std::shared_ptr<CInstrumentManager> instrumentManager);
	void setMetronome(std::shared_ptr<CMetronome> metronome);

	int getBpm();

private:
	void threadedFunction();

	void setTimer(uint64_t value);
	uint64_t getBpmToNano(int value);

private:
	int m_bpm;
	ofTimer m_timer;

	std::shared_ptr<CInstrumentManager> m_instrumentManager;
	std::shared_ptr<CMetronome> m_metronome;
};