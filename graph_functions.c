#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    // Implement the function logic here

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    fscanf(file, "%d", &graph->numVertices);

    // Read the adjacency matrix
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            fscanf(file, "%d", &graph->adjMatrix[i][j]);
        }
    }

    // Initialize the adjacency list to NULL
    for (int i = 0; i < graph->numVertices; i++)
    {
        graph->adjList[i] = NULL;
    }

    fclose(file);

    // Convert the adjacency matrix to an adjacency list
    createAdjacencyList(graph);

    return graph;
    //return NULL;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    // Implement the function logic here

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        fprintf(stderr, "Error: Memory allocation failed for node.\n");
        return NULL;
    }

    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
    //return NULL;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // Implement the function logic here

    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("Vertex %d:", i + 1);
        Node *temp = graph->adjList[i];
        while (temp)
        {
            printf(" -> %d", temp->vertex + 1);
            temp = temp->next;
        }
        printf(" NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    // Implement the function logic here
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->adjMatrix[i][j] != 0)
            {
                Node *newNode = createNode(j);
                newNode->next = graph->adjList[i];
                graph->adjList[i] = newNode;
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    visited[startVertex] = true;
    queue[++rear] = startVertex;

    printf("Final BFS Order:\n");

    while (front != rear)
    {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex + 1); // Print vertex (1-indexed)

        Node *temp = graph->adjList[currentVertex];
        while (temp)
        {
            if (!visited[temp->vertex])
            {
                visited[temp->vertex] = true;
                queue[++rear] = temp->vertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
     bool visited[MAX_VERTICES] = {false};

    printf("DFS Order:\n");

    dfsUtil(graph, startVertex, visited);
    printf("\n");
}

//===================HELPER FUNCTION======================================================

void dfsUtil(Graph *graph, int vertex, bool *visited)
{
    visited[vertex] = true;
    printf("%d ", vertex + 1); // Print vertex (1-indexed)

    Node *temp = graph->adjList[vertex];
    while (temp)
    {
        if (!visited[temp->vertex])
        {
            dfsUtil(graph, temp->vertex, visited);
        }
        temp = temp->next;
    }
}

//=================================================================

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    // Implement the function logic here
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES] = {false};
    int n = graph->numVertices;

    // Initialize distances
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[startVertex] = 0;

    // Implement Dijkstra's algorithm
    for (int i = 0; i < n - 1; i++)
    {
        // Find the vertex with the minimum distance
        int minDist = INT_MAX, u = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }

        visited[u] = true;

        // Update the distances of the neighbors
        for (int v = 0; v < n; v++)
        {
            if (graph->adjMatrix[u][v] && !visited[v] && dist[u] != INT_MAX && dist[u] + graph->adjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
            }
        }
    }

    // Print the shortest paths
    for (int i = 0; i < n; i++)
    {
        printf("Shortest distance from vertex 1 to vertex %d: %d\n", i + 1, dist[i]);
    
}
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    // Implement the function logic here

    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjList[i];
        while (temp)
        {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }

    free(graph);
}
