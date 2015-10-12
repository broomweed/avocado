%{
#include <stdio.h>
#include <string.h>
#include "../src/avocado.h"
#include "y.tab.h"

extern FILE * yyin;
%}

%option nounput noinput yylineno
%x STRING
%s INTERPOLATE
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
as                      return AS;
nothing                 return T_NOTHING;
true                    return TRUE;
false                   return FALSE;
eval                    return T_EVAL;
  /* Multi-char operators. */
==                      return EQ;
\<=                     return LTEQ;
>=                      return GTEQ;
!=                      return NE;
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
    return STRLIT;
}
<INITIAL,INTERPOLATE>\" BEGIN (STRING);
<STRING>\" {
    BEGIN(INITIAL);
}
<STRING>(\\.|[^"{])+ {
    yylval.s = (char*)calloc(strlen(yytext)+1, sizeof(char));
    strcpy(yylval.s, yytext);
    yylval.s = escape_chars(yylval.s);
    return STRLIT;
}
<STRING>"{" {
    BEGIN(INTERPOLATE);
    interp_count++;
    return INTERP_BEGIN;
}
<INTERPOLATE>"{" {
    bracket_counts[interp_count]++;
    return OBRACE;
}
<INTERPOLATE>"}" {
    bracket_counts[interp_count]--;
    if (bracket_counts[interp_count] > 1) {
        return EBRACE;
    } else {
        BEGIN(STRING);
        return INTERP_END;
    }
}
<INITIAL>"{"    return OBRACE;
<INITIAL>"}"    return EBRACE;
 /*\"(\\.|[^"])*\" {
}*/
  /* Comments. */
"//"[^\n]*\n            /* ignore */;
  /* Ignored. */
[ \t]+                  /* skip whitespace */;
\n                      /* ignore newlines */;
  /* anything else ... */
.                       return *yytext;
%%
var *eval_string(char *str) {
    YY_BUFFER_STATE buf, old = YY_CURRENT_BUFFER;
    buf = yy_scan_string(str);
    var **return_value_ptr = malloc(sizeof(return_value_ptr));
    yyparse(return_value_ptr);
    yy_delete_buffer(buf);
    yy_switch_to_buffer(old);
    var *return_value = *return_value_ptr;
    free(return_value_ptr);
    return return_value;
}
