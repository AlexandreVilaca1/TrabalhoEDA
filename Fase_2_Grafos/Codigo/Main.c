#include "Header.h"
#include <stdio.h>
#include <stdbool.h>
/**
 * @brief Função principal que gerencia a execução do programa.
 * @author Alexandre Vilaça 26590
 * @date 25.05.2024
 *
 * @return Retorna 0 se a execução foi concluída com sucesso, caso contrário, retorna 1.
 */
int main()
{
    Graph *graph = readGraphFromFile("distancias.txt");
    if (graph == NULL)
    {
        return 1;
    }
    graph->inicioGraph->nextAdjacent;
    graph = removeAdjacent(graph, 3, 4);
    graph = removeVertex(graph, 4);
    updateAdjacentDistance(graph, 1, 5, 700);
    showGraph(graph);
    DFS(graph, 2, 5);
    findLongestPath(graph, 2);

    return 0;
}
