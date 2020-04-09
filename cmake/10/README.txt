name conflict though in different lib (libwa1, libwa2)
// build
rm -rf build; mkdir build; cd build
cmake ..
make  // multiple definition of `func()'
