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

void constroi(int *array, int tamHeap){
    for(int i = tamHeap; i > 1 && array[i] > array[i/2]; i /= 2){
        troca(array + i, array + i/2);
    }
}
//=============================================================================
int getMaiorFilho(int *array, int i, int tamHeap){
    int filho;
    if (2*i == tamHeap || array[2*i] > array[2*i+1]){
        filho = 2*i;
    } else {
        filho = 2*i + 1;
    }
    return filho;
}
//=============================================================================
void reconstroi(int *array, int tamHeap){
    int i = 1;
    while(i <= (tamHeap/2)){
        int filho = getMaiorFilho(array, i, tamHeap);
        if(array[i] < array[filho]){
            troca(array + i, array + filho);
            i = filho;
        }else{
            i = tamHeap;
        }
    }
}
//=============================================================================
void heapsort(int *array, int n) {
    //Alterar o vetor ignorando a posicao zero
    // int arrayTmp[n+1];
    int *arrayTmp = (int*) malloc((n+1)*sizeof(int));
    for(int i = 0; i < n; i++){
        arrayTmp[i+1] = array[i];
    }

    //Contrucao do heap
    for(int tamHeap = 2; tamHeap <= n; tamHeap++){
        constroi(arrayTmp, tamHeap);
    }

    //Ordenacao propriamente dita
    int tamHeap = n;
    while(tamHeap > 1){
        troca(arrayTmp + 1, arrayTmp + tamHeap--);
        reconstroi(arrayTmp, tamHeap);
    }

    //Alterar o vetor para voltar a posicao zero
    for(int i = 0; i < n; i++){
        array[i] = arrayTmp[i+1];
    }
    free(arrayTmp);
}
//=============================================================================

int main(){
    srand(time(NULL));
    int i,n=400000000000000;
    clock_t inicio,fim;
    double total;
    double memory_used;
    size_t peakSize;

    for(i=1024;i<=n;i*=2){
        int *vetor = malloc(i*sizeof(int));
        preencheVetorOrdenado(vetor, i);
        inicio = clock();
        heapsort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorNaoOrdenado(vetor, i);
        inicio = clock();
        heapsort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorAleatorio(vetor, i);
        inicio = clock();
        heapsort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        free(vetor);
    }
    return 0;
}