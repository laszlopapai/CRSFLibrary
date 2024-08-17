#pragma once

#include "Messages/Message.h"
#include <vector>
#include <set>
#include <functional>
#include <memory>
#include <map>

namespace CRSF
{

using MessageHandler = std::function<void(const std::shared_ptr<Message>, bool)>;

class CRSFReader {

public:
	void setGenericMessageHandler(MessageHandler&& messageHandler) {
		m_genericHandler = messageHandler;
	}

	void setMessageHandler(MessageHandler&& messageHandler, MessageType type) {
		m_handlers[type] = messageHandler;
	}

	size_t pushByte(DataByte* bytes, size_t length);

	size_t pushByte(DataBuffer bytes);

	bool pushByte(DataByte byte);

	void reset();


private:
	static std::shared_ptr<Message> createMessage(MessageType type);

private:
	bool m_sync = false;
	std::shared_ptr<Message> m_message;
	DataByte m_length = 0;
	MessageHandler m_genericHandler;
	std::map<MessageType, MessageHandler> m_handlers;
	std::set<DataByte> m_msgs;

};

}
