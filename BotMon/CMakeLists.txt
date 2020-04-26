cmake_minimum_required (VERSION 2.8)
project (BotMon)

add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
	util.cpp
	logger.cpp
	crypt.cpp
	http.cpp
	processmod.cpp
)

set (hdrs
    main.h
	util.h
	logger.h
	crypt.h
	http.h
	processmod.h
)

add_library (BotMon SHARED ${hdrs} ${srcs} main.def)

#install
INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
