if [ -d "debug" ]
then
    rm -r debug
fi
mkdir debug
cd  debug
cmake -DCMAKE_BUILD_TYPE=Debug -S .. -B .
make
