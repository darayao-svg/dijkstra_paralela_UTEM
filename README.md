# Implementación Paralela del Algoritmo de Dijkstra

## Descripción
Este proyecto implementa el algoritmo de Dijkstra para encontrar caminos más cortos en grafos, paralelizado con OpenMP. El programa recibe una matriz de adyacencia como entrada y calcula las distancias mínimas desde un nodo origen.

## Estructura del Proyecto
dijkstra-paralelo/
├── src/
│ ├── main.c # Programa principal
│ ├── dijkstra.c # Implementación de Dijkstra
│ └── dijkstra.h # Cabeceras
├── Makefile # Instrucciones de compilación
└── README.md # Este archivo

## Requisitos
Compilador GCC con OpenMP
Sistema operativo Linux/Windows

## Compilación ```bash```
gcc -Wall -Wextra -g -fopenmp src/main.c src/dijkstra.c -o programa

## Ejecucion
./programa "[matriz]" nodo_inicio salida.txt

## Ejemplo
./programa "[[0,10,0,0,5],[0,0,1,0,2],[0,0,0,4,0],[7,0,6,0,0],[0,3,9,2,0]]" 0 resultados.txt

## Salida Esperada
Archivo resultados.txt:
Vertice Distancia
0 0
1 8
2 9
3 7
4 5

## Verificación de Paralelización
El programa muestra en consola los hilos trabajando:
Hilo 0 actualizando nodo 1
Hilo 1 actualizando nodo 3
Hilo 2 actualizando nodo 5
...
