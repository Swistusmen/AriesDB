if [ -d "build" ]
then
    rm -r build
fi
mkdir build
cd  build
cmake -S ../source/ -B .
make
