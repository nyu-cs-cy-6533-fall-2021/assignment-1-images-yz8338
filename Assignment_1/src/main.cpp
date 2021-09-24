#include <iostream>
#include <exception>
#include "MyImageClass.h"
#include <fstream>
#include <cmath>
using namespace std;

MyImageClass Gamma(MyImageClass image, double g);
MyImageClass Alpha(MyImageClass front, MyImageClass back, double a);

int main(int argc, char* argv[]) {

    try {
        MyImageClass image1("../../images/Mandrill-gray.ppm");
        MyImageClass image2("../../images/tandon_stacked_color.ppm");

        // Task 1 //
        image1.save("../../images/changed_pic.ppm");

        // Task 2 //
        // Add Image 1 and 2 and assign result to image 3
        MyImageClass image3;
        image3 = image1 + image2;
        image3.save("../../images/add_pic.ppm");

        // Addition assignment plus mirroring on X axis
        MyImageClass image4;
        image4 += image3;
        image4.mirrorX();
        image4.save("../../images/mirror_pic.ppm");

        // Subtract Image 2 from Image 1 and assign result to image 5
        MyImageClass image5;
        image5 = image1 - image2;
        image5.save("../../images/subtract_pic.ppm");

        // Subtraction assignment
        MyImageClass image6 = image1;
        image6 -= image2; // identical with image5
        image6.save("../../images/subtract_as_pic.ppm");

        // Multiplication by scalar
        MyImageClass image7 = image1 * 0.5;
        image7.save("../../images/mul_pic.ppm");

        // Multiplication assignment
        MyImageClass image8 = image1;
        image8 *= 0.5; // identical with image7
        image8.save("../../images/mul_as_pic.ppm");

        //Gamma correction
        MyImageClass image9 = image1.Gamma(2.0);
        image9.save("../../images/gamma_pic1.ppm");

        MyImageClass image10 = image1.Gamma(0.5);
        image10.save("../../images/gamma_pic2.ppm");

        // Alpha compositing
        MyImageClass image11 = image1.Alpha(image1, image2, 0.5); // alpha = 0.5
        image11.save("../../images/alpha_pic1.ppm");

        MyImageClass image12 = image1.Alpha(image1, image2, 0.85); // alpha = 0.85
        image12.save("../../images/alpha_pic2.ppm");


    } catch(exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
