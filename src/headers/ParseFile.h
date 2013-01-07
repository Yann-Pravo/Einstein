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
*	Construit le graphe en tant que structure (tab de villes, matrice, nb de villes)
*	en appelant successivement les différentes fonctions de construction.
*
*	@param file, fichier formaté correctement (voir README)
*		contient les villes, leur population, et les coordonnées géographiques.
*/
struct Graph* genFromFile(FILE *file, int nCities, float autonomy);

/*
*	Compte le nombre de villes dans le fichier donné en paramètre,
*	simplement en comptant le nombre de lignes du fichier.
*
*	@param fichier, fichier formaté correctement (voir README)
*		contient les villes, leur population et leur coordonnées géographiques
*	@return un entier correspondant au nombre de villes dans le fichier.
*/
int nbCities(FILE *file);

/*
*	Extrait les villes du fichier passé en paramètre
*	et les place dans un tableau pour être utilisé plus tard
*
*	@param file, fichier formaté correctement (voir README)
*		contient les villes, leur population et leur coordonnées géographiques
*	@return un tableau de villes extraites du fichier
*/
struct City* parseAllCities(FILE *file, int nbCities);

/*
*	Parse une ligne du fichier et extrait les informations relatives
*	à la ville. Cette fonction ne doit être utilisé que lorsqu'on
*	est sûr d'avoir affaire à une ligne contenant une ville.
*
*	@param line, une ligne du fichier, doit contenir une ville
*	@return une ville fabriquée à partir des infos extraites
*/
struct City parseCity(char *line);
