mkdir -p build
rm -rf build/*
cd build
cmake ../impls
cmake --build .
cd ..
