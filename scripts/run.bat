mkdir build
cd build
cmake ..
cmake --build .
cp ./tests/impls/TCTest ../tests/test
cd ../tests
echo "Running TCTest..."
./test
cd ..
