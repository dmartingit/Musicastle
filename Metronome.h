#pragma once
#include "ofMain.h"

class CMetronome {
public:
	CMetronome();
	~CMetronome() = default;

	void loop();

	void setEnabled(bool enabled);
	void setBeat(int beat);

	bool getEnabled();
	int getBeat();

private:
	bool m_enabled;
	int m_beat;
	ofSoundPlayer m_upbeatPlayer, m_downbeatPlayer;
};