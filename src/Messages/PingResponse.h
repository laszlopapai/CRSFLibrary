#pragma once
#include "Message.h"
#include <string>

namespace CRSF
{

class PingResponse
	: public Message
{
public:

	Address destinationAddress = Address::CRSF_ADDRESS_FLIGHT_CONTROLLER;
	Address sourceAddress = Address::CRSF_ADDRESS_CRSF_RECEIVER;
	std::string displayName = "test";  // null terminated
	std::string serialNumber = "ELRS"; // 4 character "ELRS"
	uint32_t hardwareVersion = 0;
	uint32_t softwareVersion = 0;
	uint8_t parameterCount = 0;
	uint8_t parameterProtocolVersion = 0;

	std::string toString() const override {
		// TODO
		return "Ping response";
	}

	MessageType getType() const override {
		return MessageType::CRSF_FRAMETYPE_DEVICE_INFO;
	}

protected:

	void onPushByte() override {
		// TODO
	}

	void onResetPayload() override {
		uint8_t* data;
		uint32_t uint;

		pushByte(destinationAddress);
		pushByte(sourceAddress);

		for (auto c : displayName) {
			pushByte(c);
		}
		m_payload.push_back(0);

		for (auto c : serialNumber) {
			pushByte(c);
		}

		uint = endianSwap(hardwareVersion);
		data = reinterpret_cast<uint8_t*>(&uint);
		for (int i = 0; i < sizeof(uint32_t); i++) {
			pushByte(data[i]);
		}

		uint = endianSwap(softwareVersion);
		data = reinterpret_cast<uint8_t*>(&uint);
		for (int i = 0; i < sizeof(uint32_t); i++) {
			pushByte(data[i]);
		}

		pushByte(parameterCount);
		pushByte(parameterProtocolVersion);
	}

};

}
