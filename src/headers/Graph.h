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

/*
*	Structure Graph contenant le tableau de villes,
*	la matrice (des liaisons) en elle même et le nombre de ville.
*	
*/
struct Graph
{
	struct City *matrixCities;
	float **matrix;
	int nbCities;
};

/*
*	Structure Edge représentant une arête 
*	Contenant deux sommets et la distance entre ces deux sommets.
*	
*/
struct Edge
{
	int cityA;
	int cityB;
	float distance;
};

/*
*	Crée une matrice vide de la taille passée en paramètre
*	Toutes les cases sont initialisées à 0
*
*	@param sizeMatrix, taille de la matrice
*	@return une matrice de floats initialisée à 0 à la taille donnée
*/
float** initMatrix(int sizeMatrix);

/*
*	Crée une matrice remplie avec les informations passées en paramètre
*
*	@param matrixCities, tableau des villes contenant les arêtes du graphe grâce aux coordonnées
*	@param nbCities, nombre de villes (taille) de la matrice
*	@return une matrice de floats complétée avec les infos en param
*/
float** createMatrix(struct City *matrixCities, int nbCities, float autonomy);

/*
*	Est uniquement utilisée dans la fonction quickSortPopulation pour connaître la plus grande population entre 2 villes
*
*	@param cityA, ville contenant le nom, la population et les coordonnées de la ville A.
*	@param cityB, ville contenant le nom, la population et les coordonnées de la ville B.
*	@return un entier, la différence de population entre les 2 villes
*/
int sortByPopulation(const void *cityA, const void *cityB);

/*
*	Est uniquement utilisée dans la fonction quickSortDistance pour connaître la plus petite distance entre 2 villes
*
*	@param edgeA, arête contenant les deux sommets (villes) de l'arête et la distance entre ces deux villes.
*	@param edgeB, arête contenant les deux sommets (villes) de l'arête et la distance entre ces deux villes.
*	@return un entier, la différence de distance entre les 2 villes
*/
int sortByDistance(const void *edgeA, const void *edgeB);

/*
*	Trie une matrice d'arêtes dans l'ordre croissant de la distance entre deux villes
*
*	@param matrixEdge, tableau d'arêtes 
*	@param nbEdges, nombre d'arêtes (taille) de la matrice
*	@return un entier selon si le processus de trie s'est déroulé avec succès ou non.
*/
int quickSortDistance(struct Edge *matrixEdges, int nbEdges);

/*
*	Trie une matrice de ville dans l'ordre décroissant de la population de chaque ville
*
*	@param matrixCities, tableau des villes contenant le nom, la population et les coordonnées de chaque ville.
*	@param nbCities, nombre de villes (taille) de la matrice
*	@return un entier selon si le processus de tri s'est déroulé avec succès ou non.
*/
int quickSortPopulation(struct City *matrixCities, int nbCities);

/*
*	Trouve la distance entre 2 villes dans la matrice
*
*	@param g, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de ville.
*	@param cityA, ville représentée par un entier (indice de la matrice du graphe g).
*	@param cityB, ville représentée par un entier (indice de la matrice du graphe g).
*	@return un float, la distance entre les paramètres cityA et cityB.
*/
float getDistance(struct Graph g, int cityA, int cityB);

/*
*	Calcul le chemin le plus court entre 2 villes en utilisant l'algorithme de Dijkstra
*
*	@param g, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de ville.
*	@param cityA, ville représentée par un entier (indice de la matrice du graphe g).
*	@param cityB, ville représentée par un entier (indice de la matrice du graphe g).
*	@return un tableau d'entiers, le chemin le plus court entre les paramètres cityA et cityB où chaque case représente
*		l'indice de la ville dans letableau de ville.
*/
int shortestPath(struct Graph g, int cityA, int cityB, int path[1000]);

/*
*	Calcule le rapport entre le nombre d'arêtes effectives d'un graphe g 
*	et le nombre d'arêtes obtenues dans le graphe complet de g
*
*	@param g, graphe
*	@return le pourcentage de ce rapport
*/
float graphEdgesPourcentage(struct Graph g);

/*
*	Calcul du sous arbre recouvrant minimal
*
*	@param g, graphe
*	@return un graphe avec les liaisons du sous arbre recouvrant minimal
*/
struct Graph* minSpanningTree(struct Graph g);

/*
*	Supprime le graphe de la mémoire
*
*	@param Graph, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de ville.
*/
void deleteGraph(struct Graph graph);
