#pragma once
#include "ofMain.h"

class CMetronome : public ofThread {
public:
	CMetronome();

	void setEnabled(bool enabled);
	void setBpm(int value);

	int getBpm();
	bool getEnabled();
	std::shared_ptr<bool> getTimerCalled();

private:
	void threadedFunction();
	void setTimer(uint64_t value);
	uint64_t getBpmToNano(int value);

private:
	int m_bpm;
	bool m_enabled;
	std::shared_ptr<bool> m_timerCalled;
	ofTimer m_timer;
	ofSoundPlayer m_upbeatPlayer, m_downbeatPlayer;
};