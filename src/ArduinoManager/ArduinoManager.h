#pragma once
#include "ofMain.h"
#include "ofArduino.h"

class CArduinoManager
{
public:
	CArduinoManager() = default;
	~CArduinoManager() = default;

	bool connect(const std::string device = "COM3");
	void disconnect();
	void loop();

	void setLED(bool enabled, int pin = 13);

	int getAnalog(int pin = 0);
	int getDigital(int pin = 0);

private:
	void setup(const int& version);

private:
	ofArduino m_arduino;
	bool m_setupFinished = false;
};