cmake_minimum_required(VERSION 3.27)
add_definitions(-std=c++17)

# set(CXX_FLAGS "-Wall")
# set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    MESSAGE("APPLE")
endif()

if(UNIX AND NOT APPLE)
    MESSAGE("LINUX")
endif()

# set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake-modules)
MESSAGE("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
find_package(MySqlClient REQUIRED)

MESSAGE("MYSQL_LIBRARIES: " ${MYSQL_LIBRARIES})
MESSAGE("MYSQL_INCLUDE_DIR: " ${MYSQL_INCLUDE_DIR})


project(database_adaptor)

include_directories(
    include
    ${MYSQL_INCLUDE_DIR}
)

add_executable (fetch_and_commit example/fetch_and_commit.cpp src/database_adaptor.cpp)
target_link_libraries(fetch_and_commit ${MYSQL_LIBRARIES})