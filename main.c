#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Read the graph from the file
    Graph *graph = readGraph(argv[1]);
    if (!graph)
    {
        return 1; // If the graph couldn't be read, exit the program
    }

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
                // Code for case 1
                // Display Adjacency List
            displayAdjacencyList(graph);
            
            break;
             case 2:
              bfs(graph, 0); // Start BFS from vertex 1 (index 0)
            
            break;
             case 3:
               dfs(graph, 0); // Start DFS from vertex 1 (index 0)
            break;

             case 4:
              // Find Shortest Path using Dijkstra's Algorithm
            dijkstra(graph, 0); // Start Dijkstra from vertex 1 (index 0)
            break;

             case 5:
                // Exit the program
            printf("Exiting...\n");
            break;

            default:
              printf("Invalid choice. Please try again.\n");  // handling edge cases
                break;
        }

    } while (true);

     // Free allocated memory for the graph
    freeGraph(graph);

    return 0;
}
