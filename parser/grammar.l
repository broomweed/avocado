%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

extern FILE * yyin;
%}

%%
  /* Tokens. */
var                     return TOKVAR;
print                   return TOKPRINT;
  /* Words. */
[0-9]+                  yylval.i=atoi(yytext); return INTEGER;
[0-9]+\.[0-9]+[Ee][0-9]+ {
    yylval.d = atof(yytext);
    printf("omg double\n");
    return DOUBLE;
}
[A-Za-z_][A-Za-z0-9_]*  yylval.s=strdup(yytext); return NAME;
\'(\\.|[^'])*\' {
    yylval.s = (char*)calloc(strlen(yytext)-1, sizeof(char));
    strncpy(yylval.s, &yytext[1], strlen(yytext)-2);
    return STRLIT;
}
\"(\\.|[^"])*\" {
    yylval.s = (char*)calloc(strlen(yytext)-1, sizeof(char));
    strncpy(yylval.s, &yytext[1], strlen(yytext)-2);
    return STRLIT;
}
 /*<<EOF>>                 { static int once = 0; return once++ ? 0 : '\n'; } */
  /* Ignored. */
[ \t]+                  /* skip whitespace */;
\n                      /* ignore newlines */;
  /* anything else ... */
.                       return *yytext;
%%
