#include "CRSFReader.h"
#include "Messages\VerticalSpeed.h"
#include "Messages\Battery.h"
#include "Messages\Attitude.h"
#include "Messages\FlightMode.h"
#include "Messages\ChannelsPacked.h"
#include "Messages\Heartbeat.h"
#include "Messages\LinkStatistics.h"
#include "Messages\PingRequest.h"
#include "Messages\PingResponse.h"

using namespace CRSF;

size_t CRSFReader::pushByte(DataByte* bytes, size_t length) {
	size_t okBytes = 0;
	for (size_t i = 0; i < length; i++) {
		if (pushByte(bytes[i])) {
			okBytes++;
		}
	}
	return okBytes;
}

size_t CRSFReader::pushByte(DataBuffer bytes) {
	size_t okBytes = 0;
	for (const auto byte : bytes) {
		if (pushByte(byte)) {
			okBytes++;
		}
	}
	return okBytes;
}

bool CRSFReader::pushByte(DataByte byte) {
	if (!m_sync) {
		if (byte == Address::CRSF_ADDRESS_FLIGHT_CONTROLLER) {
			m_sync = true;
			return true;
		}
		return false;
	}
	else if (!m_message && m_length == 0) {
		if (byte == 0) {
			reset();
			return false;
		}
		m_length = byte;
		return true;
	}
	else if (!m_message && m_length > 0) {
		m_message = createMessage((MessageType)byte);
		m_length--;
		if (!m_message) {
			reset();
			return false;
		}
		return true;
	}
	else if (m_message && m_length > 1) {
		m_message->pushByte(byte);
		m_length--;
		return true;
	}
	else if (m_message && m_length == 1) {
		const auto crcOk = byte == m_message->getCRC();
		const auto type = m_message->getType();
		if (m_genericHandler) {
			m_genericHandler(m_message, crcOk);
		}
		if (m_handlers.contains(type)) {
			m_handlers[type](m_message, crcOk);
		}

		reset();
		return true;
	}

	reset();
	return false;
}

void CRSFReader::reset() {
	m_sync = false;
	m_length = 0;
	m_message.reset();
}

std::shared_ptr<Message> CRSFReader::createMessage(MessageType type) {

	switch (type)
	{
	case MessageType::CRSF_FRAMETYPE_VARIO:
		return std::make_shared<VerticalSpeed>();

	case MessageType::CRSF_FRAMETYPE_BATTERY_SENSOR:
		return std::make_shared<Battery>();

	case MessageType::CRSF_FRAMETYPE_ATTITUDE:
		return std::make_shared<Attitude>();

	case MessageType::CRSF_FRAMETYPE_FLIGHT_MODE:
		return std::make_shared<FlightMode>();

	case MessageType::CRSF_FRAMETYPE_RC_CHANNELS_PACKED:
		return std::make_shared<ChannelsPacked>();

	case MessageType::CRSF_FRAMETYPE_HEARTBEAT:
		return std::make_shared<Heartbeat>();

	case MessageType::CRSF_FRAMETYPE_LINK_STATISTICS:
		return std::make_shared<LinkStatistics>();

	case MessageType::CRSF_FRAMETYPE_DEVICE_PING:
		return std::make_shared<PingRequest>();

	case MessageType::CRSF_FRAMETYPE_DEVICE_INFO:
		return std::make_shared<PingResponse>();

	default:
		return nullptr;
	}
}
