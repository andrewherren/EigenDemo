# EigenDemo

Cross-platform programs that use Eigen (for debugging and performance profiling)

## Compilation

### Cloning the Repository

To clone the repository, you must have git installed, which you can do following [these instructions](https://learn.microsoft.com/en-us/devops/develop/git/install-and-set-up-git). 

Once git is available at the command line, navigate to the folder that will store this project (in bash / zsh, this is done by running `cd` followed by the path to the directory). 
Then, clone the `EigenDemo` repo as a subfolder by running
```{bash}
git clone https://github.com/andrewherren/EigenDemo.git
```

### CMake Build

The C++ project can be built independently from the R / Python packages using `cmake`. 
See [here](https://cmake.org/install/) for details on installing cmake (alternatively, 
on MacOS, `cmake` can be installed using [homebrew](https://formulae.brew.sh/formula/cmake)).
Once `cmake` is installed, you can build the CLI by navigating to the main 
project directory at your command line (i.e. `cd /path/to/EigenDemo`) and 
running the following code 

```{bash}
rm -rf build
mkdir build
cmake -S . -B build
cmake --build build
```

The CMake build has one primary build target

#### Large Matrix

`large_matrix.cpp` defines a standalone target that can be straightforwardly run with a debugger (i.e. `lldb`, `gdb`) 
while making non-trivial changes to the C++ code.
This debugging program is compiled as part of the CMake build if the `BUILD_LARGE_MATRIX` option in `CMakeLists.txt` is set to `ON`. 
(*NOTE*: this is currently the only target, it is only placed under a flag in `CMakeLists.txt` in case we add other demo / debug programs later on.)

Once the program has been built, it can be run from the command line via `./build/largematrix` or attached to a debugger 
via `lldb ./build/largematrix` (clang) or `gdb ./build/largematrix` (gcc).

## Xcode

While using `gdb` or `lldb` on `largematrix` at the command line is very helpful, users may prefer debugging in a full-fledged IDE like xcode. This project's C++ core can be converted to an xcode project from `CMakeLists.txt`.
To generate an XCode project based on the build targets and specifications defined in a `CMakeLists.txt`, navigate to the main project folder (i.e. `cd /path/to/EigenDemo`) and run the following commands:

```{bash}
rm -rf xcode/
mkdir xcode
cd xcode
cmake -G Xcode .. -DCMAKE_C_COMPILER=cc -DCMAKE_CXX_COMPILER=c++
cd ..
```

Now, if you navigate to the xcode subfolder (in Finder), you should be able to click on a `.xcodeproj` file and the project will open in XCode.

## Visual Studio

Similar to above, a visual studio project can be generated from this project by installing the [CMake GUI](https://cmake.org/download/) on windows and following instructions to generate and configure a visual studio project.
