/*
Student Name: Jiya Jayswal
Student ID: 1310124
File name: graph.h
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

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

// Define maximum number of vertices in the graph
#define MAX_VERTICES 100

// Structure representing a node in an adjacency list
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

// Structure representing a graph
typedef struct Graph
{
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    Node *adjList[MAX_VERTICES];
} Graph;

// Function definitions
void prompt(void);
Graph *readGraph(const char *filename);
Node *createNode(int vertex);
void displayAdjacencyList(Graph *graph);
void createAdjacencyList(Graph *graph);
void bfs(Graph *graph, int startVertex);
void dfs(Graph *graph, int startVertex);
void dijkstra(Graph *graph, int startVertex);
void freeGraph(Graph *graph);

//new
void dfsUtil(Graph *graph, int vertex, int visited[]) ;

void addEdge(Graph *graph, int u, int v);

#endif // GRAPH_H
