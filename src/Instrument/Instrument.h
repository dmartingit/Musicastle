#pragma once
#include "ofMain.h"

class CInstrument {
public:
	CInstrument(std::string name = "");
	~CInstrument() = default;

	void loop(int time);
	void play(int idx);
	void addSample(std::string path, float volume = 0.75f, bool multiplay = true);
	void removeSample(int idx);
	void addTime(int sample, int time);
	void clearTimes();

	void setName(std::string name);

	std::string getName();

private:
	bool isIndexInBounds(int idx);

public:
	std::vector<ofSoundPlayer> m_samplePlayer;

private:
	std::string m_name;
	std::vector<std::vector<int>> m_sampleLoopTimes;
};