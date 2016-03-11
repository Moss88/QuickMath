# Now build our tools
enable_testing()
include_directories("${gtest_SOURCE_DIR}/include")
message(STATUS "${gtest_SOURCE_DIR}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g") 
file(GLOB TEST_SOURCE_FILES "./*.cpp")
add_executable(testProg ${TEST_SOURCE_FILES})
target_link_libraries(testProg quickmath gtest gtest_main)
