cd tests
mkdir build
cd build
for file in `cat ../../scripts/targets.txt`
do
    echo "Building $file"
    cmake ../.. -DTARGET=$file
    cmake --build .
    cp ./tests/impls/${file}Test ../samples/
done
