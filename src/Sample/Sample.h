#pragma once
#include "ofMain.h"

class CSample {
public:
	CSample(std::string path, float volume = 0.75f, bool multiplay = true);
	~CSample() = default;

	void loop(int beat);
	void addTime(int beat);
	void clearTimes();

public:
	ofSoundPlayer m_player;

private:
	std::vector<int> m_loopTimes;
};