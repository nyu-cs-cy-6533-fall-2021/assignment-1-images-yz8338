#include <string>
#include <vector>
using namespace std;

#ifndef MyImageClass_H
#define MyImageClass_H

class MyImageClass {
    public:
        MyImageClass();
        MyImageClass(const char* filename);
        ~MyImageClass(void);

        void save(const char* filename);
        void mirrorX();
        MyImageClass Gamma(double g);
        MyImageClass Alpha(MyImageClass front, MyImageClass back, double a);

        MyImageClass operator+(MyImageClass);
        MyImageClass operator-(MyImageClass);
        MyImageClass operator+=(MyImageClass);
        MyImageClass operator-=(MyImageClass);
        MyImageClass operator*(double scalar);
        MyImageClass operator*=(double scalar);
        vector<int> operator[](int index);
    private:
        string imageType;
        int width;
        int height;
        int max;
        vector<int> data;
};

#endif