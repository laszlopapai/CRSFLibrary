#pragma once
#include "Message.h"

namespace CRSF
{

class LinkStatistics
	: public Message
{
public:

	uint8_t upRSSIAnt1 = 1;
	uint8_t upRSSIAnt2 = 1;
	uint8_t upPackageSuccessRate = 1;
	int8_t upSNR = 100;
	uint8_t diversityActiveAntenna = 0;
	uint8_t rFMode = 2; // 2 = 50hz 5 = 150hz
	uint8_t upTXPower = 1;
	uint8_t downRSSI = 1;
	uint8_t downPackageSuccessRate = 100;
	int8_t downSNR = 100;

	std::string toString() const override {
		// TODO
		return "Link statistics";
	}

	MessageType getType() const override {
		return MessageType::CRSF_FRAMETYPE_LINK_STATISTICS;
	}


protected:
	void onPushByte() override {
		const auto latestByte = m_payload.size() - 1;

		if (latestByte == 0) {
			upRSSIAnt1 = m_payload[latestByte];
		}
		else if (latestByte == 1) {
			upRSSIAnt2 = m_payload[latestByte];
		}
		else if (latestByte == 2) {
			upPackageSuccessRate = m_payload[latestByte];
		}
		else if (latestByte == 3) {
			upSNR = m_payload[latestByte];
		}
		else if (latestByte == 4) {
			diversityActiveAntenna = m_payload[latestByte];
		}
		else if (latestByte == 5) {
			rFMode = m_payload[latestByte];
		}
		else if (latestByte == 6) {
			upTXPower = m_payload[latestByte];
		}
		else if (latestByte == 7) {
			downRSSI = m_payload[latestByte];
		}
		else if (latestByte == 8) {
			downPackageSuccessRate = m_payload[latestByte];
		}
		else if (latestByte == 9) {
			downSNR = m_payload[latestByte];
		}
	}

	void onResetPayload() override {
		pushByte(upRSSIAnt1);
		pushByte(upRSSIAnt2);
		pushByte(upPackageSuccessRate);
		pushByte(upSNR);
		pushByte(diversityActiveAntenna);
		pushByte(rFMode);
		pushByte(upTXPower);
		pushByte(downRSSI);
		pushByte(downPackageSuccessRate);
		pushByte(downSNR);
	}

};

}
