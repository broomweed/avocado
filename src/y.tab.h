/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     VAR = 258,
     T_PRINT = 259,
     T_IF = 260,
     THEN = 261,
     ELSE = 262,
     T_WHILE = 263,
     DO = 264,
     DEF = 265,
     AS = 266,
     T_EVAL = 267,
     T_NOTHING = 268,
     TRUE = 269,
     FALSE = 270,
     EQ = 271,
     LTEQ = 272,
     GTEQ = 273,
     NE = 274,
     SEQ = 275,
     SLTEQ = 276,
     SGTEQ = 277,
     SLT = 278,
     SGT = 279,
     SNE = 280,
     AND = 281,
     OR = 282,
     NOT = 283,
     XOR = 284,
     INCR = 285,
     DECR = 286,
     PLUSEQUALS = 287,
     MINUSEQUALS = 288,
     TIMESEQUALS = 289,
     DIVEQUALS = 290,
     CONCATEQUALS = 291,
     OBRACE = 292,
     EBRACE = 293,
     INTERP_BEGIN = 294,
     INTERP_END = 295,
     UNARY_MINUS = 296,
     NAME = 297,
     INTEGER = 298,
     STRLIT = 299,
     FLOAT = 300,
     PRINT_PREC = 301,
     EVAL_PREC = 302,
     FUNC_CALL = 303,
     COMMAS = 304,
     GT = 305,
     LT = 306,
     PAREN_FUNC_CALL = 307,
     SINGLE_EXPR = 308,
     NAMEPREC = 309
   };
#endif
/* Tokens.  */
#define END 0
#define VAR 258
#define T_PRINT 259
#define T_IF 260
#define THEN 261
#define ELSE 262
#define T_WHILE 263
#define DO 264
#define DEF 265
#define AS 266
#define T_EVAL 267
#define T_NOTHING 268
#define TRUE 269
#define FALSE 270
#define EQ 271
#define LTEQ 272
#define GTEQ 273
#define NE 274
#define SEQ 275
#define SLTEQ 276
#define SGTEQ 277
#define SLT 278
#define SGT 279
#define SNE 280
#define AND 281
#define OR 282
#define NOT 283
#define XOR 284
#define INCR 285
#define DECR 286
#define PLUSEQUALS 287
#define MINUSEQUALS 288
#define TIMESEQUALS 289
#define DIVEQUALS 290
#define CONCATEQUALS 291
#define OBRACE 292
#define EBRACE 293
#define INTERP_BEGIN 294
#define INTERP_END 295
#define UNARY_MINUS 296
#define NAME 297
#define INTEGER 298
#define STRLIT 299
#define FLOAT 300
#define PRINT_PREC 301
#define EVAL_PREC 302
#define FUNC_CALL 303
#define COMMAS 304
#define GT 305
#define LT 306
#define PAREN_FUNC_CALL 307
#define SINGLE_EXPR 308
#define NAMEPREC 309



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 120 "grammar.y"

    int i;
    char *s;
    double d;
    struct ast_node *n;


/* Line 2053 of yacc.c  */
#line 175 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (var **result);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
