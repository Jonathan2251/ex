# Demonstration for how to call bash command in cmake

# rm -rf build; mkdir build; cd build
# cmake ..  // no foobar.txt
# make hello
# make world
# make world // this "make world" doesn't call "cp ..."
# rm -f sh/world.sh
# make world

# References:
# https://gist.github.com/baiwfg2/39881ba703e9c74e95366ed422641609

cmake_minimum_required(VERSION 3.10)
project(water)

add_subdirectory("sh")
