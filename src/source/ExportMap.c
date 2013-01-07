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
#include "../headers/City.h"
#include "../headers/Graph.h"

/*	
*	Cherche un motif dans une chaîne de caractère donnée
*	@param motif, tableau de caractère contenant le motif recherché
*	@param str, tableau de caractère où l'on cherche le motif
*	@return un entier, 0 si on n'a pas trouvé le motif cherché, 1 sinon
*/
int getPattern(char * motif, char * str)
{
	int i=0, pos=0;
	while(i<strlen(str))
	{
		if(pos == 0)
		{
			if(str[i] == motif[pos])
			{
				pos++;
			}
		}
		else
		{
			if(pos >= strlen(motif)) 
			{
				return 1;
			}
			else if(str[i] == motif[pos])
			{
				pos++;
			}
			else
			{
				pos = 0;
			}
		}
		i++;
	}
	return 0;
}

/*	
*	Affiche sur une carte les villes (au nombre de nbCities) (format HTML)
*	@param matrixCities, tableau des villes
*	@param matrix, tableau qui regroupe les distances entre chaques villes
*	@param nbCities, nombre de villes que l'on veut afficher
*	@return un entier, 0 si l'export s'est bien passé, -1 sinon
*/
int exportMap(struct City * matrixCities, float ** matrix, int nbCities)
{
	FILE* mapSource = fopen("map.html", "r");
	FILE* mapOut = fopen("map-output.html", "w");
	char str[100] ="";
	int i =0, j, returnval = 0;
	if (mapSource == NULL)
	{
		printf("Le fichier source n'existe pas !\n");
	}
	else
	{
		/* on lit le fichier map jusqu'a coordinates */
		while (!feof(mapSource) && !getPattern("coordinates",str) && (returnval == 0))
		{
			if (fgets(str,100,mapSource))
			{
				fprintf(mapOut,"%s",str);
			}
			else
			{
				returnval = -1;
			}
		}
		
		/* on ajoute les villes */
		for(i=0; i<nbCities; i++)
		{
			fprintf(mapOut,"[%d,%f,%f]",i+1,matrixCities[i].orientationNS,matrixCities[i].orientationEW);
			if (i == nbCities) 
			{
				fprintf(mapOut,"\n");
			}
			else
			{
				fprintf(mapOut,",\n");
			}
		}
		fprintf(mapOut,"];\n");
		
		/* saute les ligne contenant les anciennes coordonnées */
		while (!getPattern("edges",str) && (returnval == 0))
		{
			if (!fgets(str,100,mapSource))
			{
				returnval = -1;
			}
		}
		fprintf(mapOut,"%s",str);
		
		/* on ajoute les liens entres les villes */
		for(i = 0; i<nbCities; i++)
		{
			for(j = i+1; j<nbCities; j++)
			{
				if (matrix[i][j] != -1)
				{
					
					fprintf(mapOut,"[%d, %d],\n",i+1,j+1);
					
				}
			}
		}
		fprintf(mapOut,"];\n");
		
		/* saute les lignes contenant les anciennes liaisons */
		while (!getPattern("];",str) && (returnval == 0))
		{
			if (!fgets(str,100,mapSource))
			{
				returnval = -1;
			}
		}
		
		while (!feof(mapSource) && (returnval == 0))
		{
			if (fgets(str,100,mapSource))
			{
				fprintf(mapOut,"%s",str);
			}
			else
			{
				returnval = -1;
			}
		}
		fclose(mapSource);
		fclose(mapOut);
	}
	return returnval;
}

/*	
*	Affiche sur une carte le chemin le plus court entre 2 villes
*	@param g, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de villes.
*	@param path, tableau d'entiers contenant les indices des villes du chemin
*	@return un entier, 0 si l'export s'est bien passé, -1 sinon
*/
int exportMapPath(struct Graph g, int path[g.nbCities])
{
	FILE* mapSource = fopen("map.html", "r");
	FILE* mapOut = fopen("map-output.html", "w");
	char str[100] ="";
	int i =0, returnval = 0;
	if (mapSource == NULL)
	{
		printf("Le fichier source n'existe pas !\n");
		return -1;
	}
	else
	{
		/* on lit le fichier map jusqu'a coordinates */
		while (!feof(mapSource) && !getPattern("coordinates",str) && (returnval == 0))
		{
			if (fgets(str,100,mapSource))
			{
				fprintf(mapOut,"%s",str);
			}
			else
			{
				returnval = -1;
			}
		}
		
		/* on ajoute les villes */
		i=0;
		while(path[i] != -1)
		{
			fprintf(mapOut,"[%d,%f,%f],\n",i+1,g.matrixCities[path[i]].orientationNS,g.matrixCities[path[i]].orientationEW);
			i++;
		}
		fprintf(mapOut,"];\n");
		
		/* saute les ligne contenant les anciennes coordonnées */
		while (!getPattern("edges",str) && (returnval == 0))
		{
			if (!fgets(str,100,mapSource))
			{
				returnval = -1;
			}
		}
		fprintf(mapOut,"%s",str);
		
		/* on ajoute les liens entres les villes */
		i = 1;
		while(path[i] != -1)
		{
			fprintf(mapOut,"[%d, %d],\n",i,i+1);
			i++;
		}
		fprintf(mapOut,"];\n");
		
		/* saute les lignes contenant les anciennes liaisons */
		while (!getPattern("];",str) && (returnval == 0))
		{
			if (!fgets(str,100,mapSource))
			{
				returnval = -1;
			}
		}
		
		while (!feof(mapSource) && (returnval == 0))
		{
			if (fgets(str,100,mapSource))
			{
				fprintf(mapOut,"%s",str);
			}
			else
			{
				returnval = -1;
			}
		}
		fclose(mapSource);
		fclose(mapOut);
	}
	return returnval;
}
