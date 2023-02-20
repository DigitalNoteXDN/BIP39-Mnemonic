cmake_minimum_required(VERSION 3.20)

project(Mnemonic VERSION 1.0.0)

include_directories(/var/www/DigitalNote-Builder/linux/x64/libs/openssl-1.1.1s/include)
link_directories(/var/www/DigitalNote-Builder/linux/x64/libs/openssl-1.1.1s/lib)

add_executable(Mnemonic src/main.cpp src/util.cpp src/bip39/entropy.cpp src/bip39/checksum.cpp src/bip39/mnemonic.cpp src/bip39/seed.cpp)

set_property(TARGET Mnemonic PROPERTY CXX_STANDARD 17)
target_link_libraries(Mnemonic ssl crypto)

install(TARGETS Mnemonic DESTINATION bin)

add_test(NAME TestApp COMMAND Mnemonic)
