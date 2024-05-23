cd tests
if [ $1 == 'c' ]; then
    echo "Clean option selected."
    echo "Cleaning build directory..."
    rm -rf build
    rm -f ../samples/TCTest
    echo "Build directory cleaned."
fi
mkdir -p build
cd build
cmake ../..
cmake --build .
pwd
cp tests/impls/TCTest ../
cd ../
pwd
echo "Running TCTest..."
./TCTest
cd ../..
