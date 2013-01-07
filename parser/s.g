grammar s;

options{
language = C;

}

@parser::includes{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
}

@members{
	
}

@parser::header{
	
}

s[FILE * f]	:	'<?xml' alnum* '?><kml' alnum* '>' interior[f] '</kml>'
	;

interior[FILE * f]:	'<Document>' '<name>' alnum* '</name>' contenu[f] '</Document>';


contenu[FILE * f]	:	style* placemark[f]*
	;
	
style	:	'<Style' alnum* '>' '<IconStyle>' '<scale>' alnum*  '</scale>' '<Icon>' '<href>' alnum* '</href>' '</Icon>' '</IconStyle>'
		'<LabelStyle>' '<color>' alnum* '</color>' '<scale>' alnum* '</scale>' '</LabelStyle>' '</Style>'	
	;

placemark[FILE * f]	:	'<Placemark>' name[f] description[f] styleUrl point[f] '</Placemark>'
	;

name[FILE * f]	:	'<name>' ville=city[f]* '</name>'
		{
		fprintf(f,",");
		}
	;

description[FILE * f]	:	'<description>' '<![CDATA[' fu* pop=NB fa* ']]>' '</description>' 
		{
		fprintf(f,"\%s,", $pop.text->chars);
		}
	;
	
styleUrl	:	'<styleUrl>' alnum* '</styleUrl>'
	;

point[FILE * f]	:	'<Point>' '<coordinates>' eo=NB ',' ns=NB ',' NB '</coordinates>' '</Point>'	
		{
		float NS = atof($ns.text->chars); 
		float EO = atof($eo.text->chars);
		if(NS<0) 
		{
			NS = NS * (-1.0);
			fprintf(f,"\%.2fS,", NS);
		}
		else fprintf(f,"\%.2fN,", NS);
		if(EO<0) 
		{
			EO = EO * (-1.0);
			fprintf(f,"\%.2fW", EO);
		}
		else fprintf(f,"\%.2fE", EO);
		fprintf(f,"\n");
		}
	;


fa	:	(fu|NB);
fu	:	(AL | '<' | '</' | '>' | '?');
alnum	:	(AL|NB);
city[FILE * f]	:	n=(AL|NB)
		{
			fprintf(f,"\%s",$n.text->chars);
		};

AL	:	(' '|'a'..'z'|'A'..'Z'|'"'|'.'|'='|'-'|':'|'/'|','|'#'|'&'|';'|'\u0027' | '\u00C0'..'\u00FF');
NB	:	('-')?('0'..'9')('0'..'9'|'.')*;
WS	:	('\t'|'\r'|'\n'|'\u000C')+ {$channel=HIDDEN;};