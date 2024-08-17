#pragma once
#include "Message.h"

namespace CRSF
{

class Attitude
	: public Message
{
	const uint8_t PayloadLength = 6;

public:

	float yaw;   // z
	float pitch; // y
	float roll;  // x

	std::string toString() const override {
		const auto rad2deg = 180.0f / 3.1415f;
		return "Attitude: roll: " + std::to_string(roll * rad2deg) + " pitch: " + std::to_string(pitch * rad2deg) + " yaw: " + std::to_string(yaw * rad2deg);

	}

	MessageType getType() const override {
		return CRSF_FRAMETYPE_ATTITUDE;
	}

protected:

	void onPushByte() override {
		if (m_payload.size() < PayloadLength) {
			return;
		}

		pitch = ((int8_t)m_payload[0 * 2 + 0] << 8) | ((int16_t)m_payload[0 * 2 + 1] << 0); // y
		pitch /= 10000;
		roll = ((int8_t)m_payload[1 * 2 + 0] << 8) | ((int16_t)m_payload[1 * 2 + 1] << 0); // x
		roll /= 10000;
		yaw = ((int8_t)m_payload[2 * 2 + 0] << 8) | ((int16_t)m_payload[2 * 2 + 1] << 0); // z
		yaw /= 10000;
	}

	void onResetPayload() override {
		m_payload.resize(PayloadLength);

		// TODO
	}

};

}
