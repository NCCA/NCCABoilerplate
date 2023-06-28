# GTest Example

This example show how to use the [Google Test](https://github.com/google/googletest) framework to write unit tests for your code. See lecture notes [here](https://nccastaff.bournemouth.ac.uk/jmacey/msc/ase/lectures/Lecture3/) for more examples.

## Building

Whilst this project is part of a larger set of examples it can be copied into your own project and built using the following commands:

```bash
cmake -G Ninja -B build -S .
cmake --build build
cd build
./GTestBoilerPlate
```
 
 It is also possible to use the [ctest](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html#:~:text=CTest%20is%20an%20executable%20that,the%20tests%20for%20the%20project.) command to run the tests, this is useful if you have a large number of tests and want to run them all at once.

 ## Manifest Mode

 If building at home or wanting to try a newer version of GTest (if avaliable) you can use the [vcpkg manifest mode](https://vcpkg.readthedocs.io/en/latest/users/manifests/) to install the libraries needed for this project. To do this you need to add the following to the cmake command line:

 ```bash
 mkdir build
 cd build
 cmake -G Ninja -DVCPKG_MANIFEST_DIR=../manifest/ ..
 cmake --build . 
```

This will read the file [vcpkg.json](./manifest/vcmanifest.json) and install the libraries needed for this project, just in this local folder. At home this can be useful as well.




