/**************************************************************************************************************
 * Disclaimer for CEDContours Library
 * 
 * This software library is provided "as is" and "with all faults." Authors of this library make 
 * no warranties of any kind concerning the safety, suitability, lack of viruses, inaccuracies, 
 * typographical errors, or other harmful components of this software product. There are inherent 
 * dangers in the use of any software, and you are solely responsible for determining whether this 
 * software product is compatible with your equipment and other software installed on your equipment. 
 * You are also solely responsible for the protection of your equipment and backup of your data, 
 * and the authors of this software product will not be liable for any damages you may suffer in 
 * connection with using, modifying, or distributing this software product. 
 *
 * You are allowed to use this library for scientific research only. 
 *
 * By using this library you are implicitly assumed to have accepted all of the above statements, 
 * and accept to cite the following paper:
 *
 * [1] C. Akinlar, "CEDContours: A High Speed Contour Detector for Color Images", 
 *     submitted to the Journal of Image and Vision Computing
 * [2] C. Akinlar, C. Topal, "ColorED: Color Edge and Segment Detection by Edge Drawing (ED)", 
 *     submitted to the Journal of Visual Communication and Image Representation
 **************************************************************************************************************/

/*************************************************************
 * Test code to repeat the experiments presented in the paper
 *************************************************************/
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "CEDContours.h"
#include "EdgeMap.h"
#include "Timer.h"

/// This code needs OpenCV2.1 DLLs to run (for cvSmooth function)
/// They have been copied to the current directory from OpenCV distribution
/// cv210.dll & cxcore210.dll
///

/// Two functions to read/save PGM files
int ReadImagePGM(char *filename, char **pBuffer, int *pWidth, int *pHeight);
void SaveImagePGM(char *filename, char *buffer, int width, int height);

/// One function to read PPM color image files
bool ReadImagePPM(char *filename, int *pWidth, int *pHeight, unsigned char **pRedImg, unsigned char **pGreenImg, unsigned char **pBlueImg);

/// One function to save an edgemap to a file
void SaveEdgeMap(char *filename, EdgeMap *map);

/// Initialize LUTs
void InitColorEDLib();

/// Experiments presented in the paper
void Experiment_Fig1();
void Experiment_Fig5();
void Experiment_Fig6();

///------------------------------------------------------------------------------
/// Main function
/// 
int main(){
  InitColorEDLib(); // Initialize the ColorEDLib LUTs

  Experiment_Fig1();  // Do the experiment presented in Fig. 1
  Experiment_Fig5();  // Do the experiment presented in Fig. 5
  Experiment_Fig6();  // Do the experiment presented in Fig. 6

  printf("Press ENTER to quit.\n");
  getchar();

  return 0;
} //end-main

///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 1 of the paper
///
void Experiment_Fig1(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;

  printf("================= Experiment in Fig. 1 of the paper ====================\n");

  ///--------------------------Image 385039 ----------------------------
  if (ReadImagePPM("Fig1/385039.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <385039> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig1/385039-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 92
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 92);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <385039>\n", map->noSegments);
  SaveEdgeMap("Fig1/385039-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  delete redImg;
  delete greenImg;
  delete blueImg;
} //end-Experiment_Fig1


///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 5 of the paper
///
void Experiment_Fig5(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;

  printf("================= Experiment in Fig. 5 of the paper ====================\n");

  ///--------------------------Image 253055 ----------------------------
  if (ReadImagePPM("Fig5/253055.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <253055> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/253055-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 180
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 180);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <253055>\n", map->noSegments);
  SaveEdgeMap("Fig5/253055-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 43074 ----------------------------
  if (ReadImagePPM("Fig5/43074.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <43074> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/43074-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 160
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 160);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <43074>\n", map->noSegments);
  SaveEdgeMap("Fig5/43074-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 216081 ----------------------------
  if (ReadImagePPM("Fig5/216081.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <216081> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/216081-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 92
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 92);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <216081>\n", map->noSegments);
  SaveEdgeMap("Fig5/216081-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 143090 ----------------------------
  if (ReadImagePPM("Fig5/143090.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <143090> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/143090-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 252
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 252);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <143090>\n", map->noSegments);
  SaveEdgeMap("Fig5/143090-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 145086 ----------------------------
  if (ReadImagePPM("Fig5/145086.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <145086> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/145086-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 208
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 208);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <145086>\n", map->noSegments);
  SaveEdgeMap("Fig5/145086-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 69020 ----------------------------
  if (ReadImagePPM("Fig5/69020.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <69020> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/69020-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 244
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 244);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <69020>\n", map->noSegments);
  SaveEdgeMap("Fig5/69020-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 148026 ----------------------------
  if (ReadImagePPM("Fig5/148026.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <148026> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig5/148026-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 244
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 244);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <148026>\n", map->noSegments);
  SaveEdgeMap("Fig5/148026-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  delete redImg;
  delete greenImg;
  delete blueImg;
} //end-Experiment_Fig5


///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 6 of the paper
///
void Experiment_Fig6(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;

  printf("================= Experiment in Fig. 5 of the paper ====================\n");

  ///--------------------------Image 277053 ----------------------------
  if (ReadImagePPM("Fig6/277053.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <277053> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/277053-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 172
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 172);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <277053>\n", map->noSegments);
  SaveEdgeMap("Fig6/277053-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 87015 ----------------------------
  if (ReadImagePPM("Fig6/87015.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <87015> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/87015-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 96
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 96);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <87015>\n", map->noSegments);
  SaveEdgeMap("Fig6/87015-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 368037 ----------------------------
  if (ReadImagePPM("Fig6/368037.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <368037> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/368037-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 88
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 88);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <368037>\n", map->noSegments);
  SaveEdgeMap("Fig6/368037-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 41085 ----------------------------
  if (ReadImagePPM("Fig6/41085.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <41085> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/41085-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 164
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 164);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <41085>\n", map->noSegments);
  SaveEdgeMap("Fig6/41085-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 112090 ----------------------------
  if (ReadImagePPM("Fig6/112090.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <112090> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/112090-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 84
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 84);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <112090>\n", map->noSegments);
  SaveEdgeMap("Fig6/112090-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 28083 ----------------------------
  if (ReadImagePPM("Fig6/28083.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <28083> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/28083-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 188
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 188);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <28083>\n", map->noSegments);
  SaveEdgeMap("Fig6/28083-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  ///--------------------------Image 2018 ----------------------------
  if (ReadImagePPM("Fig6/2018.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  // Gradient threshold = 32
  map = CEDContours_DiZenzo(redImg, greenImg, blueImg, width, height, 32);
  timer.Stop();

  printf("CEDContours_DiZenzo for <2018> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig6/2018-CEDContours-DiZenzo-Soft.pgm", (char *)map->edgeImg, width, height);
  delete map;

  // BW
  // Gradient threshold = 32, cutoffThreshold = 152
  map = CEDContours_DiZenzoBW(redImg, greenImg, blueImg, width, height, 32, 152);

  printf("CEDContours_DiZenzoBW returns %3d edge segments for image <2018>\n", map->noSegments);
  SaveEdgeMap("Fig6/2018-CEDContours-DiZenzo-BW.pgm", map);
  printf("\n");

  delete redImg;
  delete greenImg;
  delete blueImg;
} //end-Experiment_Fig6

/******************************************************************************
* Function: ReadImagePGM
* Purpose: This function reads in an image in PGM format. The image can be
* read in from either a file or from standard input. The image is only read
* from standard input when infilename = NULL. Because the PGM format includes
* the number of columns and the number of rows in the image, these are read
* from the file. Memory to store the image is allocated in this function.
* All comments in the header are discarded in the process of reading the
* image. Upon failure, this function returns 0, upon sucess it returns 1.
******************************************************************************/
int ReadImagePGM(char *filename, char **pBuffer, int *pWidth, int *pHeight){
   FILE *fp;
   char buf[71];
   int width, height;

   if ((fp = fopen(filename, "rb")) == NULL){
     fprintf(stderr, "Error reading the file %s in ReadImagePGM().\n", filename);
     return(0);
   } //end-if

   /***************************************************************************
   * Verify that the image is in PGM format, read in the number of columns
   * and rows in the image and scan past all of the header information.
   ***************************************************************************/
   fgets(buf, 70, fp);
   bool P2 = false;
   bool P5 = false;

   if      (strncmp(buf, "P2", 2) == 0) P2 = true;
   else if (strncmp(buf, "P5", 2) == 0) P5 = true;

   if (P2 == false && P5 == false){
      fprintf(stderr, "The file %s is not in PGM format in ", filename);
      fprintf(stderr, "ReadImagePGM().\n");
      fclose(fp);
      return 0;
   } //end-if

   do {fgets(buf, 70, fp);} while (buf[0] == '#');  /* skip all comment lines */
   sscanf(buf, "%d %d", &width, &height);
   fgets(buf, 70, fp);  // Skip max value (255)

   *pWidth = width;
   *pHeight = height;

   /***************************************************************************
   * Allocate memory to store the image then read the image from the file.
   ***************************************************************************/
   if (((*pBuffer) = (char *) malloc((*pWidth)*(*pHeight))) == NULL){
      fprintf(stderr, "Memory allocation failure in ReadImagePGM().\n");
      fclose(fp);
      return(0);
   } //end-if  

   if (P2){
      int index=0;
      char *p = *pBuffer;
      int col = 0;
      int read = 0;

      while (1){
        int c;
        if (fscanf(fp, "%d", &c) < 1) break;
        read++;

        if (col < *pWidth) p[index++] = (unsigned char)c;

        col++;
        if (col == width) col = 0;
      } //end-while

      if (read != width*height){
        fprintf(stderr, "Error reading the image data in ReadImagePGM().\n");
        fclose(fp);
        free((*pBuffer));
        return(0);
      } //end-if

   } else if (P5){
      int index=0;
      char *p = *pBuffer;
      int col = 0;
      int read = 0;

      while (1){
        unsigned char c;
        if (fread(&c, 1, 1, fp) < 1) break;
        read++;

        if (col < *pWidth) p[index++] = c;

        col++;
        if (col == width) col = 0;
      } //end-while

     if (read != width*height){
        fprintf(stderr, "Error reading the image data in ReadImagePGM().\n");
        fclose(fp);
        free((*pBuffer));
        return(0);
     } //end-if
   } //end-else

   fclose(fp);
   return 1;
} //end-ReadPGMImage

///---------------------------------------------------------------------------------
/// Save a buffer as a .pgm image
///
void SaveImagePGM(char *filename, char *buffer, int width, int height){
  FILE *fp = fopen(filename, "wb");

  // .PGM header
  fprintf(fp, "P5\n");
  fprintf(fp, "# Some comment here!\n");
  fprintf(fp, "%d %d\n", width, height);
  fprintf(fp, "255\n");

  // Grayscale image
  fwrite(buffer, 1, width*height, fp);

  fclose( fp );
} //end-SaveImagePGM

///-------------------------------------------------------------------------------------------------------------------------------------
/// Reads a PPM image. Returns true if the image is successfully read, false otherwise
///
bool ReadImagePPM(char *filename, int *pWidth, int *pHeight, unsigned char **pRedImg, unsigned char **pGreenImg, unsigned char **pBlueImg){
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) return false;

  char line[101];
  unsigned char *redImg = NULL;
  unsigned char *greenImg = NULL;
  unsigned char *blueImg = NULL;

  // Read the encoding
  bool binaryEncoding = false;
  fgets(line, 100, fp);
  if (strncmp(line, "P6", 2) == 0) binaryEncoding = true;

  // Read the width & height of the image
  int width = 0, height = 0;

  fgets(line, 100, fp);
  if (line[0] == '#') fgets(line, 100, fp);  // Skip the comment line if it exists
  sscanf(line, "%d %d", &width, &height);
  if (width == 0 || height == 0) goto PPMError;

  // Read and skip the next line
  fgets(line, 100, fp);

  // Allocate buffer for the images & read them
  redImg = new unsigned char[width*height];
  greenImg = new unsigned char[width*height];
  blueImg = new unsigned char[width*height];

  if (binaryEncoding){
    for (int i=0; i<width*height; i++){
      unsigned char c;

      if (fread(&c, 1, 1, fp) != 1) goto PPMError;
      redImg[i] = c;

      if (fread(&c, 1, 1, fp) != 1) goto PPMError;
      greenImg[i] = c;

      if (fread(&c, 1, 1, fp) != 1) goto PPMError;
      blueImg[i] = c;
    } //end-for

  } else {
    for (int i=0; i<width*height; i++){
      int c;

      if (fscanf(fp, "%d", &c) != 1) goto PPMError;
      redImg[i] = (unsigned char)c;

      if (fscanf(fp, "%d", &c) != 1) goto PPMError;
      greenImg[i] = (unsigned char)c;

      if (fscanf(fp, "%d", &c) != 1) goto PPMError;
      blueImg[i] = (unsigned char)c;
    } //end-for
  } //end-else

  fclose(fp);

  *pWidth = width;
  *pHeight = height;
  *pRedImg = redImg;
  *pGreenImg = greenImg;
  *pBlueImg = blueImg;

  return true;

PPMError:
  fclose(fp);
  if (redImg) delete redImg;
  if (greenImg)delete greenImg;
  if (blueImg) delete blueImg;

  return false;
} //end-ReadImagePPM

///--------------------------------------------------------------
/// Save the edge segments to a file
///
void SaveEdgeMap(char *filename, EdgeMap *map){
  int width = map->width;
  int height = map->height;

  memset(map->edgeImg, 0, width*height);
  for (int i=0; i<map->noSegments; i++){
    for (int j=0; j<map->segments[i].noPixels; j++){
      int r = map->segments[i].pixels[j].r;
      int c = map->segments[i].pixels[j].c;
      
      map->edgeImg[r*width+c] = 255;
    } //end-for
  } //end-for

  SaveImagePGM(filename, (char *)map->edgeImg, width, height);
} // end-SaveEdgeMap
