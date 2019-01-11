#ifndef _GED_CONTOURS_H_
#define _GED_CONTOURS_H_

#include "EdgeMap.h"

/// Initialize Look Up Tables (LUTs);
void InitEDLib();

/// Detects the contours by combining the GrayEDV results at multiple scales. Returns a soft contour map
EdgeMap *GEDContours(unsigned char *srcImg, int width, int height, int GRADIENT_THRESH=30);

/// Detects the contours by combining the GrayEDV results at multiple scales. After detection, thresholds the imaeg at the given cutoffThreshold and returns the thresholded binary contour map
EdgeMap *GEDContours_BW(unsigned char *srcImg, int width, int height, int GRADIENT_THRESH=30, int cutoffThresh=252);

#endif