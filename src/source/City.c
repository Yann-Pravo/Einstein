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

/*
*	Création d'une ville à partir des paramètres donnés.
*
*	@param nameCity, Nom de la ville
*	@param populationCity, Population de la ville
*	@param orientationNS, Latitude de la ville
*	@param orientationEW, Longitude de la ville
*	@return une ville de structure City avec les params donnés
*/
struct City createCity(char* nameCity, int populationCity, float orientationNS, float orientationEW)
{
	struct City c;
	strcpy(c.nameCity, nameCity);
	c.orientationNS = orientationNS;
	c.orientationEW = orientationEW;
	c.populationCity = populationCity;
	
	return c;
}

/*
*	Convertit un degré décimal en radian
*
*	@param deg, double représentant le degré à convertir
*	@return un double, le radian correspondant au degré passé en paramètre
*/
double deg2rad(double deg)
{
	return (deg * PI / 180);
}

/*
*	Convertit un radian en degré décimal
*
*	@param rad, double représentant le radian à convertir
*	@return un double, le degré correspondant au radian passé en paramètre
*/
double rad2deg(double rad)
{
	return (rad * 180 / PI);
}

/*
*	Calcul la distance entre 2 villes à partir de leur coordonnées.
*
*	@param c1, ville contenant le nom, la population et les coordonnées de la ville c1
*	@param c2, ville contenant le nom, la population et les coordonnées de la ville c2
*	@return un float, la distance entre les paramètres c1 et c2
*/
float distance(struct City c1, struct City c2)
{
	double R = 6371.0;
	double deltaLat, deltaLong, a, c, s1, s2;
	
	deltaLat = deg2rad(c2.orientationNS - c1.orientationNS);
	deltaLong = deg2rad(c2.orientationEW - c1.orientationEW);
	
	a = sin(deltaLat/2) * sin(deltaLat/2) + cos(deg2rad(c1.orientationNS)) * cos(deg2rad(c2.orientationNS)) * sin(deltaLong/2) * sin(deltaLong/2);
	s1 = sqrt(a);
	s2 = 1.0 - a;
	s2 = sqrt(s2);
	c = atan2(s1, s2);
	c = 2 * c;
	return R * c;
} 

/*
*	Cherche une ville depuis une chaine de caractères dans un tableau de ville
*
*	@param txt le préfixe cherché, matrixCities le tableau de villes, nbCities le nombre de villes du tableau
*	@return la position de la ville dans le tableau de ville si txt est le préfixe unique du nom d'une ville dans le tableau
*	@return -1 si il n'y a aucune ville qui correspond à ce préfixe
*	@return -2 si il y a plusieurs villes qui correspondent à la description
*/
int searchCity(char * txt, struct City *matrixCities, int nbCities)
{
	int i;
	int cpt = 0;
	int val = -1;
	
	for (i = 0; i < nbCities; i++)
	{
		if(strncmp(txt, matrixCities[i].nameCity, strlen(txt)) == 0)
		{
			val = i;
			cpt++;
			printf("%s\n",matrixCities[i].nameCity);
		}
	}
	
	if (cpt == 0)
	{
		return -1;
	}
	else if (cpt > 1)
	{
		return -2;
	}
	else
	{
		return val;
	}
}
