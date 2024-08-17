cmake_minimum_required(VERSION 3.5)

project(CRSFLibrary)

add_library(
    CRSF

    "src/CRSFReader.cpp"
    "src/CRSFReader.h"    

    "src/Messages/Attitude.h"
    "src/Messages/Battery.h"
    "src/Messages/ChannelsPacked.h"
    "src/Messages/FlightMode.h"
    "src/Messages/Heartbeat.h"
    "src/Messages/LinkStatistics.h"
    "src/Messages/Message.cpp"
    "src/Messages/Message.h"
    "src/Messages/PingRequest.h"
    "src/Messages/PingResponse.h"
    "src/Messages/VerticalSpeed.h"
 )

 include_directories(src)

add_executable(
    CRSF_Message_Check

    "exmaple/CRSF_MessageCheck.cpp"
)

target_link_libraries(
	CRSF_Message_Check
	
	CRSF
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CRSF PROPERTY CXX_STANDARD 20)
endif()
