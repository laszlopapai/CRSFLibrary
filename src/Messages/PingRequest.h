#pragma once
#include "Message.h"

namespace CRSF
{

class PingRequest
	: public Message
{
	const uint8_t PayloadLength = 2;

public:

	Address destinationAddress;
	Address sourceAddress;

	std::string toString() const override {
		return "Ping request to: " + std::to_string((uint16_t)m_payload[0]) + " from: " + std::to_string((uint16_t)m_payload[1]);
	}

	MessageType getType() const override {
		return MessageType::CRSF_FRAMETYPE_DEVICE_PING;
	}

protected:

	void onPushByte() override {
		if (m_payload.size() < PayloadLength) {
			return;
		}
		destinationAddress = (Address)m_payload[0];
		sourceAddress = (Address)m_payload[1];
	}

	void onResetPayload() override {
		pushByte(destinationAddress);
		pushByte(sourceAddress);
	}

};

}
