#include <iostream>

#include "vertex.h"

#define SIZE 6


void vertex() {

    int links_array[SIZE][SIZE];
    int minimal_distance[SIZE];
    int visited_v[SIZE];
    int temp, minindex, min;
    int begin_index = 0;


    // Links array init
    for (int i = 0; i<SIZE; i++)
    {
        links_array[i][i] = 0;
        for (int j = i + 1; j<SIZE; j++) {
            printf("Enter distance %d - %d: ", i + 1, j + 1);
            scanf("%d", &temp);

            links_array[i][j] = temp;
            links_array[j][i] = temp;
        }
    }
    // Links array print
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        printf("%5d ", links_array[i][j]);
        printf("\n");
    }
    // Vertexes and distances initialization
    for (int i = 0; i<SIZE; i++)
    {
        minimal_distance[i] = 10000;
        visited_v[i] = 1;
    }
    minimal_distance[begin_index] = 0;


    // Start of algorithm
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i<SIZE; i++)
        { //  If vertex wasn't observed and weight < min
        if ((visited_v[i] == 1) && (minimal_distance[i]<min))
        {
            min = minimal_distance[i];
            minindex = i;
        }
    }

    // Adding new min weight to vertex weight and compearing with min
    if (minindex != 10000)
    {
        for (int i = 0; i<SIZE; i++)
        {
            if (links_array[minindex][i] > 0)
            {
                temp = min + links_array[minindex][i];
                if (temp < minimal_distance[i])
                {
                    minimal_distance[i] = temp;
                }
            }
        }
        visited_v[minindex] = 0;
    }
    } while (minindex < 10000);

    printf("\nMinimal distances between vertexes: \n");
    for (int i = 0; i<SIZE; i++)
    printf("%5d ", minimal_distance[i]);

    // Route recovering
    int ver[SIZE];
    int end = 4;
    ver[0] = end + 1;
    int k = 1;
    int weight = minimal_distance[end];

    while (end != begin_index)
    {
        for (int i = 0; i<SIZE; i++)
        if (links_array[i][end] != 0)
        {
            int temp = weight - links_array[i][end];
            if (temp == minimal_distance[i])
            {
                weight = temp;
                end = i;
                ver[k] = i + 1;
                k++;
            }
        }
    }

    printf("\nShortest route: \n");
    for (int i = k - 1; i >= 0; i--)
    printf("%3d ", ver[i]);
}
