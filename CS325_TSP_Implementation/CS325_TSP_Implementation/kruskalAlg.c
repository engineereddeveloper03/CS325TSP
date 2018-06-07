/* Program Name: primAlg.c
*  Description:  Implements Kruskal's algorithm to help support solving
*                the traveling salesman problem using Christofides
*                algorithm.  Note that to be safe, each vertex set
*                should be initialized to the number of cities.  This
*                will prevent writing data to other parts of memory.
*  Author: Phillip Sturtevant
*  Date: 06/06/2018
*/

#include "kruskalAlg.h"

/* Function: mstKruskal
*  Description: Function which runs Kruskal's algorithm.  Uses a greedy
*               strategy to find the minimum spanning tree of a given
*               graph G.
*  Paramters:   G: the connected graph to be analyzed
*               size: number of cities to check
*  Returns:     the MST
*/
city2dGrid mstKruskal(city2dGrid *G, int size)
{
	// loop over vertices in G
	for (int i = 0; i < size; i++)
	{
		// find the smallest distance
		int smallestDist = findSmallest(G, i, size);

		// check if tree can be grown
		if (checkEdges(G, NULL, &G[smallestDist]))
		{
			G[i].set[G[i].setNum] = G[smallestDist];
			G[smallestDist].set[G[smallestDist].setNum] = G[i];
		}
	}

	// return the MST (any point in the array will do)
	G[0];
}


/* Function: checkEdges
*  Description: Recurses over saved edges to see if the vertex already
*               exists in the tree.
*  Paramters:   vertexCheck: the vertex to look for
*               vertexFrom:  the vertex came from
*               vertexCurr:    the current vertex
*  Returns:     true if the vertex is already in the MST
*               false if it is not
*/
bool checkEdges(city2dGrid *vertexCheck, city2dGrid *vertexFrom, city2dGrid *vertexCurr)
{
	// loop over total edges
	for (int i = 0; i < vertexCurr->setNum; i++)
	{
		// if vertex is not vertexFrom
		if (vertexCheck->set[i] != vertexFrom)
		{
			// if finds vertex, already in MST
			if (vertexCurr->set[i] == vertexCheck)
			{
				return true;
			}
			else  // recurse down each path
			{
				checkEdges(vertexCheck, vertexCurr, vertexCurr->set[i]);
			}
		}
	}
	// no common edge found. Return false
	return false;
}


/* Function: findSmallest
*  Description: Finds the smallest distance between vertices in a graph
*               using one vertex as a point of reference.
*  Paramters:   edgeList: the complete graph list
*               vetex: the array index to compare against
*               size: number of cities to check
*  Returns:     the array index with the smallest distance
*/
int findSmallest(city2dGrid *vertexList, int vertex, int size)
{
	int smallestDist = INFINITY;
	int smallestIndex = 0;

	// loop over vertex list finding smallest distance from current vertex
	for (int i = 0; i < size; i++)
	{
		int currDistance = 0;
		// only check values that are not vertex
		if (i != vertex)
		{
			// calculate distance formula
			int val1 = pow((vertexList[i].xCoordinate - vertexList[vertex].xCoordinate), 2);
			int val2 = pow((vertexList[i].yCoordinate - vertexList[vertex].yCoordinate), 2);
			currDistance = nearestInt(sqrt(val1 + val2));

			// set smallest distance and index if smaller
			if (currDistance < smallestDist)
			{
				smallestDist = currDistance;
				smallestIndex = i;
			}
		}
	}

	// return index with smallest distance
	return smallestIndex;
}

/* Function: nearestInt
*  Description: Function which rounds a float up/down to the closest integer.
*  Paramters:   distance: the inputted floating point distance calculated between
*                         two vertices
*  Returns:     the nearest integer to the given float value
*/

int nearestInt(float distance)
{
	int num = floor(distance);

	if ((distance - num) >= 0.5)
	{
		return num + 1;
	}
	else
	{
		return num;
	}
}
