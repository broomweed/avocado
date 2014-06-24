%{
#include <stdio.h>
#include <string.h>
#include "../src/avocado.h"
#include "y.tab.h"

extern FILE * yyin;
%}

%option nounput
%option noinput
%option yylineno
%%
  /* Tokens. */
var                     return VAR;
print                   return T_PRINT;
if                      return T_IF;
then                    return THEN;
else                    return ELSE;
while                   return T_WHILE;
do                      return DO;
def                     return DEF;
nothing                 return T_NOTHING;
true                    return TRUE;
false                   return FALSE;
  /* Multi-char operators. */
==                      return EQ;
\<=                     return LTEQ;
>=                      return GTEQ;
!=                      return NE;
eq                      return SEQ;
gt                      return SGT;
lt                      return SLT;
ne                      return SNE;
ge                      return SGTEQ;
le                      return SLTEQ;
&&|and                  return AND;
\|\||or                 return OR;
!|not                   return NOT;
xor                     return XOR;
\+\+                    return INCR;
--                      return DECR;
\+=                     return PLUSEQUALS;
-=                      return MINUSEQUALS;
\*=                     return TIMESEQUALS;
\/=                     return DIVEQUALS;
:=                      return CONCATEQUALS;
  /* Words. */
[0-9]+                  yylval.i=atoi(yytext); return INTEGER;
[0-9]+\.[0-9]+([Ee][0-9]+)? {
    yylval.d = atof(yytext);
    return FLOAT;
}
[A-Za-z_][A-Za-z0-9_]*  yylval.s=str_dup(yytext); return NAME;
\'(\\.|[^'])*\' {
    yylval.s = (char*)calloc(strlen(yytext)-1, sizeof(char));
    strncpy(yylval.s, &yytext[1], strlen(yytext)-2);
    yylval.s = escape_chars(yylval.s);
    return STRLIT;
}
\"(\\.|[^"])*\" {
    yylval.s = (char*)calloc(strlen(yytext)-1, sizeof(char));
    strncpy(yylval.s, &yytext[1], strlen(yytext)-2);
    yylval.s = escape_chars(yylval.s);
    return STRLIT;
}
  /* Comments. */
\/\/[^\n]*\n              /* ignore */;
  /* Ignored. */
[ \t]+                  /* skip whitespace */;
\n                      /* ignore newlines */;
  /* anything else ... */
.                       return *yytext;
%%
