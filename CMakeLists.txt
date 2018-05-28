set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(EmbbededSystemsProject)

message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")


list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/helloworld.c"
    "${PROJECT_SOURCE_DIR}/src/compass.c"
    "${PROJECT_SOURCE_DIR}/src/temperature.c"
    "${PROJECT_SOURCE_DIR}/src/accelerometer.c"
    "${PROJECT_SOURCE_DIR}/src/i2c_utils.c"
    "${PROJECT_SOURCE_DIR}/src/configure.c"
    "${PROJECT_SOURCE_DIR}/src/main.c"
    )

list(APPEND HEADERS
    "${PROJECT_SOURCE_DIR}/src/helloworld.h"
    "${PROJECT_SOURCE_DIR}/src/compass.h"
    "${PROJECT_SOURCE_DIR}/src/temperature.h"
    "${PROJECT_SOURCE_DIR}/src/accelerometer.h"
    "${PROJECT_SOURCE_DIR}/src/includes.h"
    "${PROJECT_SOURCE_DIR}/src/i2c_utils.h"
    "${PROJECT_SOURCE_DIR}/src/configure.h"
    "${PROJECT_SOURCE_DIR}/src/state.h"
    )

target_sources(app PRIVATE ${SOURCES})
target_sources(app PRIVATE ${HEADERS})
