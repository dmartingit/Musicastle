#pragma once
#include "ofMain.h"

class CSample {
public:
	CSample(std::string path, int shortcut = -1, float volume = 0.75f, bool multiplay = true);
	~CSample() = default;

	void loop(int beat);
	void addTime(int beat);
	void clearTimes();

	void setShortcut(int shortcut);

	int getShortcut() const;

public:
	ofSoundPlayer m_player;

private:
	std::vector<int> m_loopTimes;
	int m_shortcut;
};