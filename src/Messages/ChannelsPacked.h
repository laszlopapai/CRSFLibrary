#pragma once
#include <algorithm>
#include "Message.h"

namespace CRSF
{

class ChannelsPacked
	: public Message
{
	const uint8_t ValueBits = 11;
	const uint8_t PayloadLength = ValueBits * 16 / 8;

public:

	uint16_t channel[16];

	std::string toString() const override {
		std::string s = "Channel package: ";
		for (int i = 0; i < 6; i++) {
			s += "Ch" + std::to_string(i) + ": " + std::to_string(channel[i]) + " ";
		}
		return s;
	}

	MessageType getType() const override {
		return CRSF_FRAMETYPE_RC_CHANNELS_PACKED;
	}

protected:

	void onPushByte() override {
		if (m_payload.size() < PayloadLength) {
			return;
		}

		const uint16_t numOfChannels = sizeof(channel) / sizeof(channel[0]);
		const uint16_t valueMask = (1 << ValueBits) - 1;

		uint32_t channelValue = 0;
		auto bitPtr = 0;
		auto bytePtr = 0;
		for (auto i = 0; i < numOfChannels; ++i) {

			while (bitPtr < ValueBits) {
				channelValue |= ((uint16_t)m_payload[bytePtr++]) << bitPtr;
				bitPtr += 8;
			}

			channel[i] = channelValue & valueMask;
			channelValue >>= ValueBits;
			bitPtr -= ValueBits;
		}
	}

	void onResetPayload() override {
		const uint16_t numOfChannels = sizeof(channel) / sizeof(channel[0]);
		const uint16_t numOfBytes = numOfChannels * ValueBits / 8;
		const uint16_t valueMask = (1 << ValueBits) - 1;

		uint16_t channelValue = 0;
		auto channelPtr = 0;
		auto availableBits = 0;
		for (auto i = 0; i < numOfBytes; ++i) {
			uint8_t byteValue = 0;
			auto bitPtr = 0;

			while (bitPtr < 8) {
				if (availableBits == 0) {
					channelValue = channel[channelPtr++];
					availableBits += ValueBits;
				}
				byteValue |= (channelValue >> (ValueBits - availableBits)) << bitPtr;
				auto bitCount = std::min(availableBits, 8 - bitPtr);
				availableBits -= bitCount;
				bitPtr += bitCount;
			}

			pushByte(byteValue);
		}
	}

};

}
