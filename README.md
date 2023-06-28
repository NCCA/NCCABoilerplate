# NCCA Boilerplate


[![Linux and Mac](https://github.com/NCCA/NCCABoilerplate/actions/workflows/linux-mac.yml/badge.svg)](https://github.com/NCCA/NCCABoilerplate/actions/workflows/linux-mac.yml)[![Windows CI Tests](https://github.com/NCCA/NCCABoilerplate/actions/workflows/windows.yml/badge.svg)](https://github.com/NCCA/NCCABoilerplate/actions/workflows/windows.yml)


This repository contains simple [boiler plate](https://en.wikipedia.org/wiki/Boilerplate_code) projects for different things we teach across the NCCA. 

All of these project will work fine in the linux labs without any extra installation of libraries and software as we have this all set up for you. Most will not work under the Windows labs as they are missing some of the libraries and software.

For installation at home we use [vcpkg](https://vcpkg.io/en/) for most of the 3rd party libraries. This is a cross platform package manager for C++ libraries. It is very easy to use and install. For Python we use [pyenv](https://github.com/pyenv/pyenv) for specific python versions and pip for the libraries. 

Each of the projects has a README.md file that explains how to build and run the project, they will also have an optional [vcpkg manifest file](https://vcpkg.readthedocs.io/en/latest/users/manifests/) that can be used to install the libraries needed for the project, we don't use this for the labs as this is already done. 

## Top Level

The top level of the repository contains the following:
[CMakelists.txt](CMakeLists.txt) - This is the main cmake file that is used to build the projects. And is an example of a typical subdirectory project.

[.gitignore](.gitignore) - This is a file that tells git what files to ignore when committing to the repository. This is useful for ignoring build files and other files that are not needed in the repository, this particular file is setup for C++ and Python projects.

[manifest](./manifest/) this folder contains a vcpkg.json file that contains all the libs to be built for the projects. This is also used by the github actions in the [wokrflows](.github/workflows) directory. These basically builds each time we commit and generates the badges you see at the top to see if everything still builds.

### Building

To build the projects you can use the following commands, typically I use [Ninja](https://ninja-build.org/) build system as it is much faster than the default make system.  Run the following in the root of the project.

```bash
cmake -G Ninja -B build -S .
```

The ```-G``` flag indicates the build system to use, in this case Ninja. The ```-B``` flag indicates the build directory to use, in this case build. The ```-S``` flag indicates the source directory to use, in this case the current directory.

Then to build the project run the following:

```bash

cmake --build build
```


## Subdirectories