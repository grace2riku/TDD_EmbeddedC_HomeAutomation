project (LedDriver)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/util)
include_directories(${PROJECT_SOURCE_DIR}/../include/IO)
include_directories($ENV{CPPUTEST_HOME}/include)

add_library(RuntimeErrorStub RuntimeErrorStub.c)
add_library(FormatOutputSpy FormatOutputSpy.c)
add_library(FormatOutputSpyTest FormatOutputSpyTest.cpp)
add_library(MockIO MockIO.c)
