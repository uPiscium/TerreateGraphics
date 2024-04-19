cd tests
rm -rf samples
mkdir -p samples
rm -rf build
mkdir -p build
cd build
for file in `cat ../../scripts/targets.txt`
do
    echo "Building $file"
    cmake ../.. -DTARGET=$file
    cmake --build .
    cp ./tests/impls/${file}Test ../samples/
done
