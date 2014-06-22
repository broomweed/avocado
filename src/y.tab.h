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
     TOKVAR = 258,
     TOKPRINT = 259,
     TOKIF = 260,
     TOKELSE = 261,
     TOKNOTHING = 262,
     TOKTRUE = 263,
     TOKFALSE = 264,
     TOKWHILE = 265,
     TOKDEF = 266,
     EQ = 267,
     LTEQ = 268,
     GTEQ = 269,
     NE = 270,
     SEQ = 271,
     SLTEQ = 272,
     SGTEQ = 273,
     SLT = 274,
     SGT = 275,
     SNE = 276,
     AND = 277,
     OR = 278,
     NOT = 279,
     XOR = 280,
     INCR = 281,
     DECR = 282,
     PLUSEQUALS = 283,
     MINUSEQUALS = 284,
     TIMESEQUALS = 285,
     DIVEQUALS = 286,
     CONCATEQUALS = 287,
     UNARY_MINUS = 288,
     NAME = 289,
     INTEGER = 290,
     STRLIT = 291,
     FLOAT = 292,
     GT = 293,
     LT = 294
   };
#endif
/* Tokens.  */
#define TOKVAR 258
#define TOKPRINT 259
#define TOKIF 260
#define TOKELSE 261
#define TOKNOTHING 262
#define TOKTRUE 263
#define TOKFALSE 264
#define TOKWHILE 265
#define TOKDEF 266
#define EQ 267
#define LTEQ 268
#define GTEQ 269
#define NE 270
#define SEQ 271
#define SLTEQ 272
#define SGTEQ 273
#define SLT 274
#define SGT 275
#define SNE 276
#define AND 277
#define OR 278
#define NOT 279
#define XOR 280
#define INCR 281
#define DECR 282
#define PLUSEQUALS 283
#define MINUSEQUALS 284
#define TIMESEQUALS 285
#define DIVEQUALS 286
#define CONCATEQUALS 287
#define UNARY_MINUS 288
#define NAME 289
#define INTEGER 290
#define STRLIT 291
#define FLOAT 292
#define GT 293
#define LT 294



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 65 "grammar.y"

    int i;
    char *s;
    double d;
    struct ast_node *n;


/* Line 2053 of yacc.c  */
#line 143 "y.tab.h"
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
