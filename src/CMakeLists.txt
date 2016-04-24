# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

SET(COMMON_CXX_FLAGS "-std=c++11 -Wall -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS} ${COMMON_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${COMMON_CXX_FLAGS} -g")


# Now build our tools
add_library(quickmath SHARED ${PROJECT_SOURCES})

install(TARGETS quickmath DESTINATION /usr/lib)
install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../include/" DESTINATION /usr/include/QuickMath)

