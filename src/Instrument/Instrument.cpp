#include "Instrument.h"

//--------------------------------------------------------------
CInstrument::CInstrument(std::string name) 
	: m_name(name), m_beat(-1), m_maxBeat(-1), m_record(false)
{
}

//--------------------------------------------------------------
void CInstrument::loop()
{
	if (m_record) {
		++m_beat;
		auto now = std::chrono::high_resolution_clock::now();
		m_lastTimeBetweenBeats = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastBeatTime).count() / 2;
		m_lastBeatTime = now;
	}
	else {
		if (m_beat < m_maxBeat) {
			++m_beat;
		}
		else {
			m_beat = 0;
		}
	}

	if (m_maxBeat == -1) {
		return;
	}

	for (auto& sample : m_samples) {
		sample.loop(m_beat);
	}
}

//--------------------------------------------------------------
void CInstrument::play(int idx)
{
	if (this->isIndexInBounds(idx)) {
		if (m_record) {
			this->addTime(idx);
		}

		m_samples.at(idx).m_player.play();
	}
}

//--------------------------------------------------------------
void CInstrument::addSample(std::string path, int shortcut, float volume, bool multiplay)
{
	m_samples.push_back(CSample(path, shortcut, volume, multiplay));
}

//--------------------------------------------------------------
void CInstrument::removeSample(int idx)
{
	if (this->isIndexInBounds(idx)) {
		m_samples.erase(m_samples.begin() + idx);
	}
}

//--------------------------------------------------------------
void CInstrument::addTime(int sample)
{
	if (this->isIndexInBounds(sample)) {
		auto now = std::chrono::high_resolution_clock::now();
		auto beat = m_beat;
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastBeatTime).count() > m_lastTimeBetweenBeats) {
			++beat;
		}
		m_samples.at(sample).addTime(beat);
	}
}

//--------------------------------------------------------------
void CInstrument::clearTimes()
{
	for (auto& sample : m_samples) {
		sample.clearTimes();
	}
}

//--------------------------------------------------------------
void CInstrument::setRecord(bool record)
{
	m_record = record;

	if (record) {
		m_beat = -1;
		m_maxBeat = -1;
	}
	else {
		m_maxBeat = m_beat;
	}
}

//--------------------------------------------------------------
void CInstrument::setName(std::string name)
{
	m_name = name;
}

//--------------------------------------------------------------
bool CInstrument::getRecord()
{
	return m_record;
}

//--------------------------------------------------------------
std::string CInstrument::getName()
{
	return m_name;
}

//--------------------------------------------------------------
bool CInstrument::isIndexInBounds(int idx)
{
	if ((idx < 0) || (m_samples.size() < idx + 1)) {
		return false;
	}

	return true;
}
