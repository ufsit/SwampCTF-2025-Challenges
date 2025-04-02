#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class imageManipulation {
    //Nested Classes:
        struct Header{
            char _idLength;
            char _colorMapType;
            char _dataTypeCode;
            short _colorMapOrigin;
            short _colorMapLength;
            char _colorMapDepth;
            short _xOrigin;
            short _yOrigin;
            short _width;
            short _height;
            char _bitsPerPixel;
            char _imageDescriptor;
        };

        struct Pixel{
            unsigned char _redData;
            unsigned char _greenData;
            unsigned char _blueData;
        };

        struct Image {
            Header _imageHeader;
            vector <Pixel> _pixelData;
        };  

    public:
    //Constructor:
        imageManipulation();

    //Image File Reading and Writing:
        Image readImageData(string filePath);
        void writeImageData(Image data, string filePath);
    
   //Image Manipulation:      
        Image combineImagesLineByLine(Image img1, Image img2);
        Image divideImagesLineByLine(Image inputImage, int imageLookingFor, int totalImages);  
};
