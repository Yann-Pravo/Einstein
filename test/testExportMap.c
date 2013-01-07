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

TEST(testGetPattern)
{
	char* str = "Solo honoratorum solitudine sufficiente postulatus solo vel damnabatur inimico insulari nominatus rumore quod inimico suos inimico capite 					beluae nobilis capite aut onere hostiles et in iniecto solitudine iniecto fovisse damnabatur aut quod solitudine in damnabatur in et inter 					hostiles capite partes iniecto insulari capite iniecto nullo hoc nominatus aut insulari.";
	
	assertEqualsM(getPattern("solitudine", str) && getPattern("insulari", str) && !getPattern("einstein", str), 1, "Les motifs ne sont pas trouvés");
}

TEST(testExportMap)
{
	int nbCities = 3;
	struct City *matrixCities = malloc(nbCities * sizeof(struct City));
	float **matrix = malloc(nbCities * sizeof(float));

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

	matrix[0][1] = 1.0;
	matrix[0][2] = 1.0;
	matrix[1][2] = 1.0;

	exportMap(matrixCities, matrix, nbCities);

	char str[100] = "";
	char str1[100] = "";
	char str2[100] = "";
	char str3[100] = "";
	FILE* file = fopen("map-output.html", "r+");

	while(!feof(file) && !getPattern("coordinates",str))
	{
		fgets(str,100,file);
	}

	fgets(str1,100,file);
	fgets(str2,100,file);
	fgets(str3,100,file);

	assertEqualsM(getPattern("1,43.580002,7.040000", str1) && getPattern("2,49.480000,5.930000", str2) && getPattern("3,45.299999,5.630000", str3), 1, "L'export n'a pas été effectué");
}

