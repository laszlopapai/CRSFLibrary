#pragma once
#include "Message.h"

namespace CRSF
{

class VerticalSpeed
	: public Message
{
    const uint8_t PayloadLength = 2;

public:

	float verticalSpeed;

	std::string toString() const override {
		return "Vertical speed: " + std::to_string(verticalSpeed) + "m/s";
	}

	MessageType getType() const override {
		return MessageType::CRSF_FRAMETYPE_VARIO;
	}

protected:

	void onPushByte() override {
		if (m_payload.size() < PayloadLength) {
			return;
		}
		const auto data = ((int8_t)m_payload[0] << 8) | ((int16_t)m_payload[1] << 0);
		verticalSpeed = data * 0.01f;
	}

	void onResetPayload() override {
		uint16_t data = verticalSpeed * 100.0f;
		pushByte((data & 0xFF00) >> 8);
		pushByte((data & 0x00FF) >> 0);
	}

};

}
