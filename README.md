To build this
cd into 'build' directory
run 'make'

If we want to change the build process
cd into 'build' directory
run ccmake ../
change the configurations

We *might* need to do this before running ccmake:
Change the CMakeLists.txt if necessary. 
Delete everything inside build

TO BUILD FOR REAL:
cd into build/Debug
run: cmake -DCMAKE_BUILD_TYPE=Debug ../..
then run: make