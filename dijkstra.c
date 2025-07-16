#include "dijkstra.h"
#include <omp.h>
#include <string.h>

int **parse_graph(const char *input, int *nodes)
{
    const char *p = input;
    int count = 0;

    while (*p)
        if (*p++ == '[')
            count++;
    *nodes = count - 1;

    int **graph = (int **)malloc(*nodes * sizeof(int *));
    for (int i = 0; i < *nodes; i++)
    {
        graph[i] = (int *)malloc(*nodes * sizeof(int));
    }

    p = input + 1;
    int row = 0;

    while (*p && row < *nodes)
    {
        while (*p == ' ' || *p == '[')
            p++;

        int col = 0;
        while (*p != ']' && col < *nodes)
        {
            while (*p == ' ' || *p == ',')
                p++;

            char *end;
            graph[row][col] = (int)strtol(p, &end, 10);
            p = end;
            col++;
        }

        while (*p != '[' && *p != '\0')
            p++;
        row++;
    }

    return graph;
}

void dijkstra_parallel(int **graph, int nodes, int start, int *dist)
{
    int *visited = (int *)malloc(nodes * sizeof(int));

    // Configurar número de hilos
    int num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);
    printf("\nConfigurado para usar %d hilos\n", num_threads);

// Inicialización paralela
#pragma omp parallel for
    for (int i = 0; i < nodes; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
#pragma omp critical
        {
            printf("Hilo %d inicializando nodo %d\n",
                   omp_get_thread_num(), i);
        }
    }
    dist[start] = 0;

    printf("\nIniciando Dijkstra...\n");

    for (int count = 0; count < nodes - 1; count++)
    {
        // Encontrar mínimo
        int min_dist = INT_MAX;
        int min_node = -1;

        for (int v = 0; v < nodes; v++)
        {
            if (!visited[v] && dist[v] < min_dist)
            {
                min_dist = dist[v];
                min_node = v;
            }
        }

        if (min_node == -1)
            break;
        visited[min_node] = 1;

// Actualizar distancias en paralelo
#pragma omp parallel for
        for (int v = 0; v < nodes; v++)
        {
            if (!visited[v] && graph[min_node][v] > 0)
            {
                int new_dist = dist[min_node] + graph[min_node][v];
                if (new_dist < dist[v])
                {
                    dist[v] = new_dist;
                }
#pragma omp critical
                {
                    printf("Hilo %d actualizo nodo %d (distancia: %d)\n",
                           omp_get_thread_num(), v, dist[v]);
                }
            }
        }
    }

    free(visited);
    printf("\nProceso completado.\n");
}

void save_results(const char *filename, int *dist, int nodes)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error al crear archivo");
        exit(1);
    }

    fprintf(file, "Vertice Distancia\n");
    for (int i = 0; i < nodes; i++)
    {
        fprintf(file, "%d %d\n", i, dist[i]);
    }

    fclose(file);
}