#include "ArduinoManager.h"

//--------------------------------------------------------------
bool CArduinoManager::connect(const std::string device)
{
	// connect to arduino
	if (!this->m_arduino.connect(device)) {
		return false;
	}

	// add setup listener
	ofAddListener(this->m_arduino.EInitialized, this, &CArduinoManager::setup);

	this->m_setupFinished = false;
	return true;
}

//--------------------------------------------------------------
void CArduinoManager::disconnect()
{
	// clean up
	ofRemoveListener(this->m_arduino.EInitialized, this, &CArduinoManager::setup);

	// cya
	this->m_arduino.disconnect();
}

//--------------------------------------------------------------
void CArduinoManager::loop()
{
	if (!this->m_arduino.isArduinoReady()) {
		return;
	}

	// update arduino
	this->m_arduino.update();
}

//--------------------------------------------------------------
void CArduinoManager::setLED(bool enabled, int pin)
{
	if (!this->m_setupFinished) {
		return;
	}

	if (enabled) {
		this->m_arduino.sendDigital(pin, ARD_LOW);
	}
	else {
		this->m_arduino.sendDigital(pin, ARD_HIGH);
	}
}

//--------------------------------------------------------------
int CArduinoManager::getAnalog(int pin)
{
	if (!this->m_setupFinished) {
		return 0;
	}

	return this->m_arduino.getAnalog(pin);
}

//--------------------------------------------------------------
void CArduinoManager::setup(const int & version)
{
	// remove setup listener
	ofRemoveListener(this->m_arduino.EInitialized, this, &CArduinoManager::setup);

	// add led
	this->m_arduino.sendDigitalPinMode(13, ARD_OUTPUT);

	// add touch sensor
	this->m_arduino.sendAnalogPinReporting(0, ARD_ANALOG);

	// enable all features like analog reading etc.
	this->m_setupFinished = true;
}
