mkdir build
cd build

echo "--- Compile ---"

cmake ..
make
cmake --install . --prefix "../"

echo "--- RUN ---"

cd ../bin
./Mnemonic