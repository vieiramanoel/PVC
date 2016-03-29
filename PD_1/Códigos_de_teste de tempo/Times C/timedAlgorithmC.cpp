#include "highgui.h" 
#include "cv.h" 
#include <stdio.h>

//Define constantes para diferentes resoluções de imagem
#define WIDTH 8640
#define HEIGHT 4320

//Define numero de vezes a rodar o mesmo algoritmo
#define TIMESTORUN 10000

double getUnixTime();
void calculateMatrix();

int main(int argc, char const *argv[])
{
    double total_time = 0, average_time;
    double start_time, stop_time, difference;
    int i;
    FILE* arq;
    arq = fopen("timevaluesC.txt", "w");

    for (i = 0; i < TIMESTORUN; ++i)
    {
        start_time = getUnixTime();
        calculateMatrix();
        stop_time = getUnixTime();
        difference = stop_time - start_time;
        fprintf(arq, "%lf\n", difference);      
        printf("done %d\n", i);
    }

    fclose(arq);
    return 0;
}

void calculateMatrix(){
  IplImage *cvImg; // Objeto usado para armazenar a imagem
  CvSize imgSize;
  int i1 = 0, j1 = 0;
  imgSize.width = WIDTH;
  imgSize.height = HEIGHT;
  cvImg = cvCreateImage( imgSize, 8, 1 );
  for ( i1 = 0; i1 < imgSize.width; i1++ )
    for ( j1 = 0; j1 < imgSize.height; j1++ )
      ((uchar*)(cvImg->imageData + cvImg->widthStep*j1))[i1] = ( char ) ( ( i1 * j1 ) % 256 );  
  cvNamedWindow( "Abrindo a Imagem Gerada...", 1 );
  cvShowImage( "Abrindo a Imagem Gerada...", cvImg );
  cvDestroyWindow( "image" );
  cvReleaseImage( &cvImg );
}

double getUnixTime()
{
    struct timespec tv;

    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;

    return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}