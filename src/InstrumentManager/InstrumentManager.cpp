#include "InstrumentManager.h"

//--------------------------------------------------------------
void CInstrumentManager::loop(int time)
{
	for (auto instrument : m_instruments) {
		instrument.loop(time);
	}
}

//--------------------------------------------------------------
void CInstrumentManager::addInstrument(std::string name)
{
	m_instruments.push_back(CInstrument(name));
}

//--------------------------------------------------------------
void CInstrumentManager::removeInstrument(int idx)
{
	if (this->isIndexInBounds(idx)) {
		m_instruments.erase(m_instruments.begin() + idx);
	}
}

//--------------------------------------------------------------
int CInstrumentManager::getInstrumentSize()
{
	return m_instruments.size();
}

//--------------------------------------------------------------
CInstrument& CInstrumentManager::getInstrument(std::string name)
{
	for (auto& instrument : m_instruments) {
		if (name == instrument.getName()) {
			return instrument;
		}
	}
	return CInstrument("");
}

//--------------------------------------------------------------
CInstrument& CInstrumentManager::getInstrument(int idx)
{
	if (this->isIndexInBounds(idx)) {
		return m_instruments.at(idx);
	}
	return CInstrument("");
}

//--------------------------------------------------------------
bool CInstrumentManager::isIndexInBounds(int idx)
{
	if ((idx < 0) || (m_instruments.size() < idx + 1)) {
		return false;
	}
	
	return true;
}
