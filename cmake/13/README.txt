name no conflict though in different exe (water1, water2)
and execute different exe by system(char* command) on OS
// build
rm -rf build; mkdir build; cd build
cmake ..
make 
// run
./water cpu1
./water cpu2
