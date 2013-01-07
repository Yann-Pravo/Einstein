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
#include "testParseFile.h"
#include "testCity.h"
#include "testExportMap.h"
#include "testGraph.h"
#include "../src/headers/ParseFile.h"
#include "../src/headers/Graph.h"
#include "../src/headers/City.h"
#include "../src/headers/ExportMap.h"

TEST_SUITES
{
	TEST_SUITE_ADD(ParseFile),
	TEST_SUITE_ADD(Graph),
	TEST_SUITE_ADD(City),
	TEST_SUITE_ADD(ExportMap),
	TEST_SUITES_CLOSURE
};

int main (int argc, char *argv[])
{
	CU_SET_OUT_PREFIX("results/");
	CU_RUN(argc, argv);
	
	return 0;
}
