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


void mergesort(int *array, int n) {
   mergesortRec(array, 0, n-1);
}

void mergesortRec(int *array, int esq, int dir){
   if (esq < dir){
      int meio = (esq + dir) / 2;
      mergesortRec(array, esq, meio);
      mergesortRec(array, meio + 1, dir);
      intercalar(array, esq, meio, dir);
   }
}
void intercalar(int* array, int esq, int meio, int dir){
   int n1, n2, i, j, k;

   //Definir tamanho dos dois subarrays
   n1 = meio-esq+1;
   n2 = dir - meio;

   int* a1 = (int*) malloc((n1+1) * sizeof(int)); 
   int* a2 = (int*) malloc((n2+1) * sizeof(int));

   //Inicializar primeiro subarray
   for(i = 0; i < n1; i++){
      a1[i] = array[esq+i];
   }

   //Inicializar segundo subarray
   for(j = 0; j < n2; j++){
      a2[j] = array[meio+j+1];
   }

   //Sentinela no final dos dois arrays
   a1[i] = a2[j] = 0x7FFFFFFF;

   //Intercalacao propriamente dita
   for(i = j = 0, k = esq; k <= dir; k++){
      array[k] = (a1[i] <= a2[j]) ? a1[i++] : a2[j++];
   }
}

int main(){
    srand(time(NULL));
    int i,n=2048000;
    clock_t inicio,fim;
    double total;
    double memory_used;
    size_t peakSize;

    for(i=1024;i<=n;i*=2){
        int *vetor = malloc(i*sizeof(int));
        
        preencheVetorOrdenado(vetor, i);
        inicio = clock();
        mergesort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorNaoOrdenado(vetor, i);
        inicio = clock();
        mergesort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        //printf("%d | %.05f\n",i,total);

        preencheVetorAleatorio(vetor, i);
        inicio = clock();
        mergesort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        free(vetor);
    }
    return 0;
}