project (LedDriver)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/LedDriver/)
include_directories(${PROJECT_SOURCE_DIR}/../include/HomeAutomation/)
include_directories(${PROJECT_SOURCE_DIR}/../include/util)
include_directories(${PROJECT_SOURCE_DIR}/../include/IO)

## Configure a header file to pass some of the CMake settings
## to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/../include/TutorialConfig.h.in"
#  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#)

#add_executable(Tutorial ./Tutorial/tutorial.cxx)
add_library(LedDriver ./LedDriver/LedDriver.c)
add_library(LightScheduler ./HomeAutomation/LightScheduler.c)
add_library(RandomMinute ./HomeAutomation/RandomMinute.c)
add_library(Utils ./util/Utils.c)
add_library(CircularBuffer ./util/CircularBuffer.c)
add_library(Flash ./IO/Flash.c)
add_library(IO ./IO/IO.c)
