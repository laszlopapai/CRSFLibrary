#pragma once
#include "Message.h"

namespace CRSF
{

class Heartbeat
	: public Message
{
public:
	static const MessageType Type = CRSF_FRAMETYPE_HEARTBEAT;

	Address sourceAddress;

	std::string toString() const override {
		return "Hart beat to: " + std::to_string((uint16_t)m_payload[0]) + " from: " + std::to_string((uint16_t)m_payload[1]);
	}

	MessageType getType() const override {
		return MessageType::CRSF_FRAMETYPE_HEARTBEAT;
	}

protected:

	void onPushByte() override {
		if (m_payload.size() > 2) {
			sourceAddress = (Address)m_payload[1];
		}
	}

	void onResetPayload() override {
		pushByte(0);
		pushByte(sourceAddress);
	}

};

}
