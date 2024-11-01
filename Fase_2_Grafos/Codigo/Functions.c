#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "stdbool.h"
#include <float.h>

#define INF FLT_MAX
/**
 * @file functions.c
 * @brief Este ficheiro contém a implementação das funções do sistema de grafos.
 * @author Alexandre Vilaça 26590
 * @date 25.05.2024
 */

Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->inicioGraph = NULL;
    graph->numVertices = 0;
    return graph;
}

Vertex *createVertex(int id)
{
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    if (vertex != NULL)
    {
        vertex->id = id;
        vertex->visited = false;
        vertex->nextAdjacent = NULL;
        vertex->nextVertex = NULL;
    }
    return vertex;
}

Adjacent *createAdjacent(int id, float dist)
{
    Adjacent *adj = (Adjacent *)malloc(sizeof(Adjacent));
    if (adj != NULL)
    {
        adj->id = id;
        adj->dist = dist;
        adj->next = NULL;
    }
    return adj;
}

Graph *addVertex(Graph *graph, int id)
{
    Vertex *newVertex = createVertex(id);
    if (newVertex == NULL)
        return NULL;
    newVertex->nextVertex = graph->inicioGraph;
    graph->inicioGraph = newVertex;
    graph->numVertices++;
    return graph;
}

Adjacent *addAdjacent(Vertex *vertex, int id, float dist)
{
    Adjacent *newAdjacent = createAdjacent(id, dist);
    if (newAdjacent == NULL)
        return NULL;
    if (id == vertex->id)
    {
        return NULL;
    }
    newAdjacent->next = vertex->nextAdjacent;
    vertex->nextAdjacent = newAdjacent;
    return newAdjacent;
}

Graph *readGraphFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    Graph *graph = createGraph();
    if (graph == NULL)
    {
        fclose(file);
        return NULL;
    }

    char line[100];
    int vertexId = 1;

    while (fgets(line, sizeof(line), file))
    {
        int adjacentId = 1;
        graph = addVertex(graph, vertexId);

        char *token;
        token = strtok(line, ";");
        while (token != NULL)
        {
            float dist = atof(token);
            addAdjacent(graph->inicioGraph, adjacentId, dist);
            token = strtok(NULL, ";");
            adjacentId++;
        }

        vertexId++;
    }
    fclose(file);
    return graph;
}
Graph* removeAdjacent(Graph *graph, int vertexId, int adjId)
{
    Vertex *vertex = findVertexById(graph, vertexId);
    if (vertex == NULL || vertex->nextAdjacent == NULL)
    {
        return false;
    }

    Adjacent *current = vertex->nextAdjacent;
    Adjacent *previous = NULL;

    while (current != NULL && current->id != adjId)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return false;
    }

    if (previous == NULL)
    {
        vertex->nextAdjacent = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free(current);
    return graph;
}

Graph* removeVertex(Graph *graph, int vertexId)
{
    if (graph == NULL || graph->inicioGraph == NULL)
    {
        return false;
    }

    Vertex *current = graph->inicioGraph;
    Vertex *previous = NULL;

    while (current != NULL && current->id != vertexId)
    {
        previous = current;
        current = current->nextVertex;
    }

    if (current == NULL)
    {
        return false;
    }

    Adjacent *adj = current->nextAdjacent;
    while (adj != NULL)
    {
        Adjacent *temp = adj;
        adj = adj->next;
        free(temp);
    }

    if (previous == NULL)
    {
        graph->inicioGraph = current->nextVertex;
    }
    else
    {
        previous->nextVertex = current->nextVertex;
    }

    free(current);
    graph->numVertices--;
    return graph;
}

bool updateAdjacentDistance(Graph *graph, int vertexId, int adjId, float newDist)
{
    Vertex *vertex = findVertexById(graph, vertexId);
    if (vertex == NULL)
    {
        return false;
    }

    Adjacent *adj = vertex->nextAdjacent;
    while (adj != NULL)
    {
        if (adj->id == adjId)
        {
            adj->dist = newDist;
            return true;
        }
        adj = adj->next;
    }

    return false;
}

Vertex *findVertexById(Graph *graph, int id)
{
    Vertex *vertex = graph->inicioGraph;
    while (vertex != NULL)
    {
        if (vertex->id == id)
        {
            return vertex;
        }
        vertex = vertex->nextVertex;
    }
    return NULL;
}

int DFSUtil(Graph *graph, Vertex *vertex, int path[], int pathLen, float currentDistance, int destinationId)
{
    if (vertex == NULL)
    {
        return 1;
    }
    vertex->visited = true;
    path[pathLen++] = vertex->id;

    if (vertex->id == destinationId)
    {
        printf("Path: ");
        for (int i = 0; i < pathLen; i++)
        {
            printf("%d ", path[i]);
        }
        printf("(Distance: %.2f)\n", currentDistance);
    }
    else
    {
        Adjacent *adj = vertex->nextAdjacent;
        while (adj != NULL)
        {
            Vertex *adjVertex = findVertexById(graph, adj->id);
            if (adjVertex != NULL && !adjVertex->visited && !adj->visited)
            {
                adj->visited = true;
                DFSUtil(graph, adjVertex, path, pathLen, currentDistance + adj->dist, destinationId);
                adj->visited = false;
            }
            adj = adj->next;
        }
    }
    vertex->visited = false;
    return 0;
}

int DFS(Graph *graph, int startVertexId, int destinationId)
{
    Vertex *startVertex = findVertexById(graph, startVertexId);
    if (startVertex == NULL)
    {
        return 1;
    }

    Vertex *vertex = graph->inicioGraph;
    while (vertex != NULL)
    {
        vertex->visited = false;
        Adjacent *adj = vertex->nextAdjacent;
        while (adj != NULL)
        {
            adj->visited = false;
            adj = adj->next;
        }
        vertex = vertex->nextVertex;
    }

    int path[MAX_PATH_LENGTH];
    DFSUtil(graph, startVertex, path, 0, 0.0, destinationId);
    return 0;
}

void showGraph(Graph *graph)
{
    if (graph == NULL || graph->inicioGraph == NULL)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Number of vertices: %d\n", graph->numVertices);

    printf("\nVertices:\n");
    Vertex *vertex = graph->inicioGraph;
    while (vertex != NULL)
    {
        printf("Vertex ID: %d\n", vertex->id);
        printf("Adjacent vertices:\n");
        Adjacent *adj = vertex->nextAdjacent;
        while (adj != NULL)
        {
            printf("-> ID: %d, Distance: %.2f\n", adj->id, adj->dist);
            adj = adj->next;
        }
        vertex = vertex->nextVertex;
        printf("\n");
    }
}
