both dynamic libs bind the first fun() (fun1.cpp::fun()), fun2.cpp::fun() does not bind
// build
rm -rf build; mkdir build; cd build
cmake ..
make 
// run 
./water
func1.cpp::func()
func1.cpp::func()

