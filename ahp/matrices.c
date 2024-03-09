#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_CRIT 8
#define RI 1.41
#define CI(l) (l - N_CRIT) / (N_CRIT - 1)
#define CR(ci) ci / RI

typedef struct MatCriterios MatCriterios;
struct MatCriterios {
    float **Matriz;
    float *Promedios;
    float *Vector;
    float ci;
    float cr;
    float lambdaMax;
    float *VecProp;
};

MatCriterios crear_matriz_criterios(float *arr);
void calcular_vector_propio(MatCriterios *matCriterios, int max_iter);
float lambda_max(float *prom, float *vector);
float *calcular_vector(float *prom, float **mat);
float *calcular_promedios(float **mat);
float **crear_matriz(float *arr);
void print_matriz(float **mat);
void print_arreglo(float *arr);
float *calcular_promedios_criterios(float *vecA, float *vecB, float *vecC);
void imprimirResultados(MatCriterios *mat, char matriz);
float *ordenar_criterios(float *criterios);

int main() 
{
    int i;

	float A[N_CRIT] = {9,9,9,4,5,8,9,8};
	float B[N_CRIT] = {9,5,9,8,4,8,4,3};
	float C[N_CRIT] = {9,4,9,6,5,9,7,5};

    float Criterios[N_CRIT];

    for (int i=0; i<N_CRIT; i++){
        Criterios[i] = (A[i]+B[i]+C[i])/3;
    }

    printf("Criterios:\n");
    print_arreglo(Criterios);

    MatCriterios MatA = crear_matriz_criterios(A);

    printf("\n\n");

    MatCriterios Matriz_Criterios = crear_matriz_criterios(Criterios);
    
    return 0;
}

MatCriterios crear_matriz_criterios(float *arr) {        
    MatCriterios matriz = {crear_matriz(arr), NULL, NULL};
    matriz.Promedios = calcular_promedios(matriz.Matriz);
    matriz.Vector = calcular_vector(matriz.Promedios, matriz.Matriz);
    matriz.lambdaMax = lambda_max(matriz.Promedios, matriz.Vector);
    matriz.ci = CI(matriz.lambdaMax);
    matriz.cr = CR(matriz.ci);
    calcular_vector_propio(&matriz, 5); 
    imprimirResultados(&matriz, 'R');

    return matriz;
}

void calcular_vector_propio(MatCriterios *matCriterios, int max_iter) {
    int i, j, k;
    float epsilon = 0.0001;  // Criterio de convergencia
    float *vecPropAnterior, *vecPropActual;
    float norma;

    vecPropAnterior = malloc(sizeof(float) * N_CRIT);
    vecPropActual = malloc(sizeof(float) * N_CRIT);

    for (i = 0; i < N_CRIT; i++) {
        vecPropAnterior[i] = 1.0;
    }

    for (k = 0; k < max_iter; k++) {
        // Multiplicar la matriz por el vector propio anterior
        for (i = 0; i < N_CRIT; i++) {
            vecPropActual[i] = 0.0;
            for (j = 0; j < N_CRIT; j++) {
                vecPropActual[i] += matCriterios->Matriz[i][j] * vecPropAnterior[j];
            }
        }

        // Normalizar el vector propio actual
        norma = 0.0;
        for (i = 0; i < N_CRIT; i++) {
            norma += vecPropActual[i] * vecPropActual[i];
        }
        norma = sqrt(norma);

        for (i = 0; i < N_CRIT; i++) {
            vecPropActual[i] /= norma;
        }

        // Verificar la convergencia
        float diferencia = 0.0;
        for (i = 0; i < N_CRIT; i++) {
            diferencia += fabs(vecPropActual[i] - vecPropAnterior[i]);
        }

        if (diferencia < epsilon) {
            break;  // Convergencia alcanzada
        }

        // Actualizar el vector propio anterior con el actual
        for (i = 0; i < N_CRIT; i++) {
            vecPropAnterior[i] = vecPropActual[i];
        }
    }
    // Normalizar el vector propio final
    norma = 0.0;
    for (i = 0; i < N_CRIT; i++) {
        norma += vecPropActual[i];
    }
    for (i = 0; i < N_CRIT; i++) {
        vecPropActual[i] /= norma;
    }

    matCriterios->VecProp = vecPropActual;
    
    free(vecPropAnterior);
}

float lambda_max(float *prom, float *vector) {
    int i;

    float max = 0.0;
    float cociente;

    for (i = 0; i < N_CRIT; i++) {
        cociente = vector[i] / prom[i];
        if (cociente > max) max = cociente;
    }

    return max;
}

float *calcular_vector(float *prom, float **mat) {
    int i, j;

    float sum;

    float *vector;
    vector = malloc(sizeof(float) * N_CRIT);

    for (i = 0; i < N_CRIT; i++) {
        sum = 0;
        for (j = 0; j < N_CRIT; j++) {
            sum += mat[i][j] * prom[j];
        }
        vector[i] = sum;
    }

    return vector;
} 

float *calcular_promedios(float **mat) {
    int i, j;

    float *promedios;
    promedios = malloc(sizeof(float) * N_CRIT);

    // Sumas por cada columna
    float sumas_col[N_CRIT] = {0};
    for(i = 0; i < N_CRIT; i++)
        for(j = 0; j <N_CRIT; j++)
            sumas_col[i] += mat[j][i];

    // Normalización de la matriz
    float sumas_fil[N_CRIT] = {0};
    for(i = 0; i < N_CRIT; i++)
        for(j = 0; j < N_CRIT; j++)
            sumas_fil[i] += mat[i][j];

    // Creación de Promedios
    for(j = 0; j < N_CRIT; j++)
        promedios[j] = sumas_fil[j] / N_CRIT; 

    return promedios;   
        
}

float **crear_matriz(float *arr) {

	int i,j;
    float **matrix;

    matrix = malloc(sizeof(float *) * N_CRIT);

    for(i = 0; i < 8; i++)
        matrix[i] = malloc(sizeof(float) * N_CRIT);

	for(i = 0; i < N_CRIT; i++)
		for(j = 0; j < N_CRIT; j++)
			matrix[i][j] = arr[i]/arr[j];

    return matrix;
}

void print_matriz(float **mat) {
	int i,j;
	for(i = 0; i < N_CRIT; i++) {
		printf("[");
		for(j = 0; j < N_CRIT; j++)
			printf("%.3f, ", mat[i][j]);
		printf("]\n");
	}
}

void print_arreglo(float *arr) {
	int i;
	for(i = 0; i < N_CRIT; i++) {
		printf("C%d [", i+1);
		printf(" %.3f,", arr[i]);
		printf("]\n");
	}
}

void imprimirResultados(MatCriterios *mat, char matriz) {
    int i;

    printf("\nMatriz de Comparacion de Parejas %c:\n", matriz);
    print_matriz(mat->Matriz);
    printf("\nPromedios de la Matriz %c:\n", matriz);
    print_arreglo(mat->Promedios);
    printf("\nVector de Fila Total de Matriz %c:\n", matriz);
    print_arreglo(mat->Vector);
    printf("\nLambda Max de %c: %.4f", matriz, mat->lambdaMax);
    printf("\nCI de %c: %.4f", matriz, mat->ci);
    printf("\nCR de %c: %.4f", matriz, mat->cr);
    printf("\n\nVector Propio de %c:\n", matriz);
    print_arreglo(mat->VecProp);

    for (i = 0; i < N_CRIT; i++) {
        free(mat->Matriz[i]);
    }
    free(mat->Matriz);
    free(mat->Promedios);
    free(mat->Vector);
}

float *calcular_promedios_criterios(float *vecA, float *vecB, float *vecC) {
    int i;

    float *promedios;
    promedios = malloc(sizeof(float) * N_CRIT);

    for (i = 0; i < N_CRIT; i++) {
        promedios[i] = (vecA[i] + vecB[i] + vecC[i]) / 3.0;
    }

    return promedios;
}

float *ordenar_criterios(float *criterios){
    float *criterios_ordenados = malloc(sizeof(float) * N_CRIT);
    int i,j;
    for (int i = 0; i < N_CRIT; i++) {
        criterios_ordenados[i] = criterios[i];
    }

    float valor;
    for (i = 0; i < N_CRIT-1; i++) {
        for (j = 0; j < N_CRIT-i-1; j++){
            if (criterios_ordenados[j] < criterios_ordenados[j + 1]) {
                valor = criterios_ordenados[j];
                criterios_ordenados[j] = criterios_ordenados[j+1];
                criterios_ordenados[j+1] = valor;
            }          
        }
    }
    return criterios_ordenados;
}