cd tests
mkdir -p build
rm -rf build/*
cd build
cmake ../..
cmake --build .
cd ../..
