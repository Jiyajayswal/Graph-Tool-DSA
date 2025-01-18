/*
Student Name: Jiya Jayswal
Student ID: 1310124
File name: graph_functions.c
Due Date:  Nov 30, 2024
Course: CIS*2520
I have exclusive control over this submission via my password.
By including this header comment, I certify that:
1) I have read and understood the policy on academic integrity.
2) I have completed Moodle's module on academic integrity.
3) I have achieved at least 80% on the academic integrity quiz
I assert that this work is my own. I have appropriate acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by me in its entirety.
*/

#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/


/*
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int count = 0;
    int num;
    char c;

    // Read the first line
    while (fscanf(file, "%d%c", &num, &c) == 2) {
        count++;
        if (c == '\n') break;
    }

     if (count > MAX_VERTICES) {
        printf("Error: Number of vertices exceeds MAX_VERTICES (%d).\n", MAX_VERTICES);
        fclose(file);
        return NULL;
    }

    rewind(file); 


    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph) {
        perror("Error allocating memory for graph");
        fclose(file);
        return NULL;
    }

    //graph->adjList = (Node **)calloc(graph->numVertices, sizeof(Node *));
     graph->numVertices = count;
    memset(graph->adjMatrix, 0, sizeof(graph->adjMatrix));
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
    }

   
   
    // if ( fscanf(file, "%d", &graph->numVertices) != 1) {
    //     printf("Error: Number of vertices exceeds MAX_VERTICES (%d).\n", MAX_VERTICES);
    //     free(graph);
    //     fclose(file);
    //     return NULL;
    // }

//last
    // for (int i = 0; i < graph->numVertices; i++) {
    //     for (int j = 0; j < graph->numVertices; j++) {
    //         fscanf(file, "%d", &graph->adjMatrix[i][j]);
    //     }
    // }

     for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
        graph->adjList[i] = NULL; // Initialize adjacency list pointers
    }

    //graph->numVertices = 5; 
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            //fscanf(file, "%d", &graph->adjMatrix[i][j]);
            // Check for non-negative weights in the adjacency matrix
            //if (graph->adjMatrix[i][j] < 0) {
            if (fscanf(file, "%d", &graph->adjMatrix[i][j]) != 1) {
                printf("Invalid adjacency matrix value: negative weight.\n");
                free(graph);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph){
    
   printf("Vertex:  Adjacency List\n");
    for (int i = 0; i < graph->numVertices; i++) {
       //printf("H\n");
       printf("Vertex %d: ", i + 1);
        
         //printf("%d --->", i);
        // if (i == graph->numVertices) {
        //     return;
        //  }
         //else {
            Node *temp = graph->adjList[i];
           
            if (temp == NULL) {
            printf(" NULL\n");
           }else{
            while (temp) {
                //printf("%d -> ", temp->vertex + 1);
                printf("-> %d (%d)  ", temp->vertex + 1, graph->adjMatrix[i][temp->vertex]);
                temp = temp->next;
            }
            printf("NULL\n");
         }

    }
    //}

}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{

   for (int i = 0; i < graph->numVertices; i++) {
        graph->adjList[i] = NULL;
        Node *last = NULL;
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                //Node* newNode = (Node*)malloc(sizeof(Node));
                Node* newNode = createNode(j);

                if (last == NULL) {
                    graph->adjList[i] = newNode;
                } else {
                    last->next = newNode;
                }
                last = newNode;
            
                //newNode->vertex = j;
                //newNode->next = graph->adjList[i];
                //graph->adjList[i] = newNode;
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
    if (graph == NULL || graph->numVertices == 0) {
        printf("Graph is empty or not initialized.\n");
        return;
    }
    int visited[MAX_VERTICES] = {0}; // Array to keep track of visited vertices
    int queue[MAX_VERTICES];         // Queue for BFS traversal
    int front = 0, rear = 0;         // Pointers for the queue

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS traversal starting from vertex %d: ", startVertex + 1);

    while (front < rear) {
        // Dequeue a vertex and process it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex + 1);

        // Get all adjacent vertices
        Node *temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            // If the vertex hasn't been visited, mark it as visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
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
 void dfsUtil(Graph *graph, int vertex, int visited[]) {
    // Mark the vertex as visited and process it
    visited[vertex] = 1;
    printf("%d ", vertex + 1);

    // Visit all adjacent vertices
    Node *temp = graph->adjList[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            dfsUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void dfs(Graph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // Array to keep track of visited vertices
    printf("DFS traversal starting from vertex %d: ", startVertex + 1);
    dfsUtil(graph, startVertex, visited);
    printf("\n");
}

// void dfs(Graph *graph, int startVertex)
// {
//     int visited[MAX_VERTICES] = {0}; // Array to keep track of visited vertices
//     printf("DFS traversal starting from vertex %d: ", startVertex + 1);
//      visited[vertex] = 1;
//     printf("%d ", vertex + 1);

//     // Visit all adjacent vertices
//     Node *temp = graph->adjList[vertex];
//     while (temp) {
//         int adjVertex = temp->vertex;
//         if (!visited[adjVertex]) {
//             dfsUtil(graph, adjVertex, visited);
//         }
//         temp = temp->next;
//     }

//     printf("\n");
    
// }

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
     int dist[MAX_VERTICES];     // Array to store the shortest distance from startVertex
    int visited[MAX_VERTICES];  // Array to track visited vertices
   //int parent[MAX_VERTICES];   // Array to reconstruct the shortest path

    // Initialize distances to infinity and visited to 0
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
      //  parent[i] = -1;
    }
    dist[startVertex] = 0; // Distance to itself is 0

    for (int i = 0; i < graph->numVertices - 1; i++) {
        // Find the vertex with the minimum distance
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }

        visited[minIndex] = 1;

        // Update distances for adjacent vertices
        Node *temp = graph->adjList[minIndex];
        while (temp) {
            int adjVertex = temp->vertex;
            int weight = graph->adjMatrix[minIndex][adjVertex];
            if (!visited[adjVertex] && dist[minIndex] != INT_MAX && dist[minIndex] + weight < dist[adjVertex]) {
                dist[adjVertex] = dist[minIndex] + weight;
             //   parent[adjVertex] = minIndex;
            }
            temp = temp->next;
        }
    }

     //printf("Shortest distances from vertex %d:\n", startVertex + 1);
    for (int i = 0; i < graph->numVertices; i++) {
        // printf("Shortest distances from vertex %d:\n", startVertex + 1);
        printf("Shortest distances from vertex %d: %d\n", i+1, dist[i]);
        // printf(" ");
       // printPath(parent, i);
        // printf("\n");
    }


    // printf("Shortest distances from vertex %d:\n", startVertex + 1);
    // for (int i = 0; i < graph->numVertices; i++) {
    //     printf("To %d: %d\n", i + 1, dist[i]);
    // }
}



/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++) {
        Node *temp = graph->adjList[i];
        while (temp) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
}


void addEdge(Graph *graph, int u, int v) {
    // Add edge from u to v in adjacency list
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;

    // If the graph is undirected, you should also add the reverse edge:
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = graph->adjList[v];
    graph->adjList[v] = newNode;
}
