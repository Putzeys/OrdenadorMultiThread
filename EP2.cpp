#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 32767

int ordena(int tam, int tipo, int vetor[]);

void quickSort(int *a, int left, int right);

void swap(int *xp, int *yp); 

void selectionSort(int arr[], int n);

char* readFile(char caminho[]);

bool writeFile(char caminho[], char mensagem[]);

int tamanhoArquivo(char caminho[]);

int* charToIntVet(char *vetor, int n);

char* intToCharVet (int* vetor, int n);

typedef struct {
    int nome[MAX];
	int tamanho;
} VETOR;

int main(int argc, char** argv) {
	
	
	char arquivo[] = "C:/Users/natha/OneDrive/Documentos/4� ano - 2� semestre/Arquitetura/EP2/ArquivoTeste.txt";
//	char *texto = "3 8 1 0";
//	writeFile(arquivo, texto);
	
	char *retorno;
	retorno = readFile(arquivo); // guardando string do arquivo
	int tam = tamanhoArquivo(arquivo);
		
//	alterando de string para int[]
	int *armazem;
	armazem = charToIntVet(retorno, tam);
	int novoTam = tam - (tam/2);
	printf("\n");
	for (int i = 0; i < novoTam; i++) {
		printf("%d ", armazem[i]);
	}
		
	ordena(tam, 0, armazem);
	char* resposta = intToCharVet(armazem, tam);
	writeFile(arquivo, resposta);
//	readFile(arquivo);
	
	return 0;
}



char* intToCharVet (int* vetor, int n) {
	char resp[n];
	for (int i = 0; i < n; i++) {
		char ch = vetor[i] + 48;
		resp[i] = ch;
	}
	return resp;
}


int* charToIntVet(char *vetor, int n) {
	int array[MAX];
	int tamanho = 0;
	int numCasas = 0;
	for (int i = 0; i < n; i++) {
	    numCasas++;
		    
	    if (vetor[i] == ' ') {
	    	numCasas--;
	        int valorTotal = 0;
		        
	        for (int j = 1; j <= numCasas; j++) {
		        	
	        	int pot = 1;
	        	for(int p = 0; p < j-1; p++){
	        		pot = pot * 10;
	        	}
		        	
	        	int ij = i-j;
	        	int charPraInt = vetor[ij]-48;
	        	int valorParcial = charPraInt * pot;
	        	valorTotal = valorTotal + valorParcial;
				// System.out.println(valorTotal);
				// valorTotal += charPraInt * Math.pow(10, j);
	        }
		        
	        array[tamanho] = valorTotal;
	        tamanho++;
	        valorTotal = 0;
	        numCasas = 0;
	    }
		    
	}
	
	return array;
}

int tamanhoArquivo(char caminho[]) {
	char ch;
	char elem[MAX];
	int n = 0;
	FILE *arq;
 
 	arq = fopen(caminho, "r");
 	if(arq == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
 	else
    	while( (ch=fgetc(arq))!= EOF ) {
    		elem[n] = ch;
    		n++;
		}
 	fclose(arq);
 	return n;
}



char* readFile(char caminho[]) {
	char ch;
	char elem[MAX];
	int n = 0;
	FILE *arq;
 
 	arq = fopen(caminho, "r");
 	if(arq == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
 	else
    	while( (ch=fgetc(arq))!= EOF ) {
    		elem[n] = ch;
    		n++;
			putchar(ch);
		}
 	fclose(arq);
 	return elem;
}

bool writeFile(char caminho[], char mensagem[]) {
	FILE *arq;
	arq = fopen(caminho, "wt");  // Cria um arquivo texto para grava��o
	if (arq == NULL) // Se n�o conseguiu criar
	{
   		printf("Problemas na CRIACAO do arquivo\n");
   		return false;
	}

	int result = fputs(mensagem, arq);
	if (result == EOF)
    	printf("Erro na Gravacao\n");
	fclose(arq);
}


// tipo = 0   -->  selectionSort
// tipo = 1   -->  quickSort
int ordena(int tam, int tipo, int vetor[]) {
	if (tipo==0) {
		selectionSort(vetor, tam);
	} else {
		quickSort(vetor, 0, tam-1);
	}
	return tam;
} 




// SelectioSort
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 

    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 

        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
    } 
}



// Quick sort function
void quickSort(int *a, int left, int right) {
    int i, j, x, y;

    i = left;
    j = right;
    x = a[(left + right) / 2];

    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quickSort(a, left, j);
    }
    if(i < right) {
        quickSort(a, i, right);
    }
}
