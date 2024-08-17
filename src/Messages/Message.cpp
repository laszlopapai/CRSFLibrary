#include "Message.h"

using namespace CRSF;

void Message::pushByte(DataByte byte) {
	if (m_payload.empty()) {
		m_crc = crc8(0, getType());
	}
	m_payload.push_back(byte);
	m_crc = crc8(m_crc, byte);
	if (!m_reset) {
		onPushByte();
	}
}

const DataBuffer Message::getBytes() {
	DataBuffer message;
	resetPayload();
	message.push_back(Address::CRSF_ADDRESS_FLIGHT_CONTROLLER);
	message.push_back(m_payload.size() + 2);
	message.push_back(getType());
	for (const auto byte : m_payload) {
		message.push_back(byte);
	}
	message.push_back(m_crc);

	return message;
}

void Message::resetPayload() {
	m_payload.clear();
	m_crc = crc8(0, getType());
	m_reset = true;
	onResetPayload();
	m_reset = false;
}

DataByte Message::crc8(DataByte crc, DataByte a) {
	crc ^= a;
	for (int ii = 0; ii < 8; ++ii) {
		if (crc & 0x80) {
			crc = (crc << 1) ^ 0xD5;
		}
		else {
			crc = crc << 1;
		}
	}
	return crc;
}
