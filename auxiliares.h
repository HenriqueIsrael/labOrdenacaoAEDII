#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void preencheVetorOrdenado(int *vetor, int n){
    for(int i=0;i<n;i++){
        vetor[i] = i;
    }
}

void preencheVetorAleatorio(int *vetor, int n){
    preencheVetorOrdenado(vetor, n);
    srand(time(NULL));
    for(int i=0;i<n;i++){
        troca(&vetor[i], &vetor[rand()%n]);
    }
}

void preencheVetorNaoOrdenado(int *vetor, int n){
    for(int i=0;i<n;i++){
        vetor[i] = n-1-i;
    }
}

void troca(int *i, int *j){
   int temp = *i;
   *i = *j;
   *j = temp;
}

void preenchePiorCasoQuick(int *vetor, int n){
    int i,j;
    for(i=0;i<n/2;i++){
        vetor[i] = i;
    }
    vetor[n/2] = i;
    for(i= i+1, j=vetor[(n/2)-1];i<n;i++,j--){
        vetor[i] = j;
    }
}