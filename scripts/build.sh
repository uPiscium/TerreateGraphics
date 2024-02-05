cd tests
mkdir -p build
cd build
cmake ../.. -DTARGET=$1
cmake --build .
cp ./tests/impls/$1Test ../samples/
cd ../..
