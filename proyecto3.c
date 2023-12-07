// Leonardo Serrano Arias C17484
// Vincer Solis Hernandez B87702
// David Rodriguez Gutierrez B59281

/*
Funcionamiento del programa:
El programa solicita al usuario ciertos datos para crear una matriz.
El usuario debe ingresar la cantidad de filas y columnas y los números de cada posición.
La función del programa retorna 0 si no hay errores y -1 si hubo algún error.
El programa devuelve las direcciones de memoria de los números que inician cada fila.
El programa presenta verificación de errores.
*/

#include <stdio.h>
#include <stdlib.h>

// Definición de la función
int ingresarPosicionesMatriz(float ***matriz, int *filas, int *columnas, float ***direcciones);

int main() {
    // Declaración de variables para el número de filas y columnas en la matriz
    int filas, columnas;
    
    // Declaración de punteros para la matriz y las direcciones de memoria
    float **matriz; // Declaración de la matriz
    float **direcciones; // Declaración de las direcciones

    // Llamar a la función que devuelve las direcciones de los números que inician cada fila
    int resultado = ingresarPosicionesMatriz(&matriz, &filas, &columnas, &direcciones);

    // Verificar si la función de entrada de datos fue exitosa (resultado igual a 0)
    if (resultado == 0) {
        // Imprimir las direcciones de memoria del primer elemento de cada fila
        printf("\nDirecciones de memoria del primer elemento de cada fila:\n");
        for (int i = 0; i < filas; i++) {
            printf("Fila %d -> Primer elemento: %p\n", i + 1, (void *)direcciones[i]);
        }

        // Liberar la memoria asignada para cada fila de la matriz
        for (int i = 0; i < filas; i++) {
            free(matriz[i]);
        }
        // Liberar la memoria asignada para la matriz
        free(matriz);
        // Liberar la memoria asignada para las direcciones
        free(direcciones);
    } else {
        // Imprimir mensaje de error si hubo un problema durante la entrada de datos
        printf("Hubo un error durante la entrada de datos.\n");
    }

    return 0;
}

// Función para ingresar dimensiones y valores de una matriz y obtener direcciones de memoria por fila
int ingresarPosicionesMatriz(float ***matriz, int *filas, int *columnas, float ***direcciones) {
    // Solicitar al usuario las dimensiones de la matriz
    printf("Ingrese el número de filas de la matriz: ");
    // Verificar si la entrada del usuario para las filas es un número positivo
    if (scanf("%d", filas) != 1 || *filas <= 0) {
        // Error: La entrada no es un número positivo
        return -1;
    }

    printf("Ingrese el número de columnas de la matriz: ");
    // Verificar si la entrada del usuario para las columnas es un número positivo
    if (scanf("%d", columnas) != 1 || *columnas <= 0) {
        // Error: La entrada no es un número positivo
        return -1;
    }

    // Asignar dinámicamente memoria para la matriz
    *matriz = (float **)malloc(*filas * sizeof(float *));

    // Verificar si hubo un error al asignar memoria
    if (*matriz == NULL) {
        // Error al asignar memoria
        return -1;
    }

    // Asignar dinámicamente memoria para las direcciones
    *direcciones = (float **)malloc(*filas * sizeof(float *));

    // Verificar si hubo un error al asignar memoria
    if (*direcciones == NULL) {
        // Error al asignar memoria
        free(*matriz);
        return -1;
    }

    // Llenar la matriz con números ingresados por el usuario y obtener las direcciones
    for (int i = 0; i < *filas; i++) {
        printf("Ingrese los %d números para la fila %d: ", *columnas, i + 1);

        // Asignar dinámicamente memoria para cada fila de la matriz
        (*matriz)[i] = (float *)malloc(*columnas * sizeof(float));

        // Verificar si hubo un error al asignar memoria
        if ((*matriz)[i] == NULL) {
            // Error al asignar memoria para la fila
            // Liberar memoria asignada previamente
            for (int j = 0; j < i; j++) {
                free((*matriz)[j]);
            }
            free(*matriz);
            free(*direcciones);
            return -1;
        }

        // Asignar las direcciones de memoria de cada fila a *direcciones
        (*direcciones)[i] = (*matriz)[i];

        // Leer y almacenar los números ingresados por el usuario en la fila
        for (int j = 0; j < *columnas; j++) {
            if (scanf("%f", &(*matriz)[i][j]) != 1) {
                // Error: La entrada no es un número
                // Liberar memoria asignada previamente
                for (int k = 0; k <= i; k++) {
                    free((*matriz)[k]);
                }
                free(*matriz);
                free(*direcciones);
                return -1;
            }
        }
    }

    return 0; // Éxito
}
