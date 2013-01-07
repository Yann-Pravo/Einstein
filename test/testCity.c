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
#include "cu/cu.h"

TEST(testCreateCity)
{
	struct City city;
	
	city = createCity("Abbeville", 27455, 50.119999, 1.830000);
	
	assertEqualsM((strcmp(city.nameCity, "Abbeville") == 0) && (city.populationCity == 27455) && (fabs(city.orientationNS - 50.119999) < 0.000001) && (fabs(city.orientationEW - 1.830000) < 0.000001), 1, "Ville mal créée");
}
