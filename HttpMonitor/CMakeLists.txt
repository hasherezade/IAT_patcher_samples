cmake_minimum_required (VERSION 2.8)
project (MyLib)

add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
	crypt.cpp
	http.cpp
)

set (hdrs
    main.h
	crypt.h
	http.h
)

add_library (MyLib SHARED ${hdrs} ${srcs} main.def)