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
     VAR = 258,
     T_PRINT = 259,
     T_IF = 260,
     THEN = 261,
     ELSE = 262,
     T_WHILE = 263,
     DO = 264,
     DEF = 265,
     T_NOTHING = 266,
     TRUE = 267,
     FALSE = 268,
     EQ = 269,
     LTEQ = 270,
     GTEQ = 271,
     NE = 272,
     SEQ = 273,
     SLTEQ = 274,
     SGTEQ = 275,
     SLT = 276,
     SGT = 277,
     SNE = 278,
     AND = 279,
     OR = 280,
     NOT = 281,
     XOR = 282,
     INCR = 283,
     DECR = 284,
     PLUSEQUALS = 285,
     MINUSEQUALS = 286,
     TIMESEQUALS = 287,
     DIVEQUALS = 288,
     CONCATEQUALS = 289,
     UNARY_MINUS = 290,
     NAME = 291,
     INTEGER = 292,
     STRLIT = 293,
     FLOAT = 294,
     FUNC_CALL = 295,
     GT = 296,
     LT = 297,
     PAREN_FUNC_CALL = 298,
     SINGLE_EXPR = 299,
     NAMEPREC = 300,
     COMMAS = 301
   };
#endif
/* Tokens.  */
#define VAR 258
#define T_PRINT 259
#define T_IF 260
#define THEN 261
#define ELSE 262
#define T_WHILE 263
#define DO 264
#define DEF 265
#define T_NOTHING 266
#define TRUE 267
#define FALSE 268
#define EQ 269
#define LTEQ 270
#define GTEQ 271
#define NE 272
#define SEQ 273
#define SLTEQ 274
#define SGTEQ 275
#define SLT 276
#define SGT 277
#define SNE 278
#define AND 279
#define OR 280
#define NOT 281
#define XOR 282
#define INCR 283
#define DECR 284
#define PLUSEQUALS 285
#define MINUSEQUALS 286
#define TIMESEQUALS 287
#define DIVEQUALS 288
#define CONCATEQUALS 289
#define UNARY_MINUS 290
#define NAME 291
#define INTEGER 292
#define STRLIT 293
#define FLOAT 294
#define FUNC_CALL 295
#define GT 296
#define LT 297
#define PAREN_FUNC_CALL 298
#define SINGLE_EXPR 299
#define NAMEPREC 300
#define COMMAS 301



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 68 "grammar.y"

    int i;
    char *s;
    double d;
    struct ast_node *n;


/* Line 2053 of yacc.c  */
#line 157 "y.tab.h"
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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
