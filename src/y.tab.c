/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "grammar.y"

#include <stdio.h>
#include <string.h>
#include "avocado.h"
#define YYERROR_VERBOSE

FILE *yyin;
extern int yychar;
extern int yylineno;
int debug;
int yydebug = 1;

int yylex(void);
int yyparse(var **result);

scope *outermost;
scope *current_scope;
var **program_return_value;

int bracket_counts[32];
int interp_count;

void yyerror(var **result, const char *str) {
    throw_error(str, yylineno);
}

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        debug = 0;
    } else if (argc == 3) {
        if (!strcmp(argv[1], "-d")) {
            debug = 1;
            yyin = fopen(argv[2], "r");
        } else {
            fprintf(stderr, "Unrecognized flag %s\n", argv[1]);
            return 1;
        }
    } else {
        printf("usage: %s [-d] <file>\n", argv[0]);
        printf("\t-d:\trun in debug mode\n");
        return 1;
    }
    if (!yyin) {
        fprintf(stderr,
                "Couldn't open file %s. Are you sure it exists?\n",
                argv[argc-1]);
        return 1;
    }
    interp_count = 0;
    outermost = malloc(sizeof(scope));
    outermost->vars = NULL;
    outermost->outer = NULL;
    outermost->last_val = NULL;
    outermost->is_eval = 0;
    current_scope = outermost;
    if (debug) printf("==== PARSING PHASE ====\n");
    program_return_value = malloc(sizeof(program_return_value));
    yyparse(program_return_value);
    if (yyin) fclose(yyin);
    cleanup();
    free_var(*program_return_value);
    free(program_return_value);
    //printf("%p", (void*)program_return_value);
    /*if (*program_return_value) {
        return (*program_return_value)->content.i;
    } else {*/
    return 0;
    /*}*/
}


/* Line 371 of yacc.c  */
#line 145 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
/* Line 387 of yacc.c  */
#line 120 "grammar.y"

    int i;
    char *s;
    double d;
    struct ast_node *n;


/* Line 387 of yacc.c  */
#line 306 "y.tab.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 334 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   910

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  153

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,     2,     2,     2,     2,     2,     2,
      67,    72,    62,    60,    51,    61,     2,    63,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    71,
      54,    53,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    73,    64,     2,    70,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    39,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    52,    56,    57,    59,    68,    69
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    16,    21,    25,
      32,    38,    43,    47,    49,    51,    54,    56,    60,    63,
      68,    70,    74,    80,    82,    84,    86,    88,    91,    95,
      99,   103,   106,   110,   114,   118,   122,   126,   130,   134,
     138,   142,   146,   150,   154,   158,   162,   166,   170,   174,
     177,   180,   184,   189,   192,   194,   196,   198,   200,   202,
     204,   206,   208,   210,   215,   218,   222,   226,   229,   231,
     235,   240,   246,   250,   255,   259,   261,   264,   266,   270,
     273,   276,   280,   284,   288,   292
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      75,     0,    -1,    76,    -1,    84,    -1,    79,    -1,    76,
      79,    -1,    37,    76,    39,    -1,     5,    84,     6,    79,
      -1,     5,    84,    77,    -1,     5,    84,     6,    79,     7,
      79,    -1,     5,    84,    77,     7,    79,    -1,     8,    84,
       9,    79,    -1,     8,    84,    77,    -1,    77,    -1,    88,
      -1,    84,    71,    -1,    78,    -1,    83,    53,    84,    -1,
       3,    83,    -1,     3,    83,    53,    84,    -1,    44,    -1,
      70,    84,    70,    -1,    84,    41,    84,    42,    84,    -1,
      80,    -1,    91,    -1,    81,    -1,    82,    -1,     4,    84,
      -1,    84,    26,    84,    -1,    84,    27,    84,    -1,    84,
      29,    84,    -1,    65,    84,    -1,    84,    55,    84,    -1,
      84,    54,    84,    -1,    84,    16,    84,    -1,    84,    17,
      84,    -1,    84,    18,    84,    -1,    84,    19,    84,    -1,
      84,    24,    84,    -1,    84,    23,    84,    -1,    84,    20,
      84,    -1,    84,    25,    84,    -1,    84,    21,    84,    -1,
      84,    22,    84,    -1,    84,    58,    84,    -1,    84,    60,
      84,    -1,    84,    61,    84,    -1,    84,    62,    84,    -1,
      84,    63,    84,    -1,    61,    84,    -1,    60,    84,    -1,
      67,    84,    72,    -1,    84,    66,    84,    73,    -1,    12,
      84,    -1,    46,    -1,    86,    -1,    83,    -1,    45,    -1,
      47,    -1,    13,    -1,    14,    -1,    15,    -1,    85,    -1,
      84,    67,    87,    72,    -1,    83,    87,    -1,    84,    67,
      72,    -1,    66,    87,    73,    -1,    66,    73,    -1,    84,
      -1,    87,    51,    84,    -1,    10,    83,    89,    79,    -1,
      10,    83,    89,    11,    79,    -1,    10,    83,    77,    -1,
      10,    83,    11,    79,    -1,    67,    90,    72,    -1,    90,
      -1,    67,    72,    -1,    83,    -1,    90,    51,    83,    -1,
      83,    30,    -1,    83,    31,    -1,    83,    32,    84,    -1,
      83,    33,    84,    -1,    83,    34,    84,    -1,    83,    35,
      84,    -1,    83,    36,    84,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   182,   182,   194,   208,   211,   217,   222,   224,   226,
     228,   230,   232,   234,   236,   241,   244,   250,   255,   260,
     265,   267,   272,   274,   276,   278,   280,   282,   284,   286,
     288,   290,   292,   294,   296,   298,   300,   302,   304,   306,
     308,   310,   312,   314,   316,   318,   320,   322,   324,   326,
     328,   330,   332,   334,   336,   338,   340,   342,   344,   346,
     348,   350,   352,   357,   359,   361,   366,   368,   373,   375,
     380,   383,   386,   388,   394,   396,   398,   403,   405,   410,
     412,   414,   416,   418,   420,   422
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end-of-file\"", "error", "$undefined", "\"var\"", "\"print\"",
  "\"if\"", "\"then\"", "\"else\"", "\"while\"", "\"do\"", "\"def\"",
  "\"as\"", "\"eval\"", "\"nothing\"", "\"true\"", "\"false\"", "\"==\"",
  "\"<=\"", "\">=\"", "\"!=\"", "\"eq\"", "\"le\"", "\"ge\"", "\"lt\"",
  "\"gt\"", "\"ne\"", "\"&&\"", "\"||\"", "\"!\"", "\"xor\"", "\"++\"",
  "\"--\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"", "\":=\"", "OBRACE",
  "'{'", "EBRACE", "'}'", "INTERP_BEGIN", "INTERP_END", "UNARY_MINUS",
  "NAME", "INTEGER", "STRLIT", "FLOAT", "PRINT_PREC", "EVAL_PREC",
  "FUNC_CALL", "','", "COMMAS", "'='", "'<'", "'>'", "GT", "LT", "':'",
  "PAREN_FUNC_CALL", "'+'", "'-'", "'*'", "'/'", "'^'", "'!'", "'['",
  "'('", "SINGLE_EXPR", "NAMEPREC", "'`'", "';'", "')'", "']'", "$accept",
  "program", "statement_list", "block", "qualified_block", "statement",
  "assignment", "newvar", "declare", "varname", "expr", "function_call",
  "list", "comma_exprs", "function_def", "function_params", "comma_names",
  "compound", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   123,   293,
     125,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,    44,   304,    61,    60,    62,   305,   306,    58,   307,
      43,    45,    42,    47,    94,    33,    91,    40,   308,   309,
      96,    59,    41,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    79,    79,    80,    81,    82,
      83,    83,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    85,    85,    86,    86,    87,    87,
      88,    88,    88,    88,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    91,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     3,     4,     3,     6,
       5,     4,     3,     1,     1,     2,     1,     3,     2,     4,
       1,     3,     5,     1,     1,     1,     1,     2,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     2,     3,     3,     2,     1,     3,
       4,     5,     3,     4,     3,     1,     2,     1,     3,     2,
       2,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
       0,    20,    57,    54,    58,     0,     0,     0,     0,     0,
       0,     0,     2,    13,    16,     4,    23,    25,    26,    56,
       3,    62,    55,    14,    24,    18,    27,     0,     0,     0,
      53,     0,     0,    50,    49,    31,    67,    68,     0,     0,
       0,     1,     5,    79,    80,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,     0,     0,     8,     0,
      12,     0,     0,    72,    77,     0,    75,     6,     0,    66,
      51,    21,    81,    82,    83,    84,    85,    17,    34,    35,
      36,    37,    40,    42,    43,    39,    38,    41,    28,    29,
      30,     0,    33,    32,    44,    45,    46,    47,    48,     0,
      65,     0,    19,     7,     0,    11,    73,    76,     0,     0,
      70,     0,    69,     0,    52,    63,     0,    10,    74,    71,
      78,    22,     9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      42,    31,    32,    48,    33,    95,    96,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -52
static const yytype_int16 yypact[] =
{
     375,   -36,   402,   402,   402,   -36,   402,   -52,   -52,   -52,
     375,   -52,   -52,   -52,   -52,   402,   402,   402,   104,   402,
     402,    10,   375,   -52,   -52,   -52,   -52,   -52,   -52,   175,
     680,   -52,   -52,   -52,   -52,   -39,   843,   458,   513,    89,
     843,   239,   680,   -29,   -29,   -30,   -52,   843,   -20,   623,
     736,   -52,   -52,   -52,   -52,   402,   402,   402,   402,   402,
     402,   -38,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   169,   -52,   402,   375,    14,   375,
     -52,   375,   -37,   -52,   -52,   307,   -27,   -52,   402,   -52,
     -52,   -52,   -16,   -16,   -16,   -16,   -16,   843,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   272,   272,
     272,   791,   -16,   -16,    61,   -40,   -40,   -30,   -30,   565,
     -52,   -11,   843,    21,   375,   -52,   -52,   -52,    34,   375,
     -52,   -36,   843,   402,   -52,   -52,   375,   -52,   -52,   -52,
     -52,   -52,   -52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,    29,    51,   -52,     8,   -52,   -52,   -52,     4,
       0,   -52,   -52,     3,   -52,   -52,   -51,   -52
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      30,    75,    36,    37,    38,    35,    40,    11,    11,    39,
      51,    75,    75,    98,    86,    43,    44,    45,    47,    49,
      50,   134,    81,    82,   141,    75,    83,    84,   146,    47,
      52,    98,    61,    20,    20,   137,    83,    84,    84,    41,
      98,   138,    78,    94,    79,    80,    81,    82,     0,    52,
      83,    84,     0,    99,     0,   102,   103,   104,   105,   106,
     107,   145,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    47,   141,   132,   131,    88,    90,
      93,     0,     0,     0,     0,   133,    94,   135,   142,   136,
      91,     0,    75,   140,     0,     0,   148,     1,     2,     0,
       0,     0,     0,     0,     0,     0,     6,     7,     8,     9,
       0,    79,    80,    81,    82,     0,    10,    83,    84,     0,
       0,     0,     0,    11,     0,     0,     0,     0,     0,     0,
       0,     0,   147,   151,     0,   150,     0,   149,    11,    12,
      13,    14,     0,     0,   152,     0,    92,     0,     0,    20,
       0,     0,     0,     0,    15,    16,     0,     0,     0,    17,
      18,    19,     1,     2,    20,     0,     0,    46,     1,     2,
       0,     6,     7,     8,     9,     0,     0,     6,     7,     8,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,    54,    55,    56,    57,
      58,    59,     0,    11,    12,    13,    14,     0,     0,    11,
      12,    13,    14,     0,     0,     0,     0,     0,    60,    15,
      16,     0,     0,     0,    17,    18,    19,     0,     0,    20,
      17,   130,     1,     2,     3,    20,     0,     4,     0,     5,
       0,     6,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,    97,     0,
       0,     0,     0,    11,    12,    13,    14,     0,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     0,    15,
      16,     0,     0,     0,    17,    18,    19,     0,     0,    20,
       1,     2,     3,    75,     0,     4,     0,     5,   139,     6,
       7,     8,     9,     0,     0,     0,    76,    77,     0,     0,
      78,     0,    79,    80,    81,    82,     0,     0,    83,    84,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,     0,
       0,     0,    17,    18,    19,     0,     0,    20,     1,     2,
       3,     0,     0,     4,     0,     5,     0,     6,     7,     8,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     0,     0,     0,
       0,     0,    10,     0,     6,     7,     8,     9,     0,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,     0,     0,     0,
      17,    18,    19,     0,     0,    20,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,    16,    87,     0,     0,    17,    18,    19,
       0,     0,    20,     0,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,     0,    74,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     0,     0,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    77,     0,     0,    78,     0,    79,    80,
      81,    82,    89,     0,    83,    84,     0,     0,     0,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     0,    74,     0,     0,     0,     0,     0,     0,     0,
      10,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
       0,    78,     0,    79,    80,    81,    82,     0,     0,    83,
      84,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     0,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
      77,     0,     0,    78,     0,    79,    80,    81,    82,     0,
       0,    83,    84,     0,     0,     0,     0,     0,   144,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
       0,    78,     0,    79,    80,    81,    82,     0,     0,    83,
      84,     0,     0,     0,     0,   100,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    77,     0,     0,    78,     0,
      79,    80,    81,    82,     0,     0,    83,    84,     0,     0,
       0,    85,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,    77,     0,     0,    78,     0,    79,    80,    81,    82,
       0,     0,    83,    84,     0,     0,   101,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,     0,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,     0,     0,    78,
       0,    79,    80,    81,    82,     0,     0,    83,    84,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,     0,
       0,    78,     0,    79,    80,    81,    82,     0,     0,    83,
      84
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-52)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    41,     2,     3,     4,     1,     6,    44,    44,     5,
       0,    41,    41,    51,    53,    15,    16,    17,    18,    19,
      20,     7,    62,    63,    51,    41,    66,    67,     7,    29,
      22,    51,    29,    70,    70,    72,    66,    67,    67,    10,
      51,    92,    58,    39,    60,    61,    62,    63,    -1,    41,
      66,    67,    -1,    73,    -1,    55,    56,    57,    58,    59,
      60,    72,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    51,    86,    84,    37,    38,
      39,    -1,    -1,    -1,    -1,    87,    92,    89,    98,    91,
      11,    -1,    41,    95,    -1,    -1,    72,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    60,    61,    62,    63,    -1,    37,    66,    67,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   134,   143,    -1,   141,    -1,   139,    44,    45,
      46,    47,    -1,    -1,   146,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    65,
      66,    67,     3,     4,    70,    -1,    -1,    73,     3,     4,
      -1,    12,    13,    14,    15,    -1,    -1,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    44,    45,    46,    47,    -1,    -1,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    60,
      61,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,    70,
      65,    72,     3,     4,     5,    70,    -1,     8,    -1,    10,
      -1,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    39,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    60,
      61,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,    70,
       3,     4,     5,    41,    -1,     8,    -1,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    54,    55,    -1,    -1,
      58,    -1,    60,    61,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    65,    66,    67,    -1,    -1,    70,     3,     4,
       5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    12,    13,    14,    15,    -1,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      65,    66,    67,    -1,    -1,    70,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,     6,    -1,    -1,    65,    66,    67,
      -1,    -1,    70,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    -1,    -1,    58,    -1,    60,    61,
      62,    63,     9,    -1,    66,    67,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    58,    -1,    60,    61,    62,    63,    -1,    -1,    66,
      67,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    -1,    -1,    58,    -1,    60,    61,    62,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    73,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    58,    -1,    60,    61,    62,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    72,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    58,    -1,
      60,    61,    62,    63,    -1,    -1,    66,    67,    -1,    -1,
      -1,    71,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    58,    -1,    60,    61,    62,    63,
      -1,    -1,    66,    67,    -1,    -1,    70,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    58,
      -1,    60,    61,    62,    63,    -1,    -1,    66,    67,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    58,    -1,    60,    61,    62,    63,    -1,    -1,    66,
      67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     8,    10,    12,    13,    14,    15,
      37,    44,    45,    46,    47,    60,    61,    65,    66,    67,
      70,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    88,    91,    83,    84,    84,    84,    83,
      84,    76,    84,    84,    84,    84,    73,    84,    87,    84,
      84,     0,    79,    30,    31,    32,    33,    34,    35,    36,
      53,    87,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    29,    41,    54,    55,    58,    60,
      61,    62,    63,    66,    67,    71,    53,     6,    77,     9,
      77,    11,    67,    77,    83,    89,    90,    39,    51,    73,
      72,    70,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      72,    87,    84,    79,     7,    79,    79,    72,    90,    11,
      79,    51,    84,    42,    73,    72,     7,    79,    72,    79,
      83,    84,    79
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (result, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, result); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, var **result)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, result)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    var **result;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (result);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, var **result)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, result)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    var **result;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, result);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, var **result)
#else
static void
yy_reduce_print (yyvsp, yyrule, result)
    YYSTYPE *yyvsp;
    int yyrule;
    var **result;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, result); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, var **result)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, result)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    var **result;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (result);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (var **result)
#else
int
yyparse (result)
    var **result;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 182 "grammar.y"
    {
        ast_node *root = (yyvsp[(1) - (1)].n);
        if (debug) printf("==== EVALUATION PHASE ====\n");
        if (debug) printf("Evaluating root AST node...\n");
        if (root != NULL) {
            *result = ast_eval_expr(root);
        } else {
            *result = NULL;
        }
        if (debug) printf("\ndone.\n");
        if (debug) printf("==== CLEANUP PHASE ====\n");
        free_node(root);
    }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 194 "grammar.y"
    {
        ast_node *root = (yyvsp[(1) - (1)].n);
        if (debug) printf("---- Evaluating expression... ----");
        if (debug) printf("Evaluating root AST node...\n");
        if (root != NULL) {
            *result = ast_eval_expr(root);
        } else {
            *result = NULL;
        }
        if (debug) printf("\ndone.\n");
        if (debug) printf("---- Cleaning up expression. ----");
        free_node(root);
    }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 208 "grammar.y"
    {
        if (debug) printf(": %c\n", (yyvsp[(1) - (1)].n)->op);
        (yyval.n) = node(MULTI, (yyvsp[(1) - (1)].n), NULL);;
    }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 211 "grammar.y"
    {
        if (debug) printf("| %c\n", (yyvsp[(2) - (2)].n)->op);
        (yyval.n) = node(MULTI, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 217 "grammar.y"
    {
        (yyval.n) = node(ENCLOSED_SCOPE, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 222 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (4)].n), node(IFELSE, (yyvsp[(4) - (4)].n), NULL));
    }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 224 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (3)].n), node(IFELSE, (yyvsp[(3) - (3)].n), NULL));
    }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 226 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (6)].n), node(IFELSE, (yyvsp[(4) - (6)].n), (yyvsp[(6) - (6)].n)));
    }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 228 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (5)].n), node(IFELSE, (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n)));
    }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 230 "grammar.y"
    {
        (yyval.n) = node(WHILE, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 232 "grammar.y"
    {
        (yyval.n) = node(WHILE, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 234 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 236 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 241 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (2)].n);
        yyerrok;
    }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 244 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
        yyerrok;
    }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 250 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 255 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 260 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 265 "grammar.y"
    {
        (yyval.n) = node_str((yyvsp[(1) - (1)].s), yylineno);
    }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 267 "grammar.y"
    {
        (yyval.n) = node(VARNAME, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 272 "grammar.y"
    {
        (yyval.n) = node(CONCAT, (yyvsp[(1) - (5)].n), node(CONCAT, (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n)));
    }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 274 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 276 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 278 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 280 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 282 "grammar.y"
    {
        (yyval.n) = node(PRINT, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 284 "grammar.y"
    {
        (yyval.n) = node(BAND, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 286 "grammar.y"
    {
        (yyval.n) = node(BOR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 288 "grammar.y"
    {
        (yyval.n) = node(BXOR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 290 "grammar.y"
    {
        (yyval.n) = node(BNOT, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 292 "grammar.y"
    {
        (yyval.n) = node(NUM_GT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 294 "grammar.y"
    {
        (yyval.n) = node(NUM_LT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 296 "grammar.y"
    {
        (yyval.n) = node(NUM_EQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 298 "grammar.y"
    {
        (yyval.n) = node(NUM_LTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 300 "grammar.y"
    {
        (yyval.n) = node(NUM_GTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 302 "grammar.y"
    {
        (yyval.n) = node(NUM_NE, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 304 "grammar.y"
    {
        (yyval.n) = node(STR_GT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 306 "grammar.y"
    {
        (yyval.n) = node(STR_LT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 308 "grammar.y"
    {
        (yyval.n) = node(STR_EQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 310 "grammar.y"
    {
        (yyval.n) = node(STR_NE, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 312 "grammar.y"
    {
        (yyval.n) = node(STR_LTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 314 "grammar.y"
    {
        (yyval.n) = node(STR_GTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 316 "grammar.y"
    {
        (yyval.n) = node(CONCAT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 318 "grammar.y"
    {
        (yyval.n) = node(ADD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 320 "grammar.y"
    {
        (yyval.n) = node(SUB, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 322 "grammar.y"
    {
        (yyval.n) = node(MUL, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 324 "grammar.y"
    {
        (yyval.n) = node(DIV, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 326 "grammar.y"
    {
        (yyval.n) = node(SUB, node_int(0, yylineno), (yyvsp[(2) - (2)].n));
    }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 328 "grammar.y"
    {
        (yyval.n) = node(ADD, node_int(0, yylineno), (yyvsp[(2) - (2)].n));
    }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 330 "grammar.y"
    {
        (yyval.n) = (yyvsp[(2) - (3)].n);
    }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 332 "grammar.y"
    {
        (yyval.n) = node(ELEMENT, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 334 "grammar.y"
    {
        (yyval.n) = node(EVAL, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 336 "grammar.y"
    {
        (yyval.n) = node_str((yyvsp[(1) - (1)].s), yylineno);
    }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 338 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 340 "grammar.y"
    {
        (yyval.n) = node(VARNAME, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 342 "grammar.y"
    {
        (yyval.n) = node_int((yyvsp[(1) - (1)].i), yylineno);
    }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 344 "grammar.y"
    {
        (yyval.n) = node_dbl((yyvsp[(1) - (1)].d), yylineno);
    }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 346 "grammar.y"
    {
        (yyval.n) = node_nothing(yylineno);
    }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 348 "grammar.y"
    {
        (yyval.n) = node_boolean(1, yylineno);
    }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 350 "grammar.y"
    {
        (yyval.n) = node_boolean(0, yylineno);
    }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 352 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 357 "grammar.y"
    {
        (yyval.n) = node(FUNCCALL, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 359 "grammar.y"
    {
        (yyval.n) = node(FUNCCALL, node(VARNAME, (yyvsp[(1) - (2)].n), NULL), (yyvsp[(2) - (2)].n));
    }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 361 "grammar.y"
    {
        (yyval.n) = node(FUNCCALL, (yyvsp[(1) - (3)].n), node(LISTEND, NULL, NULL));
    }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 366 "grammar.y"
    {
        (yyval.n) = node(LISTEND, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 368 "grammar.y"
    {
        (yyval.n) = node(LISTEND, NULL, NULL);
    }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 373 "grammar.y"
    {
        (yyval.n) = node(LISTEND, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 375 "grammar.y"
    {
        (yyval.n) = node(LISTELEM, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n));
    }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 380 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (4)].n), node_function(
           ((yyvsp[(4) - (4)].n)->op == ENCLOSED_SCOPE ? FUNC_BLOCK : 0), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 383 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (5)].n), node_function(
           ((yyvsp[(5) - (5)].n)->op == ENCLOSED_SCOPE ? FUNC_BLOCK : 0), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n)));
    }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 386 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (3)].n), node_function(FUNC_BLOCK, node(LISTEND, NULL, NULL), (yyvsp[(3) - (3)].n)));
    }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 388 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (4)].n), node_function(
           ((yyvsp[(4) - (4)].n)->op == ENCLOSED_SCOPE ? FUNC_BLOCK : 0), node(LISTEND, NULL, NULL), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 394 "grammar.y"
    {
        (yyval.n) = (yyvsp[(2) - (3)].n);
    }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 396 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 398 "grammar.y"
    {
        (yyval.n) = node(LISTEND, NULL, NULL);
    }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 403 "grammar.y"
    {
        (yyval.n) = node(LISTEND, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 405 "grammar.y"
    {
        (yyval.n) = node(LISTELEM, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n));
    }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 410 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (2)].n), node(ADD, NULL, node_int(1, yylineno)));
    }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 412 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (2)].n), node(SUB, NULL, node_int(1, yylineno)));
    }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 414 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(ADD, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 416 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(SUB, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 418 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(MUL, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 420 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(DIV, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 422 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(CONCAT, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;


/* Line 1787 of yacc.c  */
#line 2529 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (result, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (result, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, result);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (result, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, result);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 425 "grammar.y"

