cmake_minimum_required (VERSION 2.8)
project (MyLib)

set (srcs
    main.cpp
)

set (hdrs
    main.h
)

add_library (MyLib SHARED ${hdrs} ${srcs} )
