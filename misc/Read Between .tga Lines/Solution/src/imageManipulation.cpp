#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "imageManipulation.h"

imageManipulation::imageManipulation() {

}

imageManipulation::Image imageManipulation::combineImagesLineByLine(Image img1, Image img2){
    Image finalImage;
    finalImage._imageHeader._idLength = img1._imageHeader._idLength;
    finalImage._imageHeader._colorMapType = img1._imageHeader._colorMapType;
    finalImage._imageHeader._dataTypeCode = img1._imageHeader._dataTypeCode;
    finalImage._imageHeader._colorMapOrigin = img1._imageHeader._colorMapOrigin;
    finalImage._imageHeader._colorMapLength = img1._imageHeader._colorMapLength;
    finalImage._imageHeader._colorMapDepth = img1._imageHeader._colorMapDepth;
    finalImage._imageHeader._xOrigin = img1._imageHeader._xOrigin;
    finalImage._imageHeader._yOrigin = img1._imageHeader._yOrigin;
    finalImage._imageHeader._width = img1._imageHeader._width;
    finalImage._imageHeader._height = img1._imageHeader._height * 2;
    finalImage._imageHeader._bitsPerPixel = img1._imageHeader._bitsPerPixel;
    finalImage._imageHeader._imageDescriptor = img1._imageHeader._imageDescriptor;

    int currentIndex = 0;
    int maxIndex = 2;

    for (int i = 0; i < finalImage._imageHeader._height; i++) {
        for (int j = 0; j < finalImage._imageHeader._width; j++) {
            if(currentIndex == 0){
                try{
                    finalImage._pixelData.push_back(img1._pixelData.at(((i / maxIndex) * finalImage._imageHeader._width) + j));    
                }catch(exception e){
                    finalImage._pixelData.push_back(img1._pixelData.at(0));    
                }
            }else{
                try{
                    finalImage._pixelData.push_back(img2._pixelData.at(((i / maxIndex) * finalImage._imageHeader._width) + j));     
                }catch(exception e){
                    finalImage._pixelData.push_back(img2._pixelData.at(0));    
                }
            }
        }

        currentIndex += 1;
        if(currentIndex == maxIndex){
            currentIndex = 0;
        }
    }

    return finalImage;
}

imageManipulation::Image imageManipulation::divideImagesLineByLine(Image inputImage, int imageLookingFor, int totalImages){
    Image finalImage;
    finalImage._imageHeader._idLength = inputImage._imageHeader._idLength;
    finalImage._imageHeader._colorMapType = inputImage._imageHeader._colorMapType;
    finalImage._imageHeader._dataTypeCode = inputImage._imageHeader._dataTypeCode;
    finalImage._imageHeader._colorMapOrigin = inputImage._imageHeader._colorMapOrigin;
    finalImage._imageHeader._colorMapLength = inputImage._imageHeader._colorMapLength;
    finalImage._imageHeader._colorMapDepth = inputImage._imageHeader._colorMapDepth;
    finalImage._imageHeader._xOrigin = inputImage._imageHeader._xOrigin;
    finalImage._imageHeader._yOrigin = inputImage._imageHeader._yOrigin;
    finalImage._imageHeader._width = inputImage._imageHeader._width;
    finalImage._imageHeader._height = inputImage._imageHeader._height / totalImages;
    finalImage._imageHeader._bitsPerPixel = inputImage._imageHeader._bitsPerPixel;
    finalImage._imageHeader._imageDescriptor = inputImage._imageHeader._imageDescriptor;

    int currentIndex = 0;
    for (int i = 0; i < finalImage._imageHeader._height ; i++) {
        for (int j = 0; j < finalImage._imageHeader._width; j++) {
            if (currentIndex == imageLookingFor){
                finalImage._pixelData.push_back(inputImage._pixelData.at((i  * finalImage._imageHeader._width) + j));     
            }
        }

        currentIndex += 1;
        if(currentIndex == totalImages){
            currentIndex = 0;
        }
    }

    return finalImage;
}

imageManipulation::Image imageManipulation::readImageData(string filePath) {
	ifstream inputFile(filePath, ios_base::binary);
    Image outputImage;

	if (inputFile.is_open()) {
		//Read Header File           
            inputFile.read(&outputImage._imageHeader._idLength, 1);
            inputFile.read(&outputImage._imageHeader._colorMapType, 1);
            inputFile.read(&outputImage._imageHeader._dataTypeCode, 1);
            inputFile.read((char*)&outputImage._imageHeader._colorMapOrigin, 2);
            inputFile.read((char*)&outputImage._imageHeader._colorMapLength, 2);
            inputFile.read(&outputImage._imageHeader._colorMapDepth, 1);
            inputFile.read((char*)&outputImage._imageHeader._xOrigin, 2);
            inputFile.read((char*)&outputImage._imageHeader._yOrigin, 2);
            inputFile.read((char*)&outputImage._imageHeader._width, 2);
            inputFile.read((char*)&outputImage._imageHeader._height, 2);
            inputFile.read(&outputImage._imageHeader._bitsPerPixel, 1);
            inputFile.read(&outputImage._imageHeader._imageDescriptor, 1);

      	//Read Pixel Data
            for (int i = 0; i < (outputImage._imageHeader._width * outputImage._imageHeader._height); i++) {
                Pixel tempPixel;    
                
                /*
                Some reason only works when do uncommented code:
                    inputFile.read((char*)&tempPixel._redData, 1);
                    inputFile.read((char*)&tempPixel._greenData, 1);
                    inputFile.read((char*)&tempPixel._blueData, 1);
                */

                inputFile.read((char*)&tempPixel._blueData, 1);
                inputFile.read((char*)&tempPixel._greenData, 1);
                inputFile.read((char*)&tempPixel._redData, 1);

                outputImage._pixelData.push_back(tempPixel);
            }

			inputFile.close();
	}

    return outputImage;
}

void imageManipulation::writeImageData(Image data, string filePath) {
    ofstream inputFile(filePath, ios_base::binary);
  
    if (inputFile.is_open()) {
        inputFile.write(&data._imageHeader._idLength, 1);
        inputFile.write(&data._imageHeader._colorMapType, 1);
        inputFile.write(&data._imageHeader._dataTypeCode, 1);
        inputFile.write((char*)&data._imageHeader._colorMapOrigin, 2);
        inputFile.write((char*)&data._imageHeader._colorMapLength, 2);
        inputFile.write(&data._imageHeader._colorMapDepth, 1);
        inputFile.write((char*)&data._imageHeader._xOrigin, 2);
        inputFile.write((char*)&data._imageHeader._yOrigin, 2);
        inputFile.write((char*)&data._imageHeader._width, 2);
        inputFile.write((char*)&data._imageHeader._height, 2);
        inputFile.write(&data._imageHeader._bitsPerPixel, 1);
        inputFile.write(&data._imageHeader._imageDescriptor, 1);

        for (unsigned int i = 0; i < data._pixelData.size(); i++) {
            Pixel tempPixel = data._pixelData.at(i);

            /*
            Some reason only works when do uncommented code:
                inputFile.write((char*)&tempPixel._redData, 1);
                inputFile.write((char*)&tempPixel._greenData, 1);
                inputFile.write((char*)&tempPixel._blueData, 1);
            */

            inputFile.write((char*)&tempPixel._blueData, 1);
            inputFile.write((char*)&tempPixel._greenData, 1);
            inputFile.write((char*)&tempPixel._redData, 1);
        }

        inputFile.close();
    }
}
