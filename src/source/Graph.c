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

#include "../headers/City.h"
#include "../headers/Graph.h"
#include <string.h>

/*
*	Crée une matrice vide de la taille passée en paramètre
*	Toutes les cases sont initialisées à 0
*
*	@param sizeMatrix, taille de la matrice
*	@return une matrice de floats initialisée à 0 de la taille donnée
*/
float** initMatrix(int sizeMatrix)
{
	float** matrixEmpty;
	int i;

	matrixEmpty = (float**) calloc(sizeMatrix, sizeof (float*));
	
	for (i = 0; i < sizeMatrix; i++)
	{
		matrixEmpty[i] = (float*) calloc(sizeMatrix, sizeof (float));
	}
	return matrixEmpty;
}

/*
*	Crée une matrice remplie avec les informations passées en paramètre
*
*	@param matrixCities, tableau des villes contenant les arêtes du graphe grâce aux coordonnées
*	@param nbCities, nombre de villes (taille) de la matrice
*	@return une matrice de floats complétée avec les infos en param
*/

float** createMatrix(struct City *matrixCities, int nbCities, float autonomy)
{
	float **matrix;
	float d;
	int i,j;
	
	matrix = initMatrix(nbCities);

	for(i = 0; i < nbCities-1; i++)
	{
		for(j = i+1; j < nbCities; j++)
		{
			/* si deux villes sont a plus de 300km on ne les relie pas */
			d = distance(matrixCities[i], matrixCities[j]);
			if (d > autonomy)
			{
				matrix[i][j] = -1.0;
			}
			else
			{
				matrix[i][j] = d;
			}
		}
	}
	return matrix;
}

/*
*	Est uniquement utilisé dans la fonction quickSortPopulation pour connaître la plus grande population entre 2 villes
*
*	@param cityA, ville contenant le nom, la population et les coordonnées de la ville A.
*	@param cityB, ville contenant le nom, la population et les coordonnées de la ville B.
*	@return un entier, la différence de population entre les 2 villes
*/
int sortByPopulation(void const *cityA, void const *cityB)
{
	struct City const *cCityA = cityA;
	struct City const *cCityB = cityB;

	return(cCityB->populationCity - cCityA->populationCity);
}

/*
*	Est uniquement utilisé dans la fonction quickSortDistance pour connaître la plus petite distance entre 2 villes
*
*	@param edgeA, arête contenant les deux sommets (villes) de l'arête et la distance entre ces deux villes.
*	@param edgeB, arête contenant les deux sommets (villes) de l'arête et la distance entre ces deux villes.
*	@return un entier, la différence de distance entre les 2 villes
*/
int sortByDistance(void const *edgeA, void const *edgeB)
{
	struct Edge const *cEdgeA = edgeA;
	struct Edge const *cEdgeB = edgeB;

	return(cEdgeA->distance - cEdgeB->distance);
}

/*
*	Trie une matrice d'arêtes dans l'ordre croissant de la distance entre deux villes
*
*	@param matrixEdge, tableau d'arêtes 
*	@param nbEdges, nombre d'arêtes (taille) de la matrice
*	@return un entier selon si le processus de trie s'est déroulé avec succès ou non.
*/
int quickSortDistance(struct Edge *matrixEdges, int nbEdges)
{
	qsort(matrixEdges, nbEdges, sizeof(struct Edge), sortByDistance);
	return 0;
}

/*
*	Trie une matrice de ville dans l'ordre décroissant de la population de chaque ville
*
*	@param matrixCities, tableau des villes contenant le nom, la population et les coordonnées de chaque ville.
*	@param nbCities, nombre de villes (taille) de la matrice
*	@return un entier selon si le processus de tri s'est déroulé avec succès ou non.
*/
int quickSortPopulation(struct City *matrixCities, int nbCities)
{
	qsort(matrixCities, nbCities, sizeof(struct City), sortByPopulation);
	return 0;
}	

/*
*	Trouve la distance entre 2 villes dans la matrice
*
*	@param g, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de ville.
*	@param cityA, ville représentée par un entier (indice de la matrice du graphe g).
*	@param cityB, ville représentée par un entier (indice de la matrice du graphe g).
*	@return un float, la distance entre les paramètres cityA et cityB.
*/
float getDistance(struct Graph g, int cityA, int cityB)
{
	if(cityA < cityB)
	{
		return g.matrix[cityA][cityB];
	}
	else if(cityA > cityB)
	{
		return g.matrix[cityB][cityA];
	}
	else
	{
		return -1;
	}
}

/*
*	Calcul le chemin le plus court entre 2 villes en utilisant l'algorithme de Dijkstra
*
*	@param g, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de ville.
*	@param cityA, ville représentée par un entier (indice de la matrice du graphe g).
*	@param cityB, ville représentée par un entier (indice de la matrice du graphe g).
*	@return un tableau d'entiers, le chemin le plus court entre les paramètres cityA et cityB où chaque case représente
*		l'indice de la ville dans le tableau de ville.
*/
int shortestPath(struct Graph g, int cityA, int cityB, int* path)
{
	int i, j, newCity = 0;
	float min, dist;
	int city = cityA;
	int newCityFound = 1;
	int* father = (int*) malloc(g.nbCities * sizeof(int));
	float* length = (float*) malloc(g.nbCities * sizeof(float));
	int* visited = (int*) malloc(g.nbCities * sizeof(int));

	for(i = 0; i < g.nbCities; i++)
	{
		path[i] = -1;
	}

	for(i = 0; i < g.nbCities; i++)
	{
		father[i] = -1;
		length[i] = -1.0;
		visited[i] = -1;
	}
	
	length[city] = 0;
	while(city != cityB && newCityFound)
	{
		for(i = 0; i < g.nbCities; i++)
		{
			dist = getDistance(g, i, city);
			
			if((dist > 0.0) && (visited[i] == -1))
			{
				if((length[i] == -1.0) || (dist + length[city] < length[i]))
				{
					length[i] = dist + length[city];
					
					father[i] = city;
				}					
			}
		}
		
		min = 10000000;
		newCityFound = 0;
		
		for(i = 0; i < g.nbCities; i++)
		{
			if((length[i] < min) && (visited[i] == -1) && (length[i] > 0))
			{
				min = length[i];
				newCity = i;
				newCityFound = 1;
			}
		}

		visited[newCity] = 0;
		city = newCity;
		
	}
	
	if (!newCityFound)
	{
		free(father);
		free(visited);
		free(length);
		return 0;
	}
	else
	{
		i = cityB;
		path[0] = cityB;
		j = 0;
	
		while(path[j] != cityA)
		{
			j++;
			path[j] = father[i];
			i = father[i];
		}

		free(father);
		free(visited);
		free(length);

		return 1;
	}
}

/*
*	Calcule le rapport entre le nombre d'arêtes effectives d'un graphe g 
*	et le nombre d'arêtes obtenues dans le graphe complet de g
*
*	@param g, graphe
*	@return le pourcentage de ce rapport
*/
float graphEdgesPourcentage(struct Graph g)
{
	float nbEdges = 0.0, nbEdgePossible = 0.0;
	int i,j;
	for (i = 0; i < g.nbCities-1; i++)
	{
		for (j = i+1; j < g.nbCities; j++)
		{
			if(getDistance(g,i,j) != -1.0)
			{
				nbEdges=nbEdges + 1.0;
			}
		}
	}

	nbEdgePossible = (g.nbCities*(g.nbCities-1)) / 2.0;

	if (nbEdgePossible == 0)
	{
		return 0;
	}
	else
	{
		return ((nbEdges/nbEdgePossible)*100);
	}
}

/*
*	Calcul du sous arbre recouvrant minimal
*
*	@param g, graphe
*	@return un graphe avec les liaisons du sous arbre recouvrant minimal
*/
struct Graph* minSpanningTree(struct Graph g)
{
	int l, c, i=0, nbEdges=0, cityA=-1, cityB=-1;
	int isConnexe;
	struct Edge edge;
	struct Graph* newGraph=NULL;
	struct Edge* matrixEdges=NULL;
	int* connexeComp=NULL;
	float** matrix;
	int aux, j, k;
 
	newGraph =(struct Graph*) malloc(sizeof(struct Graph));
	newGraph->nbCities = g.nbCities;

	connexeComp = malloc(g.nbCities * sizeof(int));
	matrixEdges = malloc((g.nbCities*g.nbCities) * sizeof(struct Edge));

	newGraph->matrixCities = malloc(g.nbCities * sizeof(struct City));

	for(j = 0; j < g.nbCities; j++)
	{
		newGraph->matrixCities[j] = g.matrixCities[j];
	}

	matrix = initMatrix(g.nbCities);

	for(j = 0; j < g.nbCities; j++)
	{
		for(k = 0; k < g.nbCities; k++)
		{
			matrix[j][k] = -1.0;
		}
	}

	for (l = 0; l < g.nbCities-1; l++)
	{
		for (c = l+1; c < g.nbCities; c++)
		{
			if(g.matrix[l][c] != -1)
			{
				edge.cityA = l;
				edge.cityB = c;
				edge.distance = g.matrix[l][c];
				matrixEdges[i] = edge;
				i++;
			}
		}
	}

	nbEdges = i;
	quickSortDistance(matrixEdges, nbEdges);

	for (i = 0; i < g.nbCities; i++)
	{
		connexeComp[i] = i;
	}

	k = 0;
	j = 0;
    
	while (k < (g.nbCities-1) && j<nbEdges)
	{
		cityA= matrixEdges[j].cityA;
		cityB= matrixEdges[j].cityB;
		if (connexeComp[cityA] != connexeComp[cityB])
		{
			k++;
			matrix[cityA][cityB] = getDistance(g, cityA, cityB);
			aux = connexeComp[cityB];

			for (i = 0; i < g.nbCities; i++)
			{
				if (connexeComp[i] == aux)
				{
					connexeComp[i] = connexeComp[cityA];
         			}
			}
		}
		j++;
	}

	i = 0;
	isConnexe = 1;

	while (i < g.nbCities-1 && isConnexe)
	{
		if (connexeComp[i] != connexeComp[i+1])
		{
			isConnexe = 0;
		}
		i++;
	}

	newGraph->matrix = matrix;

	if (isConnexe == 0)
	{
		free(connexeComp);
		free(matrixEdges);
		deleteGraph(*newGraph);
		free(newGraph);
		printf("The graph is not connected : there is no minimum spanning tree between these cities.\n");
		return NULL;
	}
	

	free(connexeComp);
	free(matrixEdges);

	return newGraph;
}

/*
*	Supprime le graphe de la mémoire
*
*	@param Graph, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de ville.
*/
void deleteGraph(struct Graph graph)
{
	int i;
	for (i = 0 ; i<graph.nbCities ; i++)
	{
		free(graph.matrix[i]);
		graph.matrix[i] = NULL ;
	}
	free(graph.matrix);
	free(graph.matrixCities);
}
