#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "auxiliares.h"
#include<windows.h>
#include<winbase.h>
#include<psapi.h>

double get_memory_used_MB()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}

void bolha(int *array, int n){
    int i, j;
    for (i = (n - 1); i > 0; i--) {
      for (j = 0; j < i; j++) {
         if (array[j] > array[j + 1]) {
            troca(&array[j], &array[j + 1]);
         }
      }
   }
}

int main(){
    srand(time(NULL));
    int i,n=256000;
    clock_t inicio,fim;
    double total;
    double memory_used;
    size_t peakSize;

    for(i=1024;i<=n;i*=2){
        int *vetor = malloc(i*sizeof(int));
        preencheVetorOrdenado(vetor, i);
        inicio = clock();
        bolha(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorNaoOrdenado(vetor, i);
        inicio = clock();
        bolha(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorAleatorio(vetor, i);
        inicio = clock();
        bolha(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        free(vetor);
   }
    return 0;
}