#include <opencv2/opencv.hpp>
#include "stdio.h"

//Define constantes para diferentes resoluções de imagem
#define ROWS 4320
#define COLS 8640

//Define numero de vezes a rodar o mesmo algoritmo
#define TIMESTORUN 10000

double getUnixTime();
void calculateMatrix(int, int);

/*
 *Esse código foi usado para obtenção estatistica dos valores de tempo
 *da execução do algoritmo, uma vez que com repetições demasiadamente 
 *grandes os valores tendem a um valor especifico como é característica
 *da curva normal.
*/

int main(int argc, char const *argv[])
{
    double total_time = 0, average_time;
    double start_time, stop_time, difference;
    int rows = ROWS, cols = COLS;
    FILE* arq;
    arq = fopen("timevalues.txt", "w");

    for (int i = 0; i < TIMESTORUN; ++i)
    {
        start_time = getUnixTime();
        calculateMatrix(rows, cols);
        stop_time = getUnixTime();
        difference = stop_time - start_time;
        fprintf(arq, "%lf\n", difference);      
        printf("done %d\n", i);
    }

    fclose(arq);
    return 0;
}

void calculateMatrix(int rows, int cols){
    cv::Mat Image(rows, cols, CV_8U);
    uchar* p; 
    for (int i = 0; i < Image.rows; ++i)
    {
        p = Image.ptr<uchar>(i);
        for (int j = 0; j < Image.cols; ++j)
            p[j] = ((i*j) % 256);
    }
}

double getUnixTime()
{
    struct timespec tv;

    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;

    return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}