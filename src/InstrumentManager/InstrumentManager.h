#pragma once
#include "ofMain.h"

#include "..\Instrument\Instrument.h"

class CInstrumentManager {
public:
	CInstrumentManager() = default;
	~CInstrumentManager() = default;

	void loop();
	void addInstrument(std::string name);
	void removeInstrument(int idx);
	
	int getInstrumentSize();
	CInstrument& getInstrument(std::string name);
	CInstrument& getInstrument(int idx);

private:
	bool isIndexInBounds(int idx);

private:
	std::vector<CInstrument> m_instruments;
};