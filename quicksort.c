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

void quicksortRec(int *array, int esq, int dir) {
    int i = esq, j = dir;
    int pivo = array[(dir+esq)/2];
    while (i <= j) {
        while (array[i] < pivo) i++;
        while (array[j] > pivo) j--;
        if (i <= j) {
            troca(array + i, array + j);
            i++;
            j--;
        }
    }
    if (esq < j)  quicksortRec(array, esq, j);
    if (i < dir)  quicksortRec(array, i, dir);
}

void quicksort(int *array, int n) {
    quicksortRec(array, 0, n-1);
}

int main(){
    srand(time(NULL));
    int i,n=2048000;
    clock_t inicio,fim;
    double total;
    //double memory_used;
   // size_t peakSize;

    for(i=1024;i<=n;i*=2){
        int *vetor = malloc(i*sizeof(int));

        preenchePiorCasoQuick(vetor, i);
        inicio = clock();
        quicksort(vetor, i);
        fim = clock();
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        /*preencheVetorNaoOrdenado(vetor, i);
        inicio = clock();
        quicksort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);


        preencheVetorAleatorio(vetor, i);
        inicio = clock();
        quicksort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);*/

        free(vetor);
    }
    return 0;
}