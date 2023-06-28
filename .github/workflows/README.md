## Github Actions

These are run on a commit and allow us to automatically build and test the code on different platforms. This is done using [Github Actions](https://github.com/features/actions) and the configuration files are in the [.github/workflows](.github/workflows) directory.

This is a form on Continuous Integration (CI) and is a very useful tool for testing your code on different platforms and different compilers. It is also useful for running tests on your code.

### Linux and Mac

This uses a matrix build as Mac and Linux are very similar in how they work. It will basically clone the latest version of vcpkg then use the manifest to install all the libs that are required for the project. Then it will build the project and run the tests (or executables if appropriate)

### Windows

The windows build requires a few different things to get it to work so has been split out into a separate workflow. It will basically clone the latest version of vcpkg then use the manifest to install all the libs that are required for the project. Then it will build the project and run the tests (or executables if appropriate)