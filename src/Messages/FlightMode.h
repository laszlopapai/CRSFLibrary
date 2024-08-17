#pragma once
#include "Message.h"
#include <string>

namespace CRSF
{

class FlightMode
	: public Message
{
public:

	std::string flightMode;

	std::string toString() const override {
		return "Flight mode: " + flightMode;
	}

	MessageType getType() const override {
		return MessageType::CRSF_FRAMETYPE_FLIGHT_MODE;
	}

protected:

	void onPushByte() override {
		const auto latestByte = m_payload.size() - 1;
		if (m_payload[latestByte] != '\0') {
			return;
		}
		flightMode = std::string((char*)m_payload.data());
	}

	void onResetPayload() override {
		m_payload.resize(flightMode.size() + 1);
		// TODO
	}

};

}
