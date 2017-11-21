#pragma once
#include "ofMain.h"

class CMetronome {
public:
	CMetronome();
	~CMetronome() = default;

	void loop();

	void setEnabled(bool enabled);

	bool getEnabled();

private:
	bool m_enabled;
	ofSoundPlayer m_upbeatPlayer, m_downbeatPlayer;
};