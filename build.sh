mkdir build
cd build

echo "--- Compile ---"

cmake ..
make
cmake --install . --prefix "../../../libs/mnemonic"

echo "--- RUN ---"

cd ../../../libs/mnemonic/bin
./Mnemonic