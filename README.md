# CS-GY 6533 A – Interactive Computer Graphics - Fall 2021

### Assignment 1

*Yangfan Zhou*

<yz8338@nyu.edu>

# Implementation & Result

## Task 1: Image Class

For this task, I implemented a general image class *MyImageClass*. This class contains constructors: MyImageClass() and MyImageClass(const char* filename), which are used for creating default empty image and loading image. It also has the *save* method, which can save images in "P2", "P3" or "P5", "P6" formats. 

The class has private members: imageType, width, height, max, and data (stored the pixel values as vector<int>). When we read in a image, the constructor will first get a line to store the imageType. Then, it store ASCII and binary format file differently. For the ASCII format, just reading all integers and store them in data vector. For the binary format, it allocates a buffer and use read(buffer, size) to read the pixel values.
  
As for saving image, the *save* method will first specify the image format by imageType. If the image is in p2 or p3 format, output all integers in data vector to the output file. Otherwise, use *write* function to output as binary.

All other tasks are also done by adding methods to *MyImageClass*.

By using given pictures *Mandrill.ppm* and *Mandrill-gray.ppm*, let us test reading and saving pictures by:
```bash
MyImageClass image1("../../images/Mandrill.ppm");
image1.save("../../images/p3/changed_pic.ppm");

MyImageClass image1("../../images/Mandrill-gray.ppm");
image1.save("../../images/p6/changed_pic.ppm");
```
The results are saved in *p3* and *p6* directories respectively as follows:

![changed_pic](Assignment_1/figures/p3/changed_pic.png)
![changed_pic](Assignment_1/figures/p6/changed_pic.png)


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

