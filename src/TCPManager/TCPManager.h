#pragma once
#include "ofMain.h"
#include "ofxNetwork\src\ofxNetwork.h"

class CTCPManager
{
public:
	CTCPManager() = default;
	~CTCPManager() = default;

public:
	ofxTCPServer m_tcpServer;
};