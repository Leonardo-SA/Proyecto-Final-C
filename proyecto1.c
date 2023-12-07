//Vincer Solis Hernadez B87702, Leonardo Serrano Arias C17484, David Rodriguez Gutierrez B59281

//Este programa toma una matriz dada por el usuario de un tamano dado por el usuario

//y determina el camino mas corto entre x y y ciudad definida por el usuario

// en donde se buscan todos los caminos posibles y se determina el mas corto

//y este luego se imprime junto al recorrido que tiene se tiene que hacer.



#include <stdio.h>

#include <limits.h>

#include <string.h>

#include <stdlib.h>



#define MAX_CITIES 100

#define MAX_CITY_NAME_LENGTH 50



char cityNames[MAX_CITIES][MAX_CITY_NAME_LENGTH];

int distance[MAX_CITIES][MAX_CITIES];



// Estructura para representar una ruta

typedef struct Route {

    int city;

    struct Route* next;

} Route;



void printRoute(Route* route, char cityNames[MAX_CITIES][MAX_CITY_NAME_LENGTH]) {

    if (route != NULL) {

        printRoute(route->next, cityNames);

        printf("%s -> ", cityNames[route->city]);

    }

}



void findShortestPath(int n, char startCity[], char endCity[]) {

    int start = -1, end = -1;



    // Encontrar los índices correspondientes a las ciudades de inicio y destino

    for (int i = 0; i < n; i++) {

        if (strcmp(cityNames[i], startCity) == 0) {

            start = i;

        }

        if (strcmp(cityNames[i], endCity) == 0) {

            end = i;

        }

    }



    if (start == -1 || end == -1) {

        printf("Ciudades de inicio o destino no válidas.\n");

        return;

    }



    int shortestDistance[MAX_CITIES][MAX_CITIES];



    // Inicializar la matriz de distancias más cortas

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            shortestDistance[i][j] = distance[i][j];

        }

    }



    // Matriz para almacenar los nodos intermedios en el camino más corto

    int intermediate[MAX_CITIES][MAX_CITIES];

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            intermediate[i][j] = (i != j && distance[i][j] != -1) ? i : -1;

        }

    }



    // Calcular las distancias más cortas sin utilizar algoritmo de grafos

    for (int k = 0; k < n; k++) {

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (i != j && shortestDistance[i][k] != -1 && shortestDistance[k][j] != -1) {

                    int throughK = shortestDistance[i][k] + shortestDistance[k][j];

                    if (throughK < shortestDistance[i][j] || shortestDistance[i][j] == -1) {

                        shortestDistance[i][j] = throughK;

                        intermediate[i][j] = intermediate[k][j];

                    }

                }

            }

        }

    }



    // Construir la ruta

    Route* route = NULL;

    Route* current = NULL;

    int currentCity = end;

    while (currentCity != start) {

        Route* newNode = (Route*)malloc(sizeof(Route));

        newNode->city = currentCity;

        newNode->next = NULL;



        if (current == NULL) {

            route = newNode;

            current = newNode;

        } else {

            current->next = newNode;

            current = newNode;

        }



        currentCity = intermediate[start][currentCity];

        if (currentCity == -1) {

            // No hay ruta posible

            printf("No hay ruta posible entre las ciudades %s y %s.\n", startCity, endCity);

            return;

        }

    }



    printf("La distancia más corta entre las ciudades %s y %s es: %d\n", startCity, endCity, shortestDistance[start][end]);

    printf("Ruta tomada: %s -> ", startCity);

    printRoute(route, cityNames);

    printf("%s\n", endCity);



    // Liberar la memoria de la ruta

    while (route != NULL) {

        Route* nextNode = route->next;

        free(route);

        route = nextNode;

    }

}



int main() {

    int n;

    printf("Ingrese la cantidad de ciudades: ");

    scanf("%d", &n);



    printf("Ingrese los nombres de las ciudades:\n");

    for (int i = 0; i < n; i++) {

        printf("Nombre de la ciudad %d: ", i);

        scanf("%s", cityNames[i]);

    }



    printf("Ingrese las distancias entre las ciudades (usar -1 si no hay camino):\n");

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            printf("Distancia entre la ciudad %s y la ciudad %s: ", cityNames[i], cityNames[j]);

            scanf("%d", &distance[i][j]);

            distance[j][i] = distance[i][j]; // La matriz es simétrica

        }

    }



    char startCity[MAX_CITY_NAME_LENGTH];

    char endCity[MAX_CITY_NAME_LENGTH];



    printf("Ingrese la ciudad de inicio: ");

    scanf("%s", startCity);



    printf("Ingrese la ciudad destino: ");

    scanf("%s", endCity);



    findShortestPath(n, startCity, endCity);



    return 0;

}

