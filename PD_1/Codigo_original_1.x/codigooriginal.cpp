#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main()
{
  IplImage *cvImg; // Objeto usado para armazenar a imagem
   CvSize imgSize; 
   int i1 = 0, j1 = 0;
   imgSize.width = 640; 
   imgSize.height = 480;  
 
   cvImg = cvCreateImage( imgSize, 8, 1 );

   for ( i1 = 0; i1 < imgSize.width; i1++ )
       for ( j1 = 0; j1 < imgSize.height; j1++ )
           ((uchar*)(cvImg->imageData + cvImg->widthStep*j1))[i1] = ( char ) ( ( i1 * j1 ) % 256 );
   cvNamedWindow( "Abrindo a Imagem Gerada...", 1 );
   cvShowImage( "Abrindo a Imagem Gerada...", cvImg );
   cvWaitKey( 4000 );
   cvDestroyWindow( "image" );
   cvReleaseImage( &cvImg );
}