#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_CRIT 6
#define RI 1.41
#define CI(l) (l - N_CRIT) / (N_CRIT - 1)
#define CR(ci) ci / RI

typedef struct Criterio Criterio;
struct Criterio {
    char *c;
    float val;
};

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

void generarResultados(FILE *file, MatCriterios *mat, Criterio *criterios, char cmatriz);
void fprint_matriz(FILE *file,Criterio *criterios);
void fprint_arreglo(FILE *file, float *arr, Criterio *criterios); 
MatCriterios crear_matriz_criterios(Criterio *criterios);
void calcular_vector_propio(MatCriterios *matCriterios, int max_iter);
float lambda_max(float *prom, float *vector);
float *calcular_vector(float *prom, float **mat);
float *calcular_promedios(float **mat);
float **crear_matriz(Criterio *criterios);
void print_matriz(Criterio *criterios);
void print_arreglo(float *arr, Criterio *criterios);
float *calcular_promedios_criterios(float *vecA, float *vecB, float *vecC);
void imprimirResultados(MatCriterios *mat, Criterio *criterios, char cmatriz);
void ordenar_vector_propio(float *vecPropio, Criterio *criterios);

int main() 
{
    FILE *fileA = fopen("resultados_A.txt", "w");
    FILE *fileB = fopen("resultados_B.txt", "w");
    FILE *fileC = fopen("resultados_C.txt", "w");

    if (fileA == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo\n");
        return 1; // Sale del programa con un código de error
    }
    
    if (fileB == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo\n");
        return 1; // Sale del programa con un código de error
    }

    if (fileC == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo\n");
        return 1; // Sale del programa con un código de error
    }

    int i;

    Criterio A[N_CRIT] = {
        // "c1",   9,
        "c2",   9,
        // "c3",   9,
        "c4",   4,
        "c5",   5,
        "c6",   8,
        "c7",   9,
        "c8",   8,  
    };
    Criterio B[N_CRIT] = {
        // "c1",   9,
        "c2",   5,
        // "c3",   9,
        "c4",   8,
        "c5",   4,
        "c6",   8,
        "c7",   4,
        "c8",   3,  
    };
    Criterio C[N_CRIT] = {
        // "c1",   9,
        "c2",   4,
        // "c3",   9,
        "c4",   6,
        "c5",   5,
        "c6",   9,
        "c7",   7,
        "c8",   5,  
    };
	// A = {9,9,9,4,5,8,9,8};
	// B = {9,5,9,8,4,8,4,3};
	// C = {9,4,9,6,5,9,7,5};

    // SE ELIMINAN LOS CRITERIOS 1 y 3 PARA REDUCIR REDUNDANCIA

    MatCriterios MatrizA = crear_matriz_criterios(A);
    generarResultados(fileA, &MatrizA, A, 'A');
    // imprimirResultados(&MatrizA, A, 'A');
    MatCriterios MatrizB = crear_matriz_criterios(B);
    generarResultados(fileB, &MatrizB, B, 'B');
    // imprimirResultados(&MatrizB, B, 'B');
    MatCriterios MatrizC = crear_matriz_criterios(C);
    generarResultados(fileC, &MatrizC, C, 'C');
    // imprimirResultados(&MatrizC, C, 'C');

    return 0;
}

MatCriterios crear_matriz_criterios(Criterio *criterios) {   

    MatCriterios matriz = {crear_matriz(criterios)};
    matriz.Promedios = calcular_promedios(matriz.Matriz);
    matriz.Vector = calcular_vector(matriz.Promedios, matriz.Matriz);
    matriz.lambdaMax = lambda_max(matriz.Promedios, matriz.Vector);
    matriz.ci = CI(matriz.lambdaMax);
    matriz.cr = CR(matriz.ci);
    calcular_vector_propio(&matriz, 5); 

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
        norma += vecPropActual[i] * vecPropActual[i];
    }
    norma = sqrt(norma);
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

float **crear_matriz(Criterio *criterios) {

	int i,j;
    float **matrix;

    matrix = malloc(sizeof(float *) * N_CRIT);

    for(i = 0; i < N_CRIT; i++)
        matrix[i] = malloc(sizeof(float) * N_CRIT);

	for(i = 0; i < N_CRIT; i++)
		for(j = 0; j < N_CRIT; j++)
			matrix[i][j] = criterios[i].val/criterios[j].val;

    return matrix;
}

void print_matriz(Criterio *criterios) {
    int i, j;
    for (i = 0; i < N_CRIT; i++) {
        printf("[  ");
        for (j = 0; j < N_CRIT; j++)
            printf("%.2f  ", criterios[i].val / criterios[j].val);
        printf("]\n");
    }
}

void print_arreglo(float *arr, Criterio *criterios) {
    int i;
    for (i = 0; i < N_CRIT; i++) {
        printf("%s", criterios[i].c);
        printf(" %.3f", arr[i]);
        printf("\n");
    }
}

void imprimirResultados(MatCriterios *mat, Criterio *criterios, char cmatriz) {
    int i;

    printf("\nCriterios %c:\n", cmatriz);
    printf("[ ");
    for (i = 0; i < N_CRIT; i++) {
        printf("%s\t", criterios[i].c);
    }
    printf("]\n[ ");
    for (i = 0; i < N_CRIT; i++) {
        printf("%.0f\t", criterios[i].val);
    }
    printf("]");
    printf("\n");
    printf("\nMatriz de Comparacion de Parejas:\n", cmatriz);
    print_matriz(criterios);
    printf("\nPromedios de la Matriz %c:\n", cmatriz);
    print_arreglo(mat->Promedios, criterios);
    printf("\nVector de Fila Total de Matriz %c:\n", cmatriz);
    print_arreglo(mat->Vector, criterios);
    printf("\nLambda Max de %c: %.4f", cmatriz, mat->lambdaMax);
    printf("\nCI de %c: %.4f", cmatriz, mat->ci);
    printf("\nCR de %c: %.4f", cmatriz, mat->cr);
    printf("\n\nVector Propio de %c:\n", cmatriz);
    ordenar_vector_propio(mat->VecProp, criterios);
    print_arreglo(mat->VecProp, criterios);

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


void generarResultados(FILE *file, MatCriterios *mat, Criterio *criterios, char cmatriz) {
    int i;

    fprintf(file, "Criterios %c:\n", cmatriz);
    fprintf(file,"[ ");
    for (i = 0; i < N_CRIT; i++) {
        fprintf(file,"%s\t", criterios[i].c);
    }
    fprintf(file,"]\n[ ");
    for (i = 0; i < N_CRIT; i++) {
        fprintf(file,"%.0f\t", criterios[i].val);
    }
    fprintf(file,"]");
    fprintf(file,"\n");
    fprintf(file,"\nMatriz de Comparacion de Parejas:\n", cmatriz);
    fprint_matriz(file, criterios);
    fprintf(file,"\nPromedios de la Matriz %c:\n", cmatriz);
    fprint_arreglo(file, mat->Promedios, criterios);
    fprintf(file,"\nVector de Fila Total de Matriz %c:\n", cmatriz);
    fprint_arreglo(file, mat->Vector, criterios);
    fprintf(file,"\nLambda Max de %c: %.4f", cmatriz, mat->lambdaMax);
    fprintf(file,"\nCI de %c: %.4f", cmatriz, mat->ci);
    fprintf(file,"\nCR de %c: %.4f", cmatriz, mat->cr);
    fprintf(file,"\n\nVector Propio de %c:\n", cmatriz);
    ordenar_vector_propio(mat->VecProp, criterios);
    fprint_arreglo(file, mat->VecProp, criterios);

    for (i = 0; i < N_CRIT; i++) {
        free(mat->Matriz[i]);
    }

    fclose(file);
}

void fprint_matriz(FILE *file,Criterio *criterios) {
    int i, j;
    for (i = 0; i < N_CRIT; i++) {
        fprintf(file, "[  ");
        for (j = 0; j < N_CRIT; j++)
            fprintf(file,"%.2f  ", criterios[i].val / criterios[j].val);
        fprintf(file,"]\n");
    }
}

void fprint_arreglo(FILE *file, float *arr, Criterio *criterios) {
    int i;
    for (i = 0; i < N_CRIT; i++) {
        fprintf(file,"%s", criterios[i].c);
        fprintf(file," %.3f", arr[i]);
        fprintf(file,"\n");
    }
}

void ordenar_vector_propio(float *vecPropio, Criterio *criterios) {
    int i, j;
    float temp;
    Criterio tempCriterio;

    for (i = 0; i < N_CRIT-1; i++) {
        for (j = 0; j < N_CRIT-i-1; j++) {
            if (vecPropio[j] < vecPropio[j + 1]) {
                temp = vecPropio[j];
                vecPropio[j] = vecPropio[j+1];
                vecPropio[j+1] = temp;

                // También cambiamos los criterios correspondientes
                tempCriterio = criterios[j];
                criterios[j] = criterios[j+1];
                criterios[j+1] = tempCriterio;
            }
        }
    }
}