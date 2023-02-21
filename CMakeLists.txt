cmake_minimum_required(VERSION 3.20)

project(Mnemonic VERSION 1.0.0)

include_directories(../openssl-1.1.1s/include)
link_directories(../openssl-1.1.1s/lib)

include_directories(include)

## Library
add_library(bip39 src/util.cpp src/bip39/entropy.cpp src/bip39/checksum.cpp src/bip39/mnemonic.cpp src/bip39/seed.cpp)
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
target_link_libraries(Mnemonic bip39)
install(TARGETS Mnemonic DESTINATION bin)

INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/data/
    DESTINATION data
    FILES_MATCHING PATTERN "*.txt*")