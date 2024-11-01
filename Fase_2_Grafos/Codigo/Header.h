#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 100
#define MAX_PATH_LENGTH 100
/**
 * @file Header.h
 * @brief Livraria que contém definições de tipos e estruturas para o sistema de grafos.
 * @author Alexandre Vilaça 26590
 * @date 25.05.2024
 * 
 * Este ficheiro é uma livraria que possui as estruturas utilizadas em código na implementação do grafo, este  ficheiro também ajuda na reutilização do codigo.
 */

/**
 * @struct Adjacent
 * @brief Estrutura para representar um vértice adjacente.
 *
 * A estrutura Adjacent representa um vértice adjacente de um grafo, ela tem o id que identifica a adjacência, a distancia que representa a distancia entre vértices,
 * um campo visited para perceber se a adjacencia já foi visitada e um apontador para a proxima adjacencia.
 */
typedef struct Adjacent {
	int id;
	float dist;
	bool visited;
	struct Adjacent *next;
}Adjacent;
/**
 * @struct Vertex
 * @brief Estrutura para representar um vértice.
 *
 * A estrutura Vertex representa um vértice de um grafo, ela tem o id do vértice que identifica o vértice, um campo visited para ver se o vertice já foi visistado, um apontador 
 * para a lista de vétices adjacentes e um apontador para o próximo vértice da lista
 */
typedef struct Vertex {
    int id;
	bool visited;
	Adjacent *nextAdjacent;
	struct Vertex *nextVertex;
} Vertex;

/**
 * @struct Graph
 * @brief Estrutura para representar um grafo.
 *
 * A estrutura Graph representa um grafo, ela tem um apontador que aponta para o inicio da lista dos vértices, o número do momento de vértices e o total de vértices
 */
typedef struct Graph {
	Vertex* inicioGraph;	
	int numVertices;			
}Graph;
/**
 * @struct VertexDist
 * @brief Estrutura para representar a distância de um vértice.
 *
 * A estrutura VertexDist é usada para armazenar o id de um vértice
 * e a distância, facilitando a ordenação e manipulação em algoritmos que envolvem grafos.
 */
typedef struct {
    int id;
    float dist;
} VertexDist;

/**
 * Função: createGraph
 * -------------------
 * Cria e inicializa um novo grafo.
 *
 * @return Um apontador para a estrutura Graph criada.
 *
 * A função aloca memória para uma estrutura Graph, inicializa os apontadores
 * e os contadores e retorna o apontador para a estrutura o local onde está o grafo.
 */
Graph* createGraph();
/**
 * Função: createVertex
 * --------------------
 * Cria e inicializa um novo vértice.
 *
 * @param id O id do vértice.
 * @return Um apontador para a estrutura Vertex recém-criada.
 *
 * A função aloca memória para um vértice, inicializa os campos e retorna
 * o apontador para a estrutura.
 */
Vertex* createVertex(int id);
/**
 * Função: createAdjacent
 * ----------------------
 * Cria e inicializa um novo vértice adjacente.
 *
 * @param id O id do vértice adjacente.
 * @param dist A distância até ao vértice adjacente.
 * @return Um apontador vertex para a estrutura de Adjacent criada.
 *
 * A função aloca memória para um vértice adjacente, inicializa os campos e
 * retorna o apontador para a estrutura.
 */
Adjacent* createAdjacent(int id, float dist);
/**
 * Função: addVertex
 * -----------------
 * Adiciona um novo vértice ao grafo.
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param id O identificador do vértice a ser adicionado.
 * @return Um apontador para a estrutura Graph após a adição.
 *
 * A função cria um novo vértice e insere-o no início da lista de vértices do grafo
 * Incrementa os contadores de vértices.
 */
Graph* addVertex(Graph *graph, int id);
/**
 * Função: addAdjacent
 * -------------------
 * Adiciona um novo vértice adjacente a um vértice já existente.
 *
 * @param vertex Um apontador para a estrutura Vertex.
 * @param id O id do vértice adjacente.
 * @param dist A distância até ao vértice adjacente.
 * @return Um apontador para a estrutura Adjacent após a adição da adjacência
 *
 * A função cria um novo vértice adjacente e insere-o no início da lista de adjacentes
 * do vértice conforme o id passado por parâmetro.
 */
Adjacent* addAdjacent(Vertex *vertex, int id, float dist);
/**
 * Função: readGraphFromFile
 * -------------------------
 * Lê uma matriz do ficheiro distanctias.txt e coloca-o na memória.
 *
 * @param filename O nome do ficheiro de onde o grafo é lido.
 * @return Um apontador para a estrutura Graph com os dados lidos do ficheiro.
 *
 * A função abre o ficheiro especificado, lê a quantidade de vértices e as suas adjacências, cria
 * as estruturas correspondentes e insere-as no grafo.
 */
Graph* readGraphFromFile(const char *filename); 
/**
 * Função: removeAdjacent
 * ----------------------
 * Remove um vértice adjacente de um vértice especificado pelo o utilizador no grafo.
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param vertexId O id do vértice principal.
 * @param adjId O id do vértice adjacente a ser removido.
 * @return true se o vértice adjacente foi removido com sucesso, false caso contrário.
 *
 * A função procura o vértice cujo id passado por parãmetro e, se encontrado, percorre a lista de adjacentes
 * para encontrar e remover o vértice adjacente inserido pelo o utilizador.
 */
Graph* removeAdjacent(Graph *graph, int vertexId, int adjId);
/**
 * Função: removeVertex
 * --------------------
 * Remove um vértice do grafo.
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param vertexId O id do vértice a ser removido.
 * @return true se o vértice foi removido com sucesso, false caso contrário.
 *
 * A função procura o vértice cujo id passado por parãmetro e, se encontrado, remove todas as suas
 * adjacências.
 */
Graph* removeVertex(Graph *graph, int vertexId);
/**
 * Função: updateAdjacentDistance
 * ------------------------------
 * Atualiza a distância de um vértice adjacente.
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param vertexId O id do vértice principal.
 * @param adjId O id do vértice adjacente.
 * @param newDist A nova distância para o vértice adjacente.
 * @return true se a distância foi atualizada com sucesso, false caso contrário.
 *
 * A função procura o vértice com o id passado por parâmetro e a adjacencia igual, e se encontrados,
 * atualiza a distância do vértice adjacente.
 */
bool updateAdjacentDistance(Graph *graph, int vertexId, int adjId, float newDist);
/**
 * Função: findVertexById
 * ----------------------
 * Encontra um vértice no grafo pelo seu id.
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param id O id do vértice.
 * @return Um apontador para o vertice cujo o id é igual ao id passado por parãmetro, senão encontrar retorna NULL.
 *
 * A função percorre a lista de vértices do grafo e retorna o vértice que possui o id especificado.
 */
Vertex *findVertexById(Graph *graph, int id);
/**
 * Função: DFSUtil
 * ---------------
 * Função utilitária/adjunta para a busca em profundidade (DFS).
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param vertex Um apontador para o vértice inicial.
 * @param path Um array para armazenar o caminho atual.
 * @param pathLen O comprimento atual do caminho.
 * @param currentDistance A distância atual percorrida.
 * @param destinationId O id do vértice de destino.
 * @return 0 senão existirem erros, se existirem retorna 1
 *
 * A função faz a busca em profundidade a partir de um vértice, marcando os vértices
 * visitados e resgista o caminho e a distância percorrida até ao destino.
 */
int DFSUtil(Graph *graph, Vertex *vertex, int path[], int pathLen, float currentDistance, int destinationId);
/**
 * Função: DFS
 * -----------
 * Faz a busca em profundidade (DFS) no grafo.
 *
 * @param graph Um apontador para a estrutura Graph.
 * @param startVertexId O id do vértice inicial.
 * @param destinationId O id do vértice de destino.
 * @return 0 se não existirem erros, se existirem retorna 1.
 *
 * A função inicializa a DFS a partir de um vértice inicial e chama a função utilitária
 * DFSUtil para fazer a busca e encontrar o caminho até ao destino.
 */
int DFS(Graph *graph, int startVertexId, int destinationId);

void showGraph(Graph *graph);
