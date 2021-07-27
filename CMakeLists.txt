cmake_minimum_required (VERSION 3.6)

# Use clang by default
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(friBot VERSION 0.0.0 LANGUAGES C CXX)

add_executable(friBot src/main.cpp src/yks.cpp src/cloudinary_uploader.cpp src/key_handler.cpp)

find_package (nlohmann_json REQUIRED)
target_link_libraries (friBot nlohmann_json)

# SQLite3
# find_package (SQLite3)
# if (SQLITE3_FOUND)
#   include_directories(${SQLITE3_INCLUDE_DIRS})
#   target_link_libraries (friBot ${SQLITE3_LIBRARIES})
# endif (SQLITE3_FOUND)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(friBot sleepy-discord)

set(EXECUTABLE_OUTPUT_PATH "../bin")