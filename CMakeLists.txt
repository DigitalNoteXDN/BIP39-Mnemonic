cmake_minimum_required(VERSION 3.20)

project(Mnemonic VERSION 1.0.0)

include_directories(../../libs/openssl-1.1.1s/include)
link_directories(../../libs/openssl-1.1.1s/lib)

include_directories(include)

## Library
add_library(bip39 src/database.cpp src/util.cpp src/bip39/entropy.cpp src/bip39/checksum.cpp src/bip39/mnemonic.cpp src/bip39/seed.cpp)
set_property(TARGET bip39 PROPERTY CXX_STANDARD 17)
target_link_libraries(bip39 ssl crypto)
install(TARGETS bip39 DESTINATION lib)

INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")

## App
add_executable(Mnemonic src/main.cpp )
set_property(TARGET Mnemonic PROPERTY CXX_STANDARD 17)
if(CMAKE_SYSTEM_NAME MATCHES "MINGW")
	target_link_libraries(Mnemonic bip39 ssl crypto ws2_32 stdc++)
else()
	target_link_libraries(Mnemonic bip39)
endif()

install(TARGETS Mnemonic DESTINATION bin)

## Enable if you still want to use language .txt files in installation folder
##INSTALL (
##    DIRECTORY ${CMAKE_SOURCE_DIR}/data/
##    DESTINATION data
##    FILES_MATCHING PATTERN "*.txt*")
