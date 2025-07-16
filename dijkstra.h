#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int **parse_graph(const char *input, int *nodes);
void dijkstra_parallel(int **graph, int nodes, int start, int *dist);
void save_results(const char *filename, int *dist, int nodes);

#endif