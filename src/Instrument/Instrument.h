#pragma once
#include "ofMain.h"

#include "..\Sample\Sample.h"

class CInstrument {
public:
	CInstrument(std::string name);
	~CInstrument() = default;

	void loop();
	void play(int idx);
	void addSample(std::string path, float volume = 0.75f, bool multiplay = true);
	void removeSample(int idx);
	void addTime(int sample);
	void clearTimes();

	void setRecord(bool record);
	void setName(std::string name);

	bool getRecord();
	std::string getName();

private:
	bool isIndexInBounds(int idx);

public:
	std::vector<CSample> m_samples;

private:
	std::string m_name;
	int m_beat, m_maxBeat;
	bool m_record;
};