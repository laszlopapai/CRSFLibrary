#pragma once
#include <vector>
#include <string>

namespace CRSF
{

enum Address : uint8_t
{
	CRSF_ADDRESS_FLIGHT_CONTROLLER = 0xC8,
	CRSF_ADDRESS_CRSF_RECEIVER = 0xEC
};

enum MessageType : uint8_t
{
	CRSF_FRAMETYPE_VARIO = 0x07,
	CRSF_FRAMETYPE_BATTERY_SENSOR = 0x08,
	CRSF_FRAMETYPE_ATTITUDE = 0x1E,
	CRSF_FRAMETYPE_FLIGHT_MODE = 0x21,
	CRSF_FRAMETYPE_RC_CHANNELS_PACKED = 0x16,
	CRSF_FRAMETYPE_LINK_STATISTICS = 0x14,
	CRSF_FRAMETYPE_HEARTBEAT = 0x0B,
	CRSF_FRAMETYPE_DEVICE_INFO = 0x29,
	CRSF_FRAMETYPE_DEVICE_PING = 0x28
};

using DataByte = uint8_t;
using DataBuffer = std::vector<DataByte>;

class Message
{

public:

	void pushByte(DataByte byte);

	const DataBuffer getBytes();

	void resetPayload();

	DataByte getCRC() const {
		return m_crc;
	}

	virtual std::string toString() const = 0;

	virtual MessageType getType() const = 0;

protected:
	static DataByte crc8(DataByte crc, DataByte a);

	template <typename T>
	T endianSwap(T u) {
		static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

		union
		{
			T u;
			unsigned char u8[sizeof(T)];
		} source, dest;

		source.u = u;

		for (size_t k = 0; k < sizeof(T); k++)
			dest.u8[k] = source.u8[sizeof(T) - k - 1];

		return dest.u;
	}

	virtual void onResetPayload() = 0;

	virtual void onPushByte() = 0;

protected:
	bool m_reset{ false };
	DataByte m_crc;
	DataBuffer m_payload;
};

}
