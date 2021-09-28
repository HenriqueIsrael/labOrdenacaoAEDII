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

int getMaior(int *array, int n) {
    int maior = array[0];

    for (int i = 0; i < n; i++) {
        if(maior < array[i]){
            maior = array[i];
        }
    }
    return maior;
}
//=============================================================================
void countingsort(int *array, int n) {
    //Array para contar o numero de ocorrencias de cada elemento
    int tamCount = getMaior(array, n) + 1;
    int *count = (int*) malloc(tamCount*sizeof(int));
    int *ordenado = (int*) malloc(n*sizeof(int));

    //Inicializar cada posicao do array de contagem 
    for (int i = 0; i < tamCount; count[i] = 0, i++);

    //Agora, o count[i] contem o numero de elemento iguais a i
    for (int i = 0; i < n; count[array[i]]++, i++);

    //Agora, o count[i] contem o numero de elemento menores ou iguais a i
    for(int i = 1; i < tamCount; count[i] += count[i-1], i++);

    //Ordenando
    for(int i = n-1; i >= 0; ordenado[count[array[i]]-1] = array[i], count[array[i]]--, i--);

    //Copiando para o array original
    for(int i = 0; i < n; array[i] = ordenado[i], i++);
    free(count);
    free(ordenado);
}

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
        countingsort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorNaoOrdenado(vetor, i);
        inicio = clock();
        countingsort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        preencheVetorAleatorio(vetor, i);
        inicio = clock();
        countingsort(vetor, i);
        fim = clock();
        memory_used = get_memory_used_MB();
        printf("%f\n",memory_used);
        total = ((fim-inicio)/(double)CLOCKS_PER_SEC);
        printf("%d | %.05f\n",i,total);

        free(vetor);
    }
    return 0;
}