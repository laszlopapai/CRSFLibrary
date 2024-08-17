#include <CRSFReader.h>
#include <Messages/Attitude.h>
#include <Messages/Battery.h>
#include <Messages/ChannelsPacked.h>
#include <Messages/FlightMode.h>
#include <Messages/Heartbeat.h>
#include <Messages/LinkStatistics.h>
#include <Messages/PingRequest.h>
#include <Messages/PingResponse.h>
#include <Messages/VerticalSpeed.h>

int main() {

	CRSF::CRSFReader reader;
	std::shared_ptr<CRSF::Message> sentMessage;

	reader.setGenericMessageHandler([&](const std::shared_ptr<CRSF::Message> msg, bool crcOk) {
		const auto msgOk = sentMessage->toString() == msg->toString();
		printf("%s\n%s\nCRC: %d Message: %d\n",
			sentMessage->toString().c_str(),
			msg->toString().c_str(),
			crcOk,
			msgOk
		);
	});
	
	// Attitude
	{
		auto msg = std::make_shared<CRSF::Attitude>();
		msg->pitch = 1;
		msg->roll = 2;
		msg->yaw = 3;
		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Battery
	{
		auto msg = std::make_shared<CRSF::Battery>();
		msg->current = 1;
		msg->remaining = 2;
		msg->usedCapacity = 3;
		msg->voltage = 4;
		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Channel
	{
		auto msg = std::make_shared<CRSF::ChannelsPacked>();

		for (int i = 0; i < 16; i++) {
			msg->channel[i] = i * 100;
		}

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Flight mode
	{
		auto msg = std::make_shared<CRSF::FlightMode>();

		msg->flightMode = "test";

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Heartbeat
	{
		auto msg = std::make_shared<CRSF::Heartbeat>();

		msg->sourceAddress = CRSF::Address::CRSF_ADDRESS_CRSF_RECEIVER;

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// LinkStat
	{
		auto msg = std::make_shared<CRSF::LinkStatistics>();

		msg->diversityActiveAntenna = 1;
		msg->downPackageSuccessRate = 2;
		msg->downRSSI = 3;
		msg->downSNR = 4;
		msg->rFMode = 5;
		msg->upPackageSuccessRate = 6;
		msg->upRSSIAnt1 = 7;
		msg->upRSSIAnt2 = 8;
		msg->upSNR = 9;
		msg->upTXPower = 10;

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Ping request
	{
		auto msg = std::make_shared<CRSF::PingRequest>();

		msg->destinationAddress = CRSF::Address::CRSF_ADDRESS_CRSF_RECEIVER;
		msg->sourceAddress = CRSF::Address::CRSF_ADDRESS_FLIGHT_CONTROLLER;

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Ping response
	{
		auto msg = std::make_shared<CRSF::PingResponse>();

		msg->destinationAddress = CRSF::Address::CRSF_ADDRESS_CRSF_RECEIVER;
		msg->displayName = "asd";
		msg->hardwareVersion = 1;
		msg->parameterCount = 2;
		msg->parameterProtocolVersion = 3;
		msg->softwareVersion = 4;
		msg->sourceAddress = CRSF::Address::CRSF_ADDRESS_FLIGHT_CONTROLLER;

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

	// Vertical speed
	{
		auto msg = std::make_shared<CRSF::VerticalSpeed>();

		msg->verticalSpeed = 123;

		sentMessage = msg;
	}
	reader.pushByte(sentMessage->getBytes());

}
