/**************************************************************************************************************
 * Disclaimer for ColorED Library
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
 * [1] C. Akinlar, C. Topal, "ColorED: Color Edge and Segment Detection by Edge Drawing (ED), 
 *     submitted to the Journal of Visual Communication and Image Representation
 **************************************************************************************************************/

/*************************************************************
 * Test code to repeat the experiments presented in the paper
 *************************************************************/
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "ColorEDLib.h"
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

/// Experiments presented in the paper
void Experiment_Fig1();
void Experiment_Fig3();
void Experiment_Fig4();
void Experiment_Fig5();
void Experiment_Fig7();

///------------------------------------------------------------------------------
/// Main function
/// 
int main(){
  InitColorEDLib(); // Initialize the ColorEDLib LUTs

  Experiment_Fig1();  // Do the experiment presented in Fig. 1
  Experiment_Fig3();  // Do the experiment presented in Fig. 3
  Experiment_Fig4();  // Do the experiment presented in Fig. 4
  Experiment_Fig5();  // Do the experiment presented in Fig. 5
  Experiment_Fig7();  // Do the experiment presented in Fig. 7

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

  if (ReadImagePPM("Fig1/checkerboard.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 24, 0, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <checkerboard> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());

  SaveEdgeMap("Fig1/checkerboard-ColorED.pgm", map);
  delete map;

  printf("\n");

  delete redImg;
  delete greenImg;
  delete blueImg;
} //end-Experiment_Fig1

///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 3 of the paper
///
void Experiment_Fig3(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;
  unsigned char *grayImg;

  printf("================= Experiment in Fig. 3 of the paper ====================\n");

  /************************************ Image: 295087 ************************************************/
  if (ReadImagePPM("Fig3/295087.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 60, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <295087> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/295087-ColorED.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  if (ReadImagePGM("Fig3/295087.pgm", (char **)&grayImg, &width, &height) == 0) return;

  timer.Start();
  map = GrayED(grayImg, width, height, PREWITT_OPERATOR, 44, 4, 1.5);   // Grayscale edge detection by GrayED
  timer.Stop();

  printf("GrayED  returns %3d edge segments for image <295087> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/295087-GrayED.pgm", map);
  delete map;

  delete grayImg;

  /************************************ Image: 69020 ************************************************/
  if (ReadImagePPM("Fig3/69020.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 80, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image  <69020> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/69020-ColorED.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  if (ReadImagePGM("Fig3/69020.pgm", (char **)&grayImg, &width, &height) == 0) return;

  timer.Start();
  map = GrayED(grayImg, width, height, PREWITT_OPERATOR, 60, 4, 1.5);   // Grayscale edge detection by GrayED
  timer.Stop();

  printf("GrayED  returns %3d edge segments for image  <69020> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/69020-GrayED.pgm", map);
  delete map;

  delete grayImg;

  /************************************ Image: 253027 ************************************************/
  if (ReadImagePPM("Fig3/253027.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 72, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <253027> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/253027-ColorED.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  if (ReadImagePGM("Fig3/253027.pgm", (char **)&grayImg, &width, &height) == 0) return;

  timer.Start();
  map = GrayED(grayImg, width, height, PREWITT_OPERATOR, 44, 4, 1.5);   // Grayscale edge detection by GrayED
  timer.Stop();

  printf("GrayED  returns %3d edge segments for image <253027> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/253027-GrayED.pgm", map);
  delete map;

  delete grayImg;

  /************************************ Image: 296059 ************************************************/
  if (ReadImagePPM("Fig3/296059.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 56, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <296059> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/296059-ColorED.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  if (ReadImagePGM("Fig3/296059.pgm", (char **)&grayImg, &width, &height) == 0) return;

  timer.Start();
  map = GrayED(grayImg, width, height, PREWITT_OPERATOR, 48, 4, 1.5);   // Grayscale edge detection by GrayED
  timer.Stop();

  printf("GrayED  returns %3d edge segments for image <296059> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig3/296059-GrayED.pgm", map);
  delete map;

  delete grayImg;

  printf("\n");
} //end-Experiment_Fig3

///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 4 of the paper
///
void Experiment_Fig4(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;
  unsigned char *edgeImg;

  printf("================= Experiment in Fig. 4 of the paper ====================\n");

  /************************************ Image: 385039 ************************************************/
  if (ReadImagePPM("Fig4/385039.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 48, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <385039> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig4/385039-ColorED.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 28, 56, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <385039> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig4/385039-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 260058 ************************************************/
  if (ReadImagePPM("Fig4/260058.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 60, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <260058> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig4/260058-ColorED.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <260058> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig4/260058-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 97033 ************************************************/
  if (ReadImagePPM("Fig4/97033.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 72, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <97033> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig4/97033-ColorED.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <97033> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig4/97033-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 42049 ************************************************/
  if (ReadImagePPM("Fig4/42049.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 96, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED returns %3d edge segments for image <42049> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig4/42049-ColorED.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 72, 144, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <42049> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig4/42049-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  printf("\n");
} //end-Experiment_Fig4

///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 5 of the paper
///
void Experiment_Fig5(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;
  unsigned char *edgeImg;

  printf("================= Experiment in Fig. 5 of the paper ====================\n");

  /************************************ Image: 69020 ************************************************/
  if (ReadImagePPM("Fig5/69020.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 36, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED  returns %3d edge segments for image <69020> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/69020-ColorED.pgm", map);
  delete map;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 36, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <69020> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/69020-ColorEDV.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 62096 ************************************************/
  if (ReadImagePPM("Fig5/62096.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 36, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED  returns %3d edge segments for image <62096> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/62096-ColorED.pgm", map);
  delete map;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 36, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <62096> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/62096-ColorEDV.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 85048 ************************************************/
  if (ReadImagePPM("Fig5/85048.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 36, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED  returns %3d edge segments for image <85048> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/85048-ColorED.pgm", map);
  delete map;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 36, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <85048> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/85048-ColorEDV.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: Noise-050 ************************************************/
  if (ReadImagePPM("Fig5/Noise-050.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorED(redImg, greenImg, blueImg, width, height, 36, 4, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorED  returns %3d edge segments for image <Noise-050> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/Noise-050-ColorED.pgm", map);
  delete map;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 36, 1.5);   // Color edge detection by ColorED
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <Noise-050> and takes %5.2lf ms\n", map->noSegments, timer.ElapsedTime());
  SaveEdgeMap("Fig5/Noise-050-ColorEDV.pgm", map);
  delete map;

  delete redImg;
  delete greenImg;
  delete blueImg;

  printf("\n");
} //end-Experiment_Fig5

///---------------------------------------------------------------------------
/// Do the experiment presented in Fig. 7 of the paper
///
void Experiment_Fig7(){
  EdgeMap *map = NULL;
  Timer timer;

  int width, height;
  unsigned char *redImg, *greenImg, *blueImg;
  unsigned char *edgeImg;

  printf("================= Experiment in Fig. 7 of the paper ====================\n");

  /************************************ Image: 296059-10 ************************************************/
  if (ReadImagePPM("Fig7/296059-10.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 48, 1.5);   // Color edge detection by ColorEDV
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <296059-10> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig7/296059-10-ColorEDV.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <296059-10> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig7/296059-10-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 296059-20 ************************************************/
  if (ReadImagePPM("Fig7/296059-20.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 48, 1.5);   // Color edge detection by ColorEDV
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <296059-20> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig7/296059-20-ColorEDV.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <296059-20> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig7/296059-20-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 296059-30 ************************************************/
  if (ReadImagePPM("Fig7/296059-30.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 48, 1.5);   // Color edge detection by ColorEDV
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <296059-30> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig7/296059-30-ColorEDV.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <296059-30> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig7/296059-30-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 296059-40 ************************************************/
  if (ReadImagePPM("Fig7/296059-40.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 48, 1.5);   // Color edge detection by ColorEDV
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <296059-40> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig7/296059-40-ColorEDV.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <296059-40> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig7/296059-40-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  /************************************ Image: 296059-50 ************************************************/
  if (ReadImagePPM("Fig7/296059-50.ppm", &width, &height, &redImg, &greenImg, &blueImg) == false) return;

  timer.Start();
  map = ColorEDV(redImg, greenImg, blueImg, width, height, 48, 1.5);   // Color edge detection by ColorEDV
  timer.Stop();

  printf("ColorEDV returns %3d edge segments for image <296059-50> and takes %5.2lf ms\n", map->noSegments,   timer.ElapsedTime());
  SaveEdgeMap("Fig7/296059-50-ColorEDV.pgm", map);
  delete map;

  timer.Start();
  edgeImg = ColorCanny(redImg, greenImg, blueImg, width, height, 48, 96, 1.5);   // Color edge detection by ColorCanny
  timer.Stop();

  printf("ColorCanny for image <296059-50> takes %5.2lf ms\n", timer.ElapsedTime());
  SaveImagePGM("Fig7/296059-50-ColorCanny.pgm", (char *)edgeImg, width, height);
  delete edgeImg;

  delete redImg;
  delete greenImg;
  delete blueImg;

  printf("\n");
} //end-Experiment_Fig7

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
