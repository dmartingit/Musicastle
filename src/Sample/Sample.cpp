#include "Sample.h"

//--------------------------------------------------------------
CSample::CSample(std::string path, float volume, bool multiplay)
	: m_loopTimes(std::vector<int>())
{
	m_player.load(path);
	m_player.setVolume(volume);
	m_player.setMultiPlay(multiplay);
}

//--------------------------------------------------------------
void CSample::loop(int beat)
{
	for (auto& time : m_loopTimes) {
		if (time == beat) {
			m_player.play();
		}
	}
}

// FIXME(dmartin): m_loopTimes elements does not get increased
//--------------------------------------------------------------
void CSample::addTime(int beat)
{
	m_loopTimes.push_back(beat);
}

//--------------------------------------------------------------
void CSample::clearTimes()
{
	m_loopTimes.clear();
}
