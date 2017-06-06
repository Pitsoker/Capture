//capture -w [img_width] -h [img_height] -d [imgs_directory] -e [file_extension]
//g++ `pkg-config --cflags opencv` capture.cpp `pkg-config --libs opencv` -o capture

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"


using namespace std;
using namespace cv;

//int x = 0;

int main(int argc, char const *argv[])
{
  char* imgs_directory;
  char* extension;
  int im_width, im_height;
  int x;

  static struct poptOption options[] = {
    { "img_width",'w',POPT_ARG_INT,&im_width,0,"Image width","NUM" },
    { "img_height",'h',POPT_ARG_INT,&im_height,0,"Image height","NUM" },
    { "imgs_directory",'d',POPT_ARG_STRING,&imgs_directory,0,"Directory to save images in","STR" },
    { "extension",'e',POPT_ARG_STRING,&extension,0,"Image extension","STR" },
    { "number",'n',POPT_ARG_INT,&x,0,"Image number","NUM" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0, NULL, NULL }
  };

  POpt popt(NULL, argc, argv, options, 0);
  int c;
  while((c = popt.getNextOpt()) >= 0) {}

  VideoCapture cap1(0);
  Mat img1, img_res1;
  while (1) {
    cap1 >> img1;
    resize(img1, img_res1, Size(im_width, im_height));
    imshow("IMG1", img_res1);
    if (waitKey(30) > 0) {
      x++;
      char filename1[200];
      sprintf(filename1, "%simg%d.%s", imgs_directory, x, extension);
      cout << "Capturing img number " << x << endl;
      imwrite(filename1, img_res1);
    }
  }
  return 0;
}
