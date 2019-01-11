#ifndef _COLOREDLIB_H_
#define _COLOREDLIB_H_

#include "EdgeMap.h"

/// Initialize some LUTs within the ColorEDLib
void InitColorEDLib();

///-------------------------- GRAY ED BELOW ------------------------------------------------
/// Detect Edges by Edge Drawing (ED). smoothingSigma must be >= 1.0
EdgeMap *GrayED(unsigned char *srcImg, int width, int height, GradientOperator op=PREWITT_OPERATOR, int GRADIENT_THRESH=20, int ANCHOR_THRESH=4, double smoothingSigma=1.0);

/// Detect Edges by Edge Drawing (ED) and validate the resulting edge segments. smoothingSigma must be >= 1.0
EdgeMap *GrayEDV(unsigned char *srcImg, int width, int height, GradientOperator op=PREWITT_OPERATOR, int GRADIENT_THRESH=20, double smoothingSigma=1.0);

/// Detect Edges by Edge Drawing Parameter Free (EDPF). smoothingSigma must be >= 1.0
EdgeMap *GrayEDPF(unsigned char *srcImg, int width, int height, double smoothingSigma=1.0);

///-------------------------- COLOR ED BELOW ------------------------------------------------
/// Detect Edges by Edge Drawing (ED) for color images represented by ch1Img, ch2Img and ch3Img. Uses the multi-image gradient method by DiZenzo for gradient computation. smoothingSigma must be >= 1.0
EdgeMap *ColorED(unsigned char *redImg, unsigned char *greenImg, unsigned char *blueImg, int width, int height, int GRADIENT_THRESH=20, int ANCHOR_THRESH=4, double smoothingSigma=1.5);

/// ColorED with Validation. smoothingSigma must be >= 1.0
EdgeMap *ColorEDV(unsigned char *redImg, unsigned char *greenImg, unsigned char *blueImg, int width, int height, int GRADIENT_THRESH=20, double smoothingSigma=1.5);

/// ColorEDPF. smoothingSigma must be >= 1.0
EdgeMap *ColorEDPF(unsigned char *redImg, unsigned char *greenImg, unsigned char *blueImg, int width, int height, double smoothingSigma=1.0);

///-------------------------- COLORCANNY BELOW ---------------------------------------------
unsigned char *ColorCanny(unsigned char *redImg, unsigned char *greenImg, unsigned char *blueImg, int width, int height, int lowThresh, int highThresh, double smoothingSigma);

#endif