#include "Sample.h"

//--------------------------------------------------------------
CSample::CSample(std::string path, int shortcut, float volume, bool multiplay)
	: m_loopTimes(std::vector<int>()), m_shortcut(shortcut)
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

void CSample::setShortcut(int shortcut)
{
	m_shortcut = shortcut;
}

int CSample::getShortcut() const
{
	return m_shortcut;
}
