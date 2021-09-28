#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "auxiliares.h"
//#include<windows.h>
//#include<winbase.h>
//#include<psapi.h>

/*double get_memory_used_MB()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}*/

void insercaoPorCor(int *array, int n, int cor, int h){
    for (int i = (h + cor); i < n; i+=h) {
        int tmp = array[i];
        int j = i - h;
        while ((j >= 0) && (array[j] > tmp)) {
            array[j + h] = array[j];
            j-=h;
        }
        array[j + h] = tmp;
    }
}

void shellsort(int *array, int n) {
    int h = 1;

    do { h = (h * 3) + 1; } while (h < n);

    do {
        h /= 3;
        for(int cor = 0; cor < h; cor++){
            insercaoPorCor(array, n, cor, h);
        }
    } while (h != 1);
}

int main(){
    srand(time(NULL));
    int i,n=2048000;
    clock_t inicio,fim;
    double total;
    //double memory_used;
    //size_t peakSize;

    for(i=1024;i<=n;i*=2){
        int *vetor = malloc(i*sizeof(int));

        /*preencheVetorOrdenado(vetor, i);
        inicio = clock();
        shellsort(vetor, i);
        fim = clock();
       // memory_used = get_memory_used_MB();
        //printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);*/

        preencheVetorNaoOrdenado(vetor, i);
        inicio = clock();
        shellsort(vetor, i);
        fim = clock();
        //memory_used = get_memory_used_MB();
        //printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        /*preencheVetorAleatorio(vetor, i);
        inicio = clock();
        shellsort(vetor, i);
        fim = clock();
        //memory_used = get_memory_used_MB();
        //printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);*/

        free(vetor);
    }
    return 0;
}