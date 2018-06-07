
/* NAME
*   minimumWeightMatching - Takes a Graph2dGrid, graph edge and first finds odd vertices. They are scanned for minimum cost and graph edges reconstructed on the tree.
* SYNOPSIS
*	int minimumWeightMatching(Graph2dGrid *gridOf2dcities, GraphEdge *graphEdges, int totalVertices)
* DESCRIPTION
* Takes a Graph2dGrid *gridOf2dcities, GraphEdge *graphEdges, int totalVertices. The odd vertices's are gathered based off degree. The greedy algorithm 
* consists of making the greedy choice every time of the minimum distance ran on the collection of odd vertices's. This essentially checks every 
* distance of the adjacent vertex of the odd vertex collection and selects the distance with the minimum cost, effectively making the greedy choice.
*/

int minimumWeightMatching(Graph2dGrid *gridOf2dcities, GraphEdge *graphEdges, int totalVertices)
{
	int *oddVertices;
	oddVertices = malloc(sizeof(int)*totalVertices);
	int totalOddVertices = 0;

	totalOddVertices = getOddVertices(graphEdges, oddVertices, totalVertices);

	int *oddVerticesCopy = malloc(sizeof(int)*totalOddVertices);
	for(int copyCount = 0; copyCount < totalOddVertices; copyCount++) oddVerticesCopy[copyCount] = 0;
	int *start = malloc(sizeof(int)*totalOddVertices);
	int *minimumEnd = malloc(sizeof(int)*totalOddVertices);
	int *minWeight = malloc(sizeof(int)*totalOddVertices);

	int counter = 0;
	int length;
	int testLength = 0;
	for (int oddVertexA = 0; oddVertexA < totalOddVertices; oddVertexA++)
	{
		if(oddVerticesCopy[oddVertexA] != -1)
		{
			length = INFINITY;
			for (int oddVertexB = oddVertexA + 1; oddVertexB < totalOddVertices; oddVertexB++)
			{
				if(oddVerticesCopy[oddVertexB] != -1)
				{
					testLength = euclideanDistance(&gridOf2dcities[oddVertices[oddVertexA]], &gridOf2dcities[oddVertices[oddVertexB]]);
					if(testLength < length)
					{
						start[counter] = oddVertexA;
						minimumEnd[counter] = oddVertexB;
						minWeight[counter] = testLength;
						length = testLength;
					}
				}
			}
			oddVerticesCopy[minimumEnd[counter]] = -1;
			counter++;
		}
	}

	free(oddVerticesCopy);

	for (int edgeCounter = 0; edgeCounter < totalOddVertices / 2; edgeCounter++)
	{
		graphEdges[edgeCounter + totalVertices - 1].vertexA = oddVertices[start[edgeCounter]];
		graphEdges[edgeCounter + totalVertices - 1].vertexB = oddVertices[minimumEnd[edgeCounter]];
		graphEdges[edgeCounter + totalVertices - 1].weight = minWeight[edgeCounter];
	}

	free(start);
	free(minimumEnd);
	free(minWeight);

////////////////// GREEDY - NO SCANNING FOR SMALLER ////////////////////////
	// int skip = 0;
	// int place = 0;
	// for (edgeCounter = 0; edgeCounter < totalOddVertices / 2; edgeCounter ++)
	// {
		// place = skip;
		// graphEdges[edgeCounter+totalVertices - 1].vertexA = oddVertices[place];
		// skip++;
		// graphEdges[edgeCounter+totalVertices - 1].vertexB = oddVertices[skip];
		// graphEdges[edgeCounter+totalVertices - 1].weight = euclideanDistance(&cities[oddVertices[place]], &cities[oddVertices[skip]]);
		// skip++;
	// }
/////////////////////////////////////////////////////////////////

	free(oddVertices);

	return totalVertices - 1 + totalOddVertices / 2;
}
