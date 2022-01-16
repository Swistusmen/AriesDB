mkdir build_test
cp -r test/* build_test/
cd build_test
cmake .
make
./Tests
cd ..
rm -r build_test