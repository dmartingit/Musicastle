#pragma once
#include "ofMain.h"

class CMetronom : public ofThread {
public:
	CMetronom();

	void setEnabled(bool enabled);
	void setBpm(int value);

	int getBpm();
	bool getEnabled();

private:
	void threadedFunction();
	void setTimer(uint64_t value);
	uint64_t getBpmToNano(int value);

private:
	int m_bpm;
	bool m_enabled;
	ofTimer m_timer;
	ofSoundPlayer m_upbeatPlayer, m_downbeatPlayer;
};