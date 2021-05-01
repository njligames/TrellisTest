cmake_minimum_required(VERSION 3.15.3)

project(Trellis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set(LIB_HEADERS PolicyData.h PolicyParser.h)
set(LIB_SOURCES PolicyParser.cpp)
set(MAIN_SOURCES main.cpp)
set(DATA_FILES ${CMAKE_CURRENT_SOURCE_DIR}/policies.json)

list(APPEND TARGET_DEFINITIONS -DTEST_ASSET_PATH=\"${DATA_FILES}\")

add_library(trellis-static STATIC ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(trellis-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(trellis-exe ${MAIN_SOURCES} ${DATA_FILES})
target_link_libraries(trellis-exe trellis-static)
target_include_directories(trellis-exe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(trellis-exe PUBLIC ${TARGET_DEFINITIONS})


