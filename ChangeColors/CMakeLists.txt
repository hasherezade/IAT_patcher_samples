cmake_minimum_required (VERSION 2.8)
project (ChangeColors)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
)

set (hdrs
    main.h
)

add_library (ChangeColors SHARED ${hdrs} ${srcs} main.def)