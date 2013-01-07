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

/*	
*	Cherche un motif dans une chaîne de caractère donnée
*	@param motif, tableau de caractère contenant le motif recherché
*	@param str, tableau de caractère où l'on cherche le motif
*	@return un entier, 0 si on n'a pas trouvé le motif cherché, 1 sinon
*/
int getPattern(char * motif, char * str);

/*	
*	Affiche sur une carte les villes (au nombre de nbCities) (format HTML)
*	@param matrixCities, tableau des villes
*	@param matrix, tableau qui regroupe les distances entre chaques villes
*	@param nbCities, nombre de villes que l'on veut afficher
*	@return un entier, 0 si l'export s'est bien passé, -1 sinon
*/
int exportMap(struct City * matrixCities, float ** matrix, int nbCities);

/*	
*	Affiche sur une carte le chemin le plus court entre 2 villes
*	@param g, est une matrice de n entier par n entier (représentant la distance entre 2 villes) où n représente le nombre de villes.
*	@param path, tableau d'entiers contenant les indices des villes du chemin
*	@return un entier, 0 si l'export s'est bien passé, -1 sinon
*/
int exportMapPath(struct Graph g, int path[1000]);
