#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "imageManipulation.h"

int main(){
	imageManipulation i;
	i.writeImageData(i.divideImagesLineByLine(i.readImageData("input/readbetweenthelines.tga"), 0, 2), "output/gator.tga");
	i.writeImageData(i.divideImagesLineByLine(i.readImageData("input/readbetweenthelines.tga"), 1, 2), "output/flag.tga");
}