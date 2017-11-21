#include "Instrument.h"

//--------------------------------------------------------------
CInstrument::CInstrument(std::string name) 
	: m_name(name)
{
}

//--------------------------------------------------------------
void CInstrument::loop(int time)
{
	for (auto i = 0; i < m_sampleLoopTimes.size(); ++i) {
		for (auto loopTime : m_sampleLoopTimes.at(i)) {
			if (loopTime == time) {
				m_samplePlayer.at(i).play();
			}
		}
	}
}

//--------------------------------------------------------------
void CInstrument::play(int idx)
{
	if (this->isIndexInBounds(idx)) {
		m_samplePlayer.at(idx).play();
	}
}

//--------------------------------------------------------------
void CInstrument::addSample(std::string path, float volume, bool multiplay)
{
	ofSoundPlayer player;
	player.load(path);
	player.setVolume(volume);
	player.setMultiPlay(multiplay);

	m_samplePlayer.push_back(player);
	m_sampleLoopTimes.push_back(std::vector<int>());
}

//--------------------------------------------------------------
void CInstrument::removeSample(int idx)
{
	if (this->isIndexInBounds(idx)) {
		m_samplePlayer.erase(m_samplePlayer.begin() + idx);
		m_sampleLoopTimes.erase(m_sampleLoopTimes.begin() + idx);
	}
}

//--------------------------------------------------------------
void CInstrument::addTime(int sample, int time)
{
	if (this->isIndexInBounds(sample)) {
		m_sampleLoopTimes.at(sample).push_back(time);
	}
}

//--------------------------------------------------------------
void CInstrument::clearTimes()
{
	for (auto sample : m_sampleLoopTimes) {
		sample.clear();
	}
}

//--------------------------------------------------------------
void CInstrument::setName(std::string name)
{
	m_name = name;
}

//--------------------------------------------------------------
std::string CInstrument::getName()
{
	return m_name;
}

//--------------------------------------------------------------
bool CInstrument::isIndexInBounds(int idx)
{
	if ((idx < 0) || (m_samplePlayer.size() < idx + 1) || (m_sampleLoopTimes.size() < idx + 1)) {
		return false;
	}

	return true;
}
