# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

SET(COMMON_CXX_FLAGS "-Wall -DNDEBUG -O3 -fPIC")
file(GLOB_RECURSE PROJECT_SOURCES "*.c")
message(STATUS "${PROJECT_SOURCES}")

# Now build our tools
add_library(picosat SHARED ${PROJECT_SOURCES})

install(TARGETS picosat DESTINATION /usr/lib)
#install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../include/" DESTINATION /usr/include/QuickMath)

