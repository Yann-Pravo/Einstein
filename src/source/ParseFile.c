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

#include "../headers/Graph.h"
#include "../headers/ParseFile.h"
#include "../headers/City.h"

/*
*	Construit le graphe en tant que structure (tab de villes, matrice, nb de villes)
*	en appelant successivement les différentes fonctions de construction.
*
*	@param file, fichier formaté correctement (voir README)
*		contient les villes, leur population, et les coordonnées géographiques.
*/
struct Graph* genFromFile(FILE *file, int nCities, float autonomy)
{
	int numbCities;
	struct Graph *graphToReturn;
	struct City *matrixCities;
	float **matrix;

	graphToReturn =(struct Graph*) malloc(sizeof(struct Graph));

	numbCities = nbCities(file);
	matrixCities = parseAllCities(file, numbCities);

	if(nCities != -1)
	{
		quickSortPopulation(matrixCities, numbCities);
		numbCities = nCities;
		matrix = createMatrix(matrixCities, numbCities,autonomy);
	}
	else
	{
		matrix = createMatrix(matrixCities, numbCities, autonomy);
	}

	graphToReturn->matrixCities = matrixCities;
	graphToReturn->matrix = matrix;
	graphToReturn->nbCities = numbCities;

	return graphToReturn;
}

/*
*	Compte le nombre de villes dans le fichier donné en paramètre,
*	simplement en comptant le nombre de lignes du fichier.
*
*	@param fichier, fichier formaté correctement (voir README)
*		contient les villes, leur population et leur coordonnées géographiques
*	@return un entier correspondant au nombre de villes dans le fichier.
*	@TODO gestion ligne vide
*/
int nbCities(FILE *file)
{
	int nbCities = 0;
	int c;
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			nbCities++;
		}
	}
	rewind(file);

	return nbCities;
}

/*
*	Extrait les villes du fichier passé en paramètre
*	et les place dans un tableau pour être utilisé plus tard
*
*	@param file, fichier formaté correctement (voir README)
*		contient les villes, leur population et leur coordonnées géographiques
*	@return un tableau de villes extraites du fichier
*/
struct City* parseAllCities(FILE *file, int nbCities)
{
	struct City *matrixCities;
	int i;
	char *valreturn;
	char *line = malloc(100 * sizeof(char));
	matrixCities = malloc(nbCities * sizeof(struct City));

	for (i = 0; i < nbCities; i++)
	{
		valreturn = fgets(line, 100, file);
		matrixCities[i] = parseCity(line);
	}

	free(line);

	return matrixCities;
}

/*
*	Parse une ligne du fichier et extrait les informations relatives
*	à la ville. Cette fonction ne doit être utilisé que lorsqu'on
*	est sûr d'avoir affaire à une ligne contenant une ville.
*
*	@param line, une ligne du fichier, doit contenir une ville
*	@return une ville fabriquée à partir des infos extraites
*/
struct City parseCity(char *line)
{
	struct City city;
	char nameCity[50];
	int populationCity;
	float orientationNS;
	float orientationEW;
	char Longitude[5];
	char NS;
	char EW;

	/* On extrait les sous chaines directement */
	sscanf(line, "%[^,],%d,%f%c,%[^(E|W)]%c", nameCity, &populationCity, &orientationNS, &NS, Longitude, &EW);

	orientationEW = atof(Longitude);

	if(NS =='S')
	{
		orientationNS = (-1) * orientationNS;
	}

	if(EW =='W')
	{
		orientationEW = (-1) * orientationEW;
	}

	city = createCity(nameCity, populationCity, orientationNS, orientationEW);

	return city;
}
