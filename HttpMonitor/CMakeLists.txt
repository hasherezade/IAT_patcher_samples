cmake_minimum_required (VERSION 2.8)
project (MyLib)

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

add_library (MyLib SHARED ${hdrs} ${srcs} main.def)