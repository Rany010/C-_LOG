
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
rm -rf ./*
cmake ..
make

./LOG_TEST