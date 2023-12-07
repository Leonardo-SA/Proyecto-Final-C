#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Universidad de Costa Rica
Facultad de Ingenieria
Escuela de Ingenieria Electrica
Programacion bajo plataformas abiertas
Prof: Julian Gairaud
David Rodriguez Gutierrez / B59281
Vincer Solis Hernandez / B87702
Leonardo Serrano Arias / C17484

Proyecto 2 de C

Introduccion:
El presente codigo de C recibe las coordenadas bidimensionales de los vertices 
de un poligono convexo de n lados y calcula sus angulos internos.   
*/

int main() {

    // Creamos una variable vertices para almacenar la cantidad de vertices y una variable 
    // n para almacenar el numero de vertice a ingresar. 
    int vertices;
    int n;

    // Solicitamos el numero de vertices del poligono
    printf("Ingrese la cantidad de vertices del poligono: \n");
    scanf(" %d", &vertices);
    
    // Colocamos una excepcion para un numero de vertices menos a tres

    if (vertices < 3) {
        printf("El numero de vertices debe ser igual o mayor a 3...Saliendo... \n");
        exit(0);
    }

    // Creamos dos arreglos del tamano vertices para almacenar las coordenadas ingresadas
    float x[vertices];
    float y[vertices];

    // Creamos dos arreglos del tamano vertices para almacenar las rectas

    float rectasX[vertices];
    float rectasY[vertices];

    // Creamos un arreglo para guardar el angulo formado entre las rectas
    float angulos[vertices];

    printf("\nAntes de ingresar las coordenadas, favor enumere los vertices consecutivamente siguiendo cualquier trayectoria haste cerrar el poligono.\n");
    printf("Puede tomar cualquiera de los vertices como el primero.\n");

    // Con un for, se ingresa n veces los vertices
    for (int i = 0; i < vertices; i++) {

        // Los vertices pueden ingresarse aleatoriamente mas sin embargo, necesitamos por fuerza
        // mayor que se ingresen los vertices enumerados para saber cual va conectado con cual
        printf("\nIngrese el numero de vertice que desea: \n");
        scanf(" %d", &n);
        
        printf("\nIngrese las coordenadas X,Y del vertice %d: \n", n);
        scanf(" %f, %f", &x[n-1], &y[n-1]);

    }

        // Imprimimos las coordenadas ingresadas
        printf("\nCoordenadas ingresadas:\n");
        for (int i = 0; i < vertices; i++) {
            printf("Vertice %d: (%.2f, %.2f)\n", i + 1, x[i], y[i]);
        }

    // Calculamos las rectas

    for (int i = 0; i < vertices-1 ; i++) {

        float rectaX = x[i+1]-x[i];
        rectasX[i]= rectaX;

        float rectaY = y[i+1]-y[i];
        rectasY[i]= rectaY;

    }

    // Para el ultimo vertice es especial dado que se calcula con el primero

    float rectaX = x[0]-x[vertices-1];
    rectasX[vertices-1]= rectaX;

    float rectaY = y[0]-y[vertices-1];
    rectasY[vertices-1]= rectaY;


    // Ya con las rectas podemos calcular los angulos

    // Para el primer vertice es distinto

    float coscita = (rectasX[0] * -rectasX[vertices-1] + rectasY[0] * -rectasY[vertices-1]) /
                            (sqrt(rectasX[0] * rectasX[0] + rectasY[0] * rectasY[0]) *
                            sqrt(rectasX[vertices-1] * rectasX[vertices-1] +
                                rectasY[vertices-1] * rectasY[vertices-1]));

    angulos[0] = acos(coscita) * (180.0 / M_PI);


    // Para los demas vertices

    for (int i = 0; i < vertices - 1; i++) {

        float coscita = (rectasX[i] * -rectasX[i+1] + rectasY[i] * -rectasY[i+1]) /
                            (sqrt(rectasX[i] * rectasX[i] + rectasY[i] * rectasY[i]) *
                            sqrt(rectasX[i+1] * rectasX[i+1] +
                                rectasY[i+1] * rectasY[i+1]));

        angulos[i+1] = acos(coscita) * (180.0 / M_PI);

        }

    
    // Calculamos las suma de los angulos internos

    float suma = 0;

    for (int i = 0; i < vertices; i++) {

        suma = suma + angulos[i];

    }

    // Calculamos la totalidad de grados teorica 

    float teorica = (vertices-2)*180;
    
    // Realizamos una comparacion entre la suma y la teorica para ver si es convexo a no

    if (suma != teorica) {
        printf("El poligono no es convexo... Saliendo...\n");
        exit(0);
    }
    
    
    // Mostramos los resultados
    
    printf("\nÁngulos calculados:\n");
        for (int i = 0; i < vertices; i++) {

            printf("El angulo en el vertice %d es de %.2f grados\n", i+1, angulos[i]);

        }
    
    return 0;

    }
