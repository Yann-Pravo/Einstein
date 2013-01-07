/*
 _____ ___ _   _ ____ _____ _____ ___ _   _ 
| ____|_ _| \ | / ___|_   _| ____|_ _| \ | |
|  _|  | ||  \| \___ \ | | |  _|  | ||  \| |
| |___ | || |\  |___) || | | |___ | || |\  |
|_____|___|_| \_|____/ |_| |_____|___|_| \_|

Einstein Is a New and Super-fast Traveler Engine for Intellectual Newbies.

Coders:
ca.raymond(at)free(dot)fr
jerome.audoux(at)polytech.univ-montp2(dot)fr
justine.ranc(at)hotmail(dot)fr
yann.pravo(at)gmail(dot)com

Repo: http://github.com/polytech-projet-ig3/r4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/headers/City.h"
#include "../src/headers/Graph.h"
#include "../src/headers/ParseFile.h"
#include "../src/headers/ExportMap.h"
#include "cu/cu.h"

TEST(testCreateMatrix_getDistance)
{
	int nbCities = 3;
	struct City *matrixCities = malloc(nbCities * sizeof(struct City));
	float **matrix = malloc(nbCities * sizeof(float*));

	int i;
	for(i = 0; i < 3; i++)
	{
		matrix[i] = malloc(nbCities * sizeof(float));
	}

	struct City c1;
	strcpy(c1.nameCity, "Vallauris");
	c1.orientationNS = 43.58;
	c1.orientationEW = 7.04;
	c1.populationCity = 28722;

	struct City c2;
	strcpy(c2.nameCity, "Villerupt");
	c2.orientationNS = 49.48;
	c2.orientationEW = 5.93;
	c2.populationCity = 9687;

	struct City c3;
	strcpy(c3.nameCity, "Voreppe");
	c3.orientationNS = 45.30;
	c3.orientationEW = 5.63;
	c3.populationCity = 10779;

	matrixCities[0] = c1;
	matrixCities[1] = c2;
	matrixCities[2] = c3;

	matrix = createMatrix(matrixCities, nbCities, 1000);

	struct Graph g;
	g.matrix = matrix;
	g.matrixCities = matrixCities;
	g.nbCities = nbCities;

	assertEqualsM(matrix[0][1] == fabs(distance(c1, c2)) && matrix[0][2] == fabs(distance(c1, c3)) && matrix[1][2] == fabs(distance(c2, c3)), 1, "La matrice est mal initialisé");
	assertEqualsM(getDistance(g, 0, 1) == fabs(distance(c1, c2)) && getDistance(g, 0, 2) == fabs(distance(c1, c3)) && getDistance(g, 1, 2) == fabs(distance(c2, c3)), 1, "Les distances sont mal recherchées");
}

TEST(testShortestPath)
{
	int nbCities = 3;
	struct City *matrixCities = malloc(nbCities * sizeof(struct City));
	float **matrix = malloc(nbCities * sizeof(float*));
	int* route = (int*) malloc(nbCities * sizeof(int));

	int i;
	for(i = 0; i < 3; i++)
	{
		matrix[i] = malloc(nbCities * sizeof(float));
	}

	struct City c1;
	strcpy(c1.nameCity, "Angouleme");
	c1.orientationNS = 45.66;
	c1.orientationEW = 0.15;
	c1.populationCity = 52429;

	struct City c2;
	strcpy(c2.nameCity, "Montlucon");
	c2.orientationNS = 46.34;
	c2.orientationEW = 2.58;
	c2.populationCity = 45529;

	struct City c3;
	strcpy(c3.nameCity, "Seclin");
	c3.orientationNS = 50.55;
	c3.orientationEW = 3.02;
	c3.populationCity = 12216;

	matrixCities[0] = c1;
	matrixCities[1] = c2;
	matrixCities[2] = c3;

	matrix = createMatrix(matrixCities, nbCities, 500);

	struct Graph g;
	g.matrix = matrix;
	g.matrixCities = matrixCities;
	g.nbCities = nbCities;

	shortestPath(g, 0, 2, route);

	assertEqualsM(route[0] == 2 && route[1] == 1 && route[2] == 0, 1, "le chemin le plus court est mal enregistré");
	assertEqualsM(graphEdgesPourcentage(g) > fabs(66) && graphEdgesPourcentage(g) < fabs(67), 1, "Le pourcentage est mal calculé");
}
