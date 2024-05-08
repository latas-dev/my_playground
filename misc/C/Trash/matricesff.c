#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_CRIT 6
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
typedef struct Conjuntos Conjuntos;
struct Conjuntos {
    char *c;
    float *v;
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
void print_arreglo_multi(Conjuntos *conjunto);
void print_arreglo_m(float *arr);
MatCriterios crear_matriz_c(float *arr);
void ordenar_promedios_criterios(Conjuntos *promedioCriterios);
void print_arreglo_multi_dec(Conjuntos *conjunto);

int main() 
{
    int i;
    //Eliminacion de criterios 1 y 3
	float A[N_CRIT] = {9,4,5,8,9,8};
	float B[N_CRIT] = {5,8,4,8,4,3};
	float C[N_CRIT] = {4,6,5,9,7,5};
    char criterios[N_CRIT] = {'1', '2', '3', '4', '5', '6'};
    Conjuntos conjuntoA;
    conjuntoA.Criterio = criterios;
    conjuntoA.Valor = A;
    Conjuntos conjuntoB;
    conjuntoB.Criterio = criterios;
    conjuntoB.Valor = B;
    Conjuntos conjuntoC;
    conjuntoC.Criterio = criterios;
    conjuntoC.Valor = C;
    MatCriterios MatA = crear_matriz_c(conjuntoA.Valor);
    MatCriterios MatB = crear_matriz_c(conjuntoB.Valor);
    MatCriterios MatC = crear_matriz_c(conjuntoC.Valor);
    float *promedioscriterios = calcular_promedios_criterios(MatA.VecProp, MatB.VecProp, MatC.VecProp);
    Conjuntos promedioCriterios;
    promedioCriterios.Criterio = criterios;
    promedioCriterios.Valor = promedioscriterios;
    ordenar_promedios_criterios(&promedioCriterios);
    int opcion=1;
    
    while(opcion!=0){
        printf("\nSeleccione una opcion:\n");
        printf("0. Salir \n");
        printf("1. Imprimir Conjuntos (A,B,C) \n");
        printf("2. Imprimir Matriz de Comparacion de Parejas A \n");
        printf("3. Imprimir Matriz de Comparacion de Parejas B \n");
        printf("4. Imprimir Matriz de Comparacion de Parejas C \n");
        printf("5. Imprimir Peso de criterios\n");
        printf("\nIngrese una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("\nEntrada no valida. Intente nuevamente.\n");
            continue;  
        }
        switch (opcion)
        {
        case 0: 
            printf("\nSaliendo....\n");
        break;
        case 1:
            printf("\nConjunto A\n");
            print_arreglo_multi(&conjuntoA); 
            printf("\nConjunto B\n");
            print_arreglo_multi(&conjuntoB); 
            printf("\nConjunto C\n");
            print_arreglo_multi(&conjuntoC); 
            break;
        case 2:
            imprimirResultados(&MatA, 'A');
            break;
        case 3:
            imprimirResultados(&MatB, 'B');
            break;
        case 4:
            imprimirResultados(&MatC, 'C');
            break;
        case 5:
            printf("\nPeso de criterios\n");
            print_arreglo(promedioscriterios);
            printf("\nCriterios ordenados\n");
            print_arreglo_multi_dec(&promedioCriterios);
            break;
        
        default:
            printf("\nOpcion no valida \n");
            break;
        }
    }
    for (i = 0; i < N_CRIT; i++) {
        free(MatA.Matriz[i]);
    }
    free(MatA.Matriz);
    free(MatA.Promedios);
    free(MatA.Vector);
    free(MatA.VecProp);

    for (i = 0; i < N_CRIT; i++) {
        free(MatB.Matriz[i]);
    }
    free(MatB.Matriz);
    free(MatB.Promedios);
    free(MatB.Vector);
    free(MatB.VecProp);

    for (i = 0; i < N_CRIT; i++) {
        free(MatC.Matriz[i]);
    }
    free(MatC.Matriz);
    free(MatC.Promedios);
    free(MatC.Vector);
    free(MatC.VecProp);

    free(promedioscriterios);

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
    float sumas_col[N_CRIT];
    for(i = 0; i < N_CRIT; i++){
        sumas_col[i] = 0;
    }
    for(i = 0; i < N_CRIT; i++)
        for(j = 0; j <N_CRIT; j++)
            sumas_col[i] += mat[j][i];

    // Normalización de la matriz
    float sumas_fil[N_CRIT];
    for(i = 0; i < N_CRIT; i++){
        sumas_fil[i] = 0;
    }
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


void print_arreglo_multi(Conjuntos *conjunto) {
    int i;
    for(i = 0; i < N_CRIT; i++) {
        printf("C%c [", conjunto->Criterio[i]);
        printf(" %.0f", conjunto->Valor[i]);
        printf("]\n");
    }
}
void print_arreglo_multi_dec(Conjuntos *conjunto) {
    int i;
    for(i = 0; i < N_CRIT; i++) {
        printf("C%c [", conjunto->Criterio[i]);
        printf(" %.3f", conjunto->Valor[i]);
        printf("]\n");
    }
}
MatCriterios crear_matriz_c(float *arr) {
    MatCriterios matriz;
    matriz.Matriz = crear_matriz(arr);
    matriz.Promedios = calcular_promedios(matriz.Matriz);
    matriz.Vector = calcular_vector(matriz.Promedios, matriz.Matriz);
    matriz.lambdaMax = lambda_max(matriz.Promedios, matriz.Vector);
    matriz.ci = CI(matriz.lambdaMax);
    matriz.cr = CR(matriz.ci);
    calcular_vector_propio(&matriz, 5); 
    return matriz;
}

void ordenar_promedios_criterios(Conjuntos *promedioCriterios) {
    float *valores = promedioCriterios->Valor;
    char *criterios = promedioCriterios->Criterio;

    for (int i = 0; i < N_CRIT - 1; i++) {
        for (int j = 0; j < N_CRIT - i - 1; j++) {
            if (valores[j] < valores[j + 1]) {
                float temp_valor = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = temp_valor;

                char temp_criterio = criterios[j];
                criterios[j] = criterios[j + 1];
                criterios[j + 1] = temp_criterio;
            }
        }
    }
}
