#ifndef _CED_CONTOURS_H_
#define _CED_CONTOURS_H_

#include "EdgeMap.h"

/// Detects the contours by combining the ColorEDV results at multiple scales. Returns a soft contour map
EdgeMap *CEDContours_DiZenzo(unsigned char *redImg, unsigned char *greenImg, unsigned char *blueImg, int width, int height, int GRADIENT_THRESH=32);

/// Detects the contours by combining the ColorEDV results at multiple scales. After detection, thresholds the imaeg at the given cutoffThreshold and returns the thresholded binary contour map
EdgeMap *CEDContours_DiZenzoBW(unsigned char *redImg, unsigned char *greenImg, unsigned char *blueImg, int width, int height, int GRADIENT_THRESH=32, int cutoffThresh=200);

#endif