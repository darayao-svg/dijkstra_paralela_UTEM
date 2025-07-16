#include "dijkstra.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Uso: %s \"[matriz]\" inicio salida.txt\n", argv[0]);
        return 1;
    }

    int nodes;
    int **graph = parse_graph(argv[1], &nodes);
    int start = atoi(argv[2]);

    printf("Matriz leida (%dx%d):\n", nodes, nodes);
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            printf("%3d ", graph[i][j]);
        }
        printf("\n");
    }

    int *dist = (int *)malloc(nodes * sizeof(int));
    dijkstra_parallel(graph, nodes, start, dist);

    save_results(argv[3], dist, nodes);

    // Liberar memoria
    for (int i = 0; i < nodes; i++)
        free(graph[i]);
    free(graph);
    free(dist);

    return 0;
}