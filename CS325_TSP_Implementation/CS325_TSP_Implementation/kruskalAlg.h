/* Program Name: kruskalAlg.h
*  Description:  Header file to implement KruskalAlg.c.
*  Author: Phillip Sturtevant
*  Date: 06/06/2018
*/

#ifndef KRUSKALALG_H
#define KRUSKALALG_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/******** Struct Declarations ********/
typedef struct
{
	int id;
	int xCoordinate;
	int yCoordinate;
	city2dGrid *set;
	int setNum;
}city2dGrid;

city2dGrid mstKruskal(city2dGrid *G, int size);

bool checkEdges(city2dGrid *vertexCheck, city2dGrid *vertexFrom, city2dGrid *vertexCurr);

int findSmallest(city2dGrid *vertexList, int vertex, int size);

int nearestInt(float distance);

#endif