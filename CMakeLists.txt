cmake_minimum_required(VERSION 3.17)
project(chat_app)

set(CMAKE_CXX_STANDARD 17)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.75.0 REQUIRED COMPONENTS system thread regex)

IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(server main.cpp session/session.cpp session/session.h server/server.cpp server/server.h)