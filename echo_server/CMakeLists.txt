CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(ECHO_UNIX_DOMAIN_SOCKET_SERVER)

SET(ECHO_UNIX_DOMAIN_SOCKET_SERVER_VERSION_MAJOR 1)
SET(ECHO_UNIX_DOMAIN_SOCKET_SERVER_VERSION_MINOR 0)

INCLUDE_DIRECTORIES(include)

FIND_PACKAGE(Boost)
IF(NOT Boost_FOUND)
    message( FATAL_ERROR "Boost libarary Not Found!!!!")
ENDIF()

FIND_PACKAGE(Boost 1.58.0 REQUIRED COMPONENTS system thread regex)

INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}")
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)

ADD_EXECUTABLE(echo_server src/server.cpp src/EchoConnectionHandler.cpp src/EchoUnixDomainSocketServer.cpp)
TARGET_LINK_LIBRARIES(echo_server ${Boost_LIBRARIES})

ADD_EXECUTABLE(echo_client src/client.cpp)
TARGET_LINK_LIBRARIES(echo_client ${Boost_LIBRARIES})
