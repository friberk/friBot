cmake_minimum_required (VERSION 3.6)
project(friBot)

option(USE_CLANG "build application with clang" ON)
set(ENV{PKG_CONFIG_PATH} "/usr/local/opt/openssl/lib/pkgconfig")

add_executable(friBot src/main.cpp src/yks.cpp src/cloudinary_uploader.cpp src/key_handler.cpp)

# OpenSSL
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    if(APPLE)
        include_directories(/usr/local/Cellar/openssl@1.1/1.1.1k/include)
        list(APPEND LIB_LIST /usr/local/Cellar/openssl@1.1/1.1.1k/lib/libssl.dylib)
        list(APPEND LIB_LIST /usr/local/Cellar/openssl@1.1/1.1.1k/lib/libcrypto.dylib)
        message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
    else()
        include_directories(${OPENSSL_INCLUDE_DIR})
        list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})
        message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
    endif()
endif()

# SQLite3
# find_package (SQLite3)
# if (SQLITE3_FOUND)
#   include_directories(${SQLITE3_INCLUDE_DIRS})
#   target_link_libraries (friBot ${SQLITE3_LIBRARIES})
# endif (SQLITE3_FOUND)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(friBot sleepy-discord)

set(EXECUTABLE_OUTPUT_PATH "../bin")