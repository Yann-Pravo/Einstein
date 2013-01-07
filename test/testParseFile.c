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
#include "../src/headers/ParseFile.h"
#include "../src/headers/City.h"
#include "../src/headers/Graph.h"
#include "cu/cu.h"

TEST(testGenFromFile)
{
	FILE * testFile = tmpfile();
	struct Graph *testGraph;
	
	fputs("Arnouville-les-Gonesse,13306,48.99N,2.41E\n", testFile);
	fputs("Cannes,70891,43.56N,7.02E\n", testFile);
	fputs("Dijon,145441,47.33N,5.03E", testFile);

	testGraph = genFromFile(testFile, 3, 200.0);

	assertEqualsM(testGraph->nbCities, 3, "Mauvais nombre de villes");
	assertEqualsM(testGraph->matrix[0][1] == distance(testGraph->matrixCities[0], testGraph->matrixCities[1]) &&
				testGraph->matrix[0][2] == distance(testGraph->matrixCities[0], testGraph->matrixCities[2]) &&
				testGraph->matrix[1][2] == distance(testGraph->matrixCities[1], testGraph->matrixCities[2])
				, 1, "Les distances ne sont pas enregistrées correctement");

	fclose(testFile);
	free(testGraph);
}

TEST(testParseAllCities)
{
	struct City *city;
	FILE * testFile = tmpfile();
	int i = 0;
	
	fputs("Frejus,58391,43.45N,6.73E\n", testFile);
	fputs("Manosque,22446,43.84N,5.77E\n", testFile);
	fputs("Osny,18788,49.07N,2.06E", testFile);
	
	city = parseAllCities(testFile, 3);
	
	while ((strcmp(city[i].nameCity, "") != 0) && (city[i].populationCity != -1) && (city[i].orientationNS != -1) && (city[i].orientationEW != -1) && (i < 3))
	{
		i++;
	}
	assertEqualsM(i, 3, "Mauvais nombre de villes");
	
	fclose(testFile);
	free(city);
}

TEST(testParseCity)
{
	struct City city;
	char *line = malloc(30 * sizeof(char));
	strcpy(line, "Gaillard,13286,46.18N,6.22E");
	
	city = parseCity(line);
	
	assertEqualsM(
	((strcmp(city.nameCity, "Gaillard") == 0) && city.populationCity == 13286) && (fabs(city.orientationNS - 46.18) < 0.000001) && (fabs(city.orientationEW - 6.22) < 0.000001), 1,
	"La ville n'a pas été extraite correctement");
	
	free(line);
}
