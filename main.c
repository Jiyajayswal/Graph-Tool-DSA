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

/*
 * A basic menu based structure has been provided
 */
void prompt() {
    printf("\nMenu Options:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Perform Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}


int main(int argc, char *argv[]){
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // FILE *file = fopen(argv[1], "r");
    // if (!file) {
    //     perror("Error opening file");
    //     return 1;
    // }

    // Create the graph object
    Graph *graph = readGraph(argv[1]);

    // Call readGraph to populate the graph from the file
    if (graph == NULL) {
        fprintf(stderr, "Error reading graph from file: %s\n", argv[1]);
        //fclose(file);
        return 1;
    }

    createAdjacencyList(graph);
    // Close the file after reading
    //fclose(file);

    //Graph *graph = createGraphFromFile(filename);
    // Graph graph; 
    // createGraphFromFile(&graph);
    // if (graph.numVertices == 0)
    // {
    //     fprintf(stderr, "Error: Could not create graph from file %s\n", argv[1]);
    //     return 1;
    // }

    int choice;
    // int startVertex = 1;

    do
    {

        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);

        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */

        switch (choice) {
            case 1:

                displayAdjacencyList(graph);
                break;
            case 2:
                bfs(graph, 0); // Assuming vertex 1 corresponds to index 0
                break;
            case 3:
                dfs(graph, 0); // Assuming vertex 1 corresponds to index 0
                break;
            case 4:
                dijkstra(graph, 0); // Assuming vertex 1 corresponds to index 0
                break;
            case 5:
                printf("Exiting program.\n");
                freeGraph(graph);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (true);

    return 0;
}
