# CS-GY 6533 A – Interactive Computer Graphics - Fall 2021

### Assignment 1

*Yangfan Zhou*

<yz8338@nyu.edu>

# Implementation & Result

## Task 1: Image Class

For this task, I implemented a general image class *MyImageClass*. This class contains constructors: MyImageClass() and MyImageClass(const char* filename), which are used for creating default empty image and read-in image. It also has the *save* method, which can save images in "P2", "P3" or "P5", "P6" formats. All other tasks are also done by adding methods to *MyImageClass*.

I tested the loading function by the given pictures *Mandrill.ppm* and *Mandrill-gray.ppm*. By using
```bash
MyImageClass image1("../../images/Mandrill.ppm");
```
and
```bash
MyImageClass image1("../../images/Mandrill-gray.ppm");
```
We can read in images in either ASCII or binary representations.

## Task 2: Operations on Images

## Task 3: Gamma Correction

## Task 4: Alpha Compositing




# Compilation Instructions

```bash
cd Assignment_1
mkdir build
cd build
cmake ../ # re-run cmake when you add/delete source files
make # use "cmake --build ." for Windows
```

