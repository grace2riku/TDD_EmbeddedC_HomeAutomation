project (LedDriver)

# include project source
include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/LedDriver)
include_directories(${PROJECT_SOURCE_DIR}/../include/HomeAutomation)
include_directories(${PROJECT_SOURCE_DIR}/../include/util)
include_directories(${PROJECT_SOURCE_DIR}/../include/IO)

# include mocks only for test code
include_directories(${PROJECT_SOURCE_DIR}/../mocks)

# include CppUTest headers
include_directories($ENV{CPPUTEST_HOME}/include)

# add cpputest library
add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTest.a)
#             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/src/CppUTest/libCppUTest.a)

# build test library for LedDriver
add_library(LedDriverTest ./LedDriver/LedDriverTest.cpp)
add_library(LightSchedulerTest ./HomeAutomation/LightSchedulerTest.cpp)
add_library(LightControllerSpyTest ./HomeAutomation/LightControllerSpyTest.cpp)
add_library(LightControllerSpy ./HomeAutomation/LightControllerSpy.c)
add_library(FakeTimeServiceTest ./HomeAutomation/FakeTimeServiceTest.cpp)
add_library(FakeTimeService ./HomeAutomation/FakeTimeService.c)
add_library(RandomMinuteTest ./HomeAutomation/RandomMinuteTest.cpp)
add_library(LightSchedulerRandomizeTest ./HomeAutomation/LightSchedulerRandomizeTest.cpp)
add_library(FakeRandomMinute ./HomeAutomation/FakeRandomMinute.c)
add_library(CircularBufferPrintTest ./util/CircularBufferPrintTest.cpp)
add_library(FlashTest ./IO/FlashTest.cpp)
add_library(FlashTest_CppUMock ./IO/FlashTest_CppUMock.cpp)

add_executable(RunAllTests RunAllTests.cpp)
target_link_libraries(RunAllTests imp_cpputest
                    LedDriverTest LedDriver
                    LightSchedulerTest LightScheduler
                    LightControllerSpyTest LightControllerSpy
                    FakeTimeServiceTest FakeTimeService
                    RandomMinuteTest RandomMinute
                    LightSchedulerRandomizeTest
                    RuntimeErrorStub
                    FakeRandomMinute
                    FormatOutputSpyTest FormatOutputSpy
                    Utils
                    CircularBufferPrintTest
                    CircularBuffer
                    FlashTest Flash
                    MockIO
                    FakeMicroTime
                    IO
                    FlashTest_CppUMock
                    )
