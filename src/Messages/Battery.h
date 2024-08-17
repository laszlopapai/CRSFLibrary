#pragma once
#include "Message.h"

namespace CRSF
{

class Battery
	: public Message
{
	const uint8_t PayloadLength = 8;

public:

	float voltage;
	float current;
	float usedCapacity;
	float remaining;

	std::string toString() const override {
		return "Battery: " + std::to_string(voltage) + "v " + std::to_string(current) + "A Used: " + std::to_string(usedCapacity) + "mAh " + std::to_string(remaining) + "%";
	}

	MessageType getType() const override {
		return CRSF_FRAMETYPE_BATTERY_SENSOR;
	}

protected:

	void onPushByte() override {
		if (m_payload.size() < PayloadLength) {
			return;
		}

		voltage = ((int8_t)m_payload[0] << 8) | ((int16_t)m_payload[1] << 0);
		voltage *= 0.1f;

		current = ((int8_t)m_payload[2] << 8) | ((int16_t)m_payload[3] << 0);
		current *= 0.1f;

		usedCapacity = ((int8_t)m_payload[4] << 16) | ((int8_t)m_payload[5] << 8) | ((int32_t)m_payload[6] << 0);
		usedCapacity *= 0.1f;

		remaining = (int8_t)m_payload[7];
	}

	void onResetPayload() override {
		m_payload.resize(PayloadLength);
		// TODO
	}

};

}
