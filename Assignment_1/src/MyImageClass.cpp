#include  "MyImageClass.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

template<class T>
T clamp(T x, T min, T max) {
    if (x > max)
        return max;
    if (x < min)
        return min;
    return x;
}

// Default: 512 * 512 empty image
MyImageClass::MyImageClass() {
    imageType = "P3";
    width = 512;
    height = 512;
    max = 255;

    vector<int> newImageData;
    for (int i = 0; i < 786432; i ++) {
        newImageData.push_back(0);
    }
    data = newImageData;
}

MyImageClass::MyImageClass(const char* filename) {
    ifstream imageFile;

    // If the file is a PPM type 5 or 6 (binary)
    imageFile.open(filename, ios::in | ios::binary);
    
    if (imageFile.is_open()){
        string line;
        vector<int> data;
        bool first = true;
        int header = 0;

        getline(imageFile, line);
        stringstream lineStream(line);
        lineStream >> imageType;

        if (imageType == "P2" || imageType == "P3") {
            while (getline(imageFile, line)) {
                stringstream ss;
                ss << line;

                // Save integers
                if (!ss.eof()) {
                    int temp;
                    while (ss >> temp) {
                        data.push_back(temp);
                    } // int
                } 
            }
            // Save width, height, max pixel value
            width = data.at(0);
            height = data.at(1);
            max = data.at(2);

            for (int i=0; i < 3; i++) {
                data.erase(data.begin());
            }
        }

        if (imageType == "P5" || imageType == "P6") {
            int count = 0;
            while (getline(imageFile, line)) {
                stringstream ss;
                ss << line;

                // Save width, height, max pixel value
                // Also ignore comments
                if (!ss.eof()) {
                    int temp;
                    while (ss >> temp) {
                        data.push_back(temp);
                        count ++;
                    } 
                    if (count == 3) {
                        break;
                    }
                } 
            }
            width = data.at(0);
            height = data.at(1);
            max = data.at(2);

            for (int i=0; i < 3; i++) {
                data.erase(data.begin());
            }

            // Read pixels
            int size = width * height * 3;
            char *buffer = new char[size];
            imageFile.read(buffer, size);
            
            for (int i = 0; i < size; i ++) {
                unsigned char temp = buffer[i];
                data.push_back((int)temp);
            }
        }

        // Save pixels
        this->data = data;

        imageFile.close();
    } else {
        cout<<"Can not open!";
    }
}

// Destructor
MyImageClass::~MyImageClass(void) {
}

void MyImageClass::save(const char* filename) {

    if (imageType == "P2" || imageType == "P3") {
        ofstream imageFile;
        imageFile.open(filename);
        if (imageFile.is_open()) {
            imageFile << (this->imageType) << "\n";
            imageFile << (this->width) << "\n";
            imageFile << (this->height) << "\n";
            imageFile << (this->max) << "\n";
            for (int i = 0; i < (this->data).size(); i ++) {
                imageFile << (this->data).at(i) << "\n";
            }
        imageFile.close();
        }
    }

    if (imageType == "P5" || imageType == "P6") {
        ofstream imageFile;
        imageFile.open(filename, ios::out | ios::binary);
        if (imageFile.is_open()) {
            imageFile << (this->imageType) << "\n";
            imageFile << (this->width) << " ";
            imageFile << (this->height) << "\n";
            imageFile << (this->max) << "\n";
            for (int i = 0; i < (this->data).size(); i ++) {
                imageFile.write((char*)&data.at(i), 1);
            }
        imageFile.close();
        }
    }
}

MyImageClass MyImageClass::operator+(MyImageClass image) {
    MyImageClass newImage;
    vector<int> newImageData;
    int sum;

    // Check size
    if (this->width == image.width && this->height == image.height) {
        // Addition
        newImage.imageType = image.imageType;
        newImage.width = image.width;
        newImage.height = image.height;
        for (int i = 0; i < image.data.size(); i ++) {
            sum = (this->data).at(i) + image.data.at(i);
            newImageData.push_back(sum);
        }
        newImage.data = newImageData;
        newImage.max = max;
    } else {
        cout << "The images must be the same size! \n";
    }
    return newImage;
}

MyImageClass MyImageClass::operator-(MyImageClass image) {
    MyImageClass newImage;
    vector<int> newImageData;
    int diff;

    // Check size
    if (this->width == image.width && this->height == image.height) {
        // Subtraction
        newImage.imageType = image.imageType;
        newImage.width = image.width;
        newImage.height = image.height;
        for (int i = 0; i < image.data.size(); i ++) {
            diff = (this->data).at(i) - image.data.at(i);
            diff = clamp(diff, 0, max);
            newImageData.push_back(diff);
        }
        newImage.data = newImageData;
        newImage.max = max;
    } else {
        cout << "The images must be the same size! \n";
    }
    return newImage;
}

MyImageClass MyImageClass::operator+=(MyImageClass image) {
    MyImageClass newImage;
    // Check size
    if (this->width == image.width && this->height == image.height) {
        // Addition assignment
        newImage.imageType = image.imageType;
        newImage.width = image.width;
        newImage.height = image.height;
        for (int i = 0; i < image.data.size(); i ++) {
            (this->data).at(i) += image.data.at(i);
            (this->data).at(i) = (this->data).at(i)/2;
        }
        newImage.max = max;
    } else {
        cout << "The images must be the same size! \n";
    }
    return newImage;
}

MyImageClass MyImageClass::operator-=(MyImageClass image) {
    MyImageClass newImage;
    // Check size
    if (this->width == image.width && this->height == image.height) {
        // Subtraction assignment
        newImage.imageType = image.imageType;
        newImage.width = image.width;
        newImage.height = image.height;
        for (int i = 0; i < image.data.size(); i ++) {
            (this->data).at(i) -= image.data.at(i);
            (this->data).at(i) = clamp((this->data).at(i), 0, max);
        }
        newImage.max = max;
    } else {
        cout << "The images must be the same size! \n";
    }
    return newImage;
}

MyImageClass MyImageClass::operator*(double scalar) {
    MyImageClass newImage;
    vector<int> newImageData;
    int mul;

    newImage.imageType = imageType;
    newImage.width = width;
    newImage.height = height;
    for (int i = 0; i < data.size(); i ++) {
        mul = (int)(data.at(i) * scalar);
        newImageData.push_back(mul);
    }
    newImage.data = newImageData;
    newImage.max = max;

    return newImage;
}

MyImageClass MyImageClass::operator*=(double scalar) {
    MyImageClass newImage;

    newImage.imageType = imageType;
    newImage.width = width;
    newImage.height = height;
    for (int i = 0; i < data.size(); i ++) {
        data.at(i) = (int)(data.at(i) * scalar);
    }
    newImage.max = max;

    return newImage;
}

vector<int> MyImageClass::operator[](int index) {
    vector<int> pixel;

    pixel.push_back(data.at(index*3));
    pixel.push_back(data.at(index*3 + 1));
    pixel.push_back(data.at(index*3 + 2));
    return pixel;
}

void MyImageClass::mirrorX() {
    vector<int> newImage;
    vector<int> temp;
    int index;

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j ++) {
            index = i*width + (width - 1 - j); // mirror on X axis
            temp = operator[](index);
            newImage.push_back(temp.at(0));
            newImage.push_back(temp.at(1));
            newImage.push_back(temp.at(2));
        }
    }
    data = newImage;
}

MyImageClass MyImageClass::Gamma(double g) {
    MyImageClass newImage;
    float max_f = (float)max;
    for(int i = 0; i < data.size(); i ++) {
        double temp = pow((double)(data.at(i)/max_f), g) * max_f;
        newImage.data.at(i) = (int)temp;
    }
    return newImage;
}

MyImageClass MyImageClass::Alpha(MyImageClass front, MyImageClass back, double a) {
    MyImageClass newImage = front * a + back * (1-a);
    return newImage;
}

MyImageClass MyImageClass::dilate() {
    MyImageClass newImage;
    newImage.data = this->data;

    int se[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 1; i < height - 1; i ++) {
        for (int j = 1; j < width - 1; j ++) {

            int index[9] = {(i-1)*width+(j-1), (i-1)*width+j, (i-1)*width+(j+1),
                    i*width+(j-1), i*width+j, i*width+(j+1),
                    (i+1)*width+(j-1), (i+1)*width+j, (i+1)*width+(j+1)};
            
            for (int m = 0; m < 3; m ++) {
                int temp[9] = {se[0] * (operator[](index[0]).at(m)), se[1] * (operator[](index[1]).at(m)),
                    se[2] * (operator[](index[2]).at(m)), se[3] * (operator[](index[3]).at(m)),
                    se[4] * (operator[](index[4]).at(m)), se[5] * (operator[](index[5]).at(m)),
                    se[6] * (operator[](index[6]).at(m)), se[7] * (operator[](index[7]).at(m)),
                    se[8] * (operator[](index[8]).at(m))};
                
                int max = 0;
                for (int n = 0; n < 9; n ++) {
                    if (temp[n] > max) {
                        max = temp[n];
                    }
                }

                newImage.data.at(3 * (i*width + j) + m) = max;
            }
        }
    }
    return newImage;
}

MyImageClass MyImageClass::erode() {
    MyImageClass newImage;
    newImage.data = this->data;

    int se[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 1; i < height - 1; i ++) {
        for (int j = 1; j < width - 1; j ++) {

            int index[9] = {(i-1)*width+(j-1), (i-1)*width+j, (i-1)*width+(j+1),
                    i*width+(j-1), i*width+j, i*width+(j+1),
                    (i+1)*width+(j-1), (i+1)*width+j, (i+1)*width+(j+1)};
            
            for (int m = 0; m < 3; m ++) {
                int temp[9] = {se[0] * (operator[](index[0]).at(m)), se[1] * (operator[](index[1]).at(m)),
                    se[2] * (operator[](index[2]).at(m)), se[3] * (operator[](index[3]).at(m)),
                    se[4] * (operator[](index[4]).at(m)), se[5] * (operator[](index[5]).at(m)),
                    se[6] * (operator[](index[6]).at(m)), se[7] * (operator[](index[7]).at(m)),
                    se[8] * (operator[](index[8]).at(m))};
                
                int min = temp[0];
                for (int n = 0; n < 9; n ++) {
                    if (temp[n] < min) {
                        min = temp[n];
                    }
                }

                newImage.data.at(3 * (i*width + j) + m) = min;
            }
        }
    }
    return newImage;
}