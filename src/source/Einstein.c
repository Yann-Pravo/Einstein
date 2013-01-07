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
#include "../headers/ParseFile.h"
#include "../headers/Graph.h"
#include "../headers/ExportMap.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void printCities(struct Graph einsteinGraph, int numCities)
{
	int i;
	for(i = 0; i < numCities; i++)
	{
		printf("%s : %d, %f, %f \n", einsteinGraph.matrixCities[i].nameCity, einsteinGraph.matrixCities[i].populationCity, einsteinGraph.matrixCities[i].orientationNS, einsteinGraph.matrixCities[i].orientationEW);
	}
}

int getCity(struct City *matrixCities, int nbCities)
{
	int findRes = -1;
	char txt[50];
	int i = 0;

	while (findRes < 0)
	{
		printf("\nKey in firsts characters of a city name : ");
		if (!fgets(txt, 50, stdin))
		{
			printf("Error: the city was not taken correctly");
			abort();
		}

		while(txt[i] != '\n' && i < 50)
		{
			i++;
		}
		if (i >= 50)
		{
			fflush(stdin);
		}
		else
		{
			txt[i] = '\0';
			findRes = searchCity(txt,matrixCities,nbCities);
		}

		if (findRes == -1)
		{
			printf("No city begins with these letters.\n");
		}
	}

	return findRes;
}

void printHelp()
{
	printf("Usage: ./einstein -a FLOAT...OPTION\n");
	printf("   or: ./einstein --autonomy FLOAT...OPTION\n");
	printf("   or: ./einstein --help\n\n");
	printf("Mandatory arguments to long options are mandatory for short options too.\n");
	printf("  -a, --autonomy FLOAT			determine the autonomy of the plane in\n");
	printf("					kilometers.\n");
	printf("  -b, --biggest-cities INT		print the N biggest cities\n");
	printf("  -f, --file PATH			path of file that contains the list\n");
	printf("					of cities\n");
	printf("  -h, --help				display this help and exit\n");
	printf("  -m, --min-spanning-tree INT		print the min spanning tree with the\n");
	printf("					INT'th firsts cities.\n");
	printf("  -s, --shortest-path			print the shortest path between two\n");
	printf("					cities\n\n");
	printf("Examples:\n");
	printf("./einstein --autonomy 500 --min-spanning-tree 90\n");
	printf("./einstein -a 200 -m 70\n");
	printf("./einstein -a 102.4 -s\n");
	printf("./einstein -sa 300\n");
	printf("Report einstein bugs to ca.raymond(at)free(dot)fr\n");
	printf("			jerome.audoux(at)polytech.univ-montp2(dot)fr\n");
	printf("			justine.ranc(at)hotmail(dot)fr\n");
	printf("			yann.pravo(at)gmail(dot)com\n");
	printf("Einstein home page: <https://github.com/polytech-projet-ig3/r4>\n");
}

int main (int argc, char *argv[])
{
	FILE* file = NULL;
	char *pathFile = NULL;
	int* route;
	int i=0;
	int cityA = 0;
	int cityB = 0;
	int nCities = 0;
	float autonomy=0;
	char *cvalue = NULL;
	int c;
	int a = 0;
	int b = 0;
	int h = 0;
	int f = 0;
	int m = 0;
	int s = 0;

	struct Graph* einsteinGraph=NULL;
	struct Graph* einsteinGraph2=NULL;

	static struct option long_options[] =
	{
		{"autonomy",    required_argument, 0, 'a'},
		{"biggest-cities",    required_argument, 0, 'b'},
		{"file",    required_argument, 0, 'f'},
		{"help",    no_argument, 0, 'h'},
		{"min-spanning-tree",    required_argument, 0, 'm'},
		{"shortest-path",    no_argument, 0, 's'},
	};
	int option_index = 0;

	while ((c = getopt_long(argc, argv, "a:b:m:shf:", long_options, &option_index)) != -1)
	{
		switch(c)
		{
			case 'a':
					cvalue = optarg;
					autonomy = atoi(cvalue);
					a = 1;
					break;
			case 'b':
					cvalue = optarg;
					nCities = atoi(cvalue);
					b = 1;
					break;
			case 'f':
					pathFile = optarg;
					f = 1;
					break;
			case 'h':
					h = 1;
					break;
			case 'm':
					cvalue = optarg;
					nCities = atoi(cvalue);
					m = 1;
					break;
			case 's':
					s = 1;
					break;
			case '?':
					if (optopt == 'c')
					{
						printHelp();
						break;
					}
					else if (isprint (optopt))
					{
						fprintf (stderr, "Unknown option `-%c'.\n", optopt);
					}
					else
					{
						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
					}
					return 1;
			default:
					abort();
		}
	}

	if(f)
	{
		file = fopen(pathFile, "r");
	}
	else
	{
		file = fopen("villes.csv", "r");
	}

	if (file == NULL)
	{
		printf("%s:  No such file or directory\n", pathFile);
	}
	else
	{
		if(a && autonomy > 0 && !h)
		{
			if(m && !s && !b)
			{
				if(nbCities(file) < nCities)
				{
					printf("The argument nbCities (%d) is greater than the real number of cities in the file (%d)\n", nCities, nbCities(file));
				}
				else
				{
					einsteinGraph = genFromFile(file, nCities, autonomy);
					printf("The graph is at %2.2f%% full.\n", graphEdgesPourcentage(*einsteinGraph));
					einsteinGraph2 = minSpanningTree(*einsteinGraph);
					if (einsteinGraph2 != NULL)
					{
						exportMap(einsteinGraph2->matrixCities, einsteinGraph2->matrix, einsteinGraph2->nbCities);
						deleteGraph(*einsteinGraph2);
						free(einsteinGraph2);
					}

					if(!system("firefox `pwd`/map-output.html &"))
					{
						printf("Lancement du Navigateur Firefox\n");
					}

					deleteGraph(*einsteinGraph);
					free(einsteinGraph);
				}
			}
			else if(!m && s && !b)
			{
				einsteinGraph = genFromFile(file, -1, autonomy);
				printf("The graph is at %2.2f%% full.\n", graphEdgesPourcentage(*einsteinGraph));

				cityA = getCity(einsteinGraph->matrixCities, einsteinGraph->nbCities);
				cityB = getCity(einsteinGraph->matrixCities, einsteinGraph->nbCities);

				printf("\nDistance as the crow flies : %f km \n", distance(einsteinGraph->matrixCities[cityA],einsteinGraph->matrixCities[cityB]));
				route = (int*) malloc(einsteinGraph->nbCities * sizeof(int));
				if(shortestPath(*einsteinGraph, cityA, cityB, route))
				{
					i = 0;

					while(route[i] != -1)
					{
						printf("%d %s\n", route[i], einsteinGraph->matrixCities[route[i]].nameCity);
						i++;
					}
					exportMapPath(*einsteinGraph,route);
					if(!system("firefox `pwd`/map-output.html &"))
					{
						printf("Lancement du Navigateur Firefox\n");
					}
				}
				else
				{
					printf("The graph is not connected : there is no path between these cities.\n");
				}
					
				deleteGraph(*einsteinGraph);
				free(einsteinGraph);
				free(route);
			}
			else if(!m && !s && b)
			{
				if(nbCities(file) < nCities)
				{
					printf("The argument nbCities (%d) is greater than the real number of cities in the file (%d)\n", nCities, nbCities(file));
				}
				else
				{
					einsteinGraph = genFromFile(file, nCities, autonomy);	
					exportMap(einsteinGraph->matrixCities, einsteinGraph->matrix, nCities);
					printCities(*einsteinGraph, nCities);
					printf("The graph is at %2.2f%% full.\n", graphEdgesPourcentage(*einsteinGraph));

					if(!system("firefox `pwd`/map-output.html &"))
					{
						printf("Lancement du Navigateur Firefox\n");
					}

					deleteGraph(*einsteinGraph);
					free(einsteinGraph);
				}
			}
			else
			{
				printHelp();
			}
		}
		else
		{
			printHelp();
		}
		
		fclose(file);


	}
	return 0;
}
