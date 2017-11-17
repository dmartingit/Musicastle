#pragma once
#include "ofMain.h"

class CLoopManager : public ofThread {
public:
	class CLoopManager();

	void setTimerCalled(std::shared_ptr<bool> timerCalled);

private:
	void threadedFunction();

private:
	std::shared_ptr<bool> m_timerCalled;
	// contains sample id and a vector with all the time positions when the sample should be played
	std::map<int, std::vector<int>> m_sampleTimeMap;
};