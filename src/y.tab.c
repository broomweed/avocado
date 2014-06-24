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

int yylex(void);
int yyparse(void);

scope *outermost;
scope *current_scope;

void yyerror(const char *str) {
    fprintf(stderr, "error: %s near line %d\n", str, yylineno);
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
    outermost = malloc(sizeof(scope));
    outermost->vars = NULL;
    outermost->outer = NULL;
    current_scope = outermost;
    if (debug) printf("==== PARSING PHASE ====\n");
    yyparse();
    return 0;
}

ast_node *root;


/* Line 371 of yacc.c  */
#line 129 "y.tab.c"

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
/* Line 387 of yacc.c  */
#line 68 "grammar.y"

    int i;
    char *s;
    double d;
    struct ast_node *n;


/* Line 387 of yacc.c  */
#line 272 "y.tab.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 300 "y.tab.c"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   662

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,     2,     2,     2,     2,     2,
      41,    64,    49,    47,    55,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    62,
      42,    63,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    65,    51,     2,    59,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    44,    45,    52,    56,
      57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    18,    22,    29,
      35,    40,    44,    46,    48,    51,    53,    55,    57,    59,
      61,    63,    66,    70,    73,    78,    80,    84,    88,    92,
      96,    99,   103,   107,   111,   115,   119,   123,   127,   131,
     135,   139,   143,   147,   151,   155,   159,   163,   167,   170,
     173,   177,   182,   184,   186,   188,   190,   192,   194,   196,
     198,   200,   205,   208,   212,   215,   217,   221,   228,   233,
     235,   239,   242,   245,   249,   253,   257,   261
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    68,    -1,    -1,    68,    71,    -1,    60,
      68,    61,    -1,     5,    77,     6,    71,    -1,     5,    77,
      69,    -1,     5,    77,     6,    71,     7,    71,    -1,     5,
      77,    69,     7,    71,    -1,     8,    77,     9,    71,    -1,
       8,    77,    69,    -1,    69,    -1,    81,    -1,    72,    62,
      -1,    70,    -1,    73,    -1,    83,    -1,    74,    -1,    75,
      -1,    77,    -1,     4,    77,    -1,    76,    63,    77,    -1,
       3,    76,    -1,     3,    76,    63,    77,    -1,    36,    -1,
      59,    77,    59,    -1,    77,    24,    77,    -1,    77,    25,
      77,    -1,    77,    27,    77,    -1,    53,    77,    -1,    77,
      43,    77,    -1,    77,    42,    77,    -1,    77,    14,    77,
      -1,    77,    15,    77,    -1,    77,    16,    77,    -1,    77,
      17,    77,    -1,    77,    22,    77,    -1,    77,    21,    77,
      -1,    77,    18,    77,    -1,    77,    23,    77,    -1,    77,
      19,    77,    -1,    77,    20,    77,    -1,    77,    46,    77,
      -1,    77,    47,    77,    -1,    77,    48,    77,    -1,    77,
      49,    77,    -1,    77,    50,    77,    -1,    48,    77,    -1,
      47,    77,    -1,    41,    77,    64,    -1,    77,    54,    77,
      65,    -1,    38,    -1,    79,    -1,    76,    -1,    37,    -1,
      39,    -1,    11,    -1,    12,    -1,    13,    -1,    78,    -1,
      77,    41,    80,    64,    -1,    76,    80,    -1,    54,    80,
      65,    -1,    54,    65,    -1,    77,    -1,    80,    55,    80,
      -1,    10,    76,    41,    82,    64,    71,    -1,    10,    76,
      82,    71,    -1,    76,    -1,    82,    55,    76,    -1,    76,
      28,    -1,    76,    29,    -1,    76,    30,    77,    -1,    76,
      31,    77,    -1,    76,    32,    77,    -1,    76,    33,    77,
      -1,    76,    34,    77,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   124,   124,   135,   138,   144,   149,   151,   153,   155,
     157,   159,   161,   163,   168,   170,   175,   177,   179,   181,
     183,   185,   190,   195,   200,   205,   207,   212,   214,   216,
     218,   220,   222,   224,   226,   228,   230,   232,   234,   236,
     238,   240,   242,   244,   246,   248,   250,   252,   254,   256,
     258,   260,   262,   264,   266,   268,   270,   272,   274,   276,
     278,   283,   285,   290,   292,   297,   299,   304,   306,   311,
     313,   318,   320,   322,   324,   326,   328,   330
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR", "T_PRINT", "T_IF", "THEN", "ELSE",
  "T_WHILE", "DO", "DEF", "T_NOTHING", "TRUE", "FALSE", "EQ", "LTEQ",
  "GTEQ", "NE", "SEQ", "SLTEQ", "SGTEQ", "SLT", "SGT", "SNE", "AND", "OR",
  "NOT", "XOR", "INCR", "DECR", "PLUSEQUALS", "MINUSEQUALS", "TIMESEQUALS",
  "DIVEQUALS", "CONCATEQUALS", "UNARY_MINUS", "NAME", "INTEGER", "STRLIT",
  "FLOAT", "FUNC_CALL", "'('", "'<'", "'>'", "GT", "LT", "':'", "'+'",
  "'-'", "'*'", "'/'", "'^'", "PAREN_FUNC_CALL", "'!'", "'['", "','",
  "SINGLE_EXPR", "NAMEPREC", "COMMAS", "'`'", "'{'", "'}'", "';'", "'='",
  "')'", "']'", "$accept", "program", "statementlist", "block",
  "qualifiedblock", "statement", "singlestatement", "assignment", "newvar",
  "declare", "varname", "expr", "function_call", "list", "comma_exprs",
  "function_def", "comma_names", "compound", YY_NULL
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    40,    60,    62,   296,   297,    58,    43,    45,    42,
      47,    94,   298,    33,    91,    44,   299,   300,   301,    96,
     123,   125,    59,    61,    41,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    73,    74,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     4,     3,     6,     5,
       4,     3,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     3,     2,     4,     1,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     2,     3,     2,     1,     3,     6,     4,     1,
       3,     2,     2,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,    57,
      58,    59,    25,    55,    52,    56,     0,     0,     0,     0,
       0,     0,     3,    12,    15,     4,     0,    16,    18,    19,
      54,    20,    60,    53,    13,    17,    23,    54,    21,     0,
       0,     0,     0,    49,    48,    30,    64,    65,     0,     0,
       0,    14,    71,    72,     0,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     0,    11,     0,    69,
       0,    50,     0,    63,    26,     5,    73,    74,    75,    76,
      77,    22,    33,    34,    35,    36,    39,    41,    42,    38,
      37,    40,    27,    28,    29,     0,    32,    31,    43,    44,
      45,    46,    47,     0,    24,     6,     0,    10,     0,     0,
      68,    66,    61,    51,     0,     9,     0,    70,     8,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    23,    24,    25,    26,    27,    28,    29,
      37,    31,    32,    33,    60,    34,    90,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -68
static const yytype_int16 yypact[] =
{
     -68,    10,   244,   -68,   -35,   502,   502,   502,   -35,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   502,   502,   502,   502,
      24,   502,   -68,   -68,   -68,   -68,   -49,   -68,   -68,   -68,
     333,   594,   -68,   -68,   -68,   -68,   -41,   320,   594,   293,
     384,   -33,   483,   -68,   -68,   -40,   -68,   -68,   -50,   548,
     132,   -68,   -68,   -68,   502,   502,   502,   502,   502,   502,
     -24,   502,   502,   502,   502,   502,   502,   502,   502,   502,
     502,   502,   502,   502,   502,   502,   502,   502,   502,   502,
     502,   502,   502,   502,   244,    25,   244,   -68,   -35,   -68,
     191,   -68,   502,   -68,   -68,   -68,   594,   594,   594,   594,
     594,   594,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   608,   608,   608,   -48,   100,   100,   -20,   -29,
     -29,   -40,   -40,   431,   594,    26,   244,   -68,   -46,   -35,
     -68,   -68,   -68,   -68,   244,   -68,   244,   -68,   -68,   -68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,    16,   -28,   -68,   -67,   -68,   -68,   -68,   -68,
      -2,    36,   -68,   -68,   -16,   -68,   -44,   -68
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      30,    12,    36,    12,    48,    92,    41,    92,    88,   129,
       3,    85,    87,    51,    82,    93,   132,   125,   136,   127,
      80,    81,    83,   130,    21,    82,    21,    78,    79,    80,
      81,    92,   126,   134,    82,     9,    10,    11,    50,    89,
       0,    38,    39,    40,   128,     0,     0,     0,    30,     0,
       0,     0,    42,    43,    44,    45,    47,    49,   115,   135,
      12,    13,    14,    15,     0,    16,    47,   138,     0,   139,
       0,    17,    18,    47,     0,     0,   131,    19,    20,     0,
       0,     0,    30,    21,    30,     0,    89,     0,    30,    46,
      96,    97,    98,    99,   100,   101,     0,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      47,   116,   117,   118,   119,   120,   121,   122,   123,   124,
       0,     0,     0,     0,    30,     0,     0,   137,    47,     0,
       0,     0,    30,     0,    30,     4,     5,     6,     0,     0,
       7,     0,     8,     9,    10,    11,    77,    78,    79,    80,
      81,     0,     0,     0,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    13,
      14,    15,     0,    16,     0,     0,     0,     0,     0,    17,
      18,     0,     0,     0,     0,    19,    20,     0,     0,     0,
       0,    21,    22,    95,     4,     5,     6,     0,     0,     7,
       0,     8,     9,    10,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,    14,
      15,     0,    16,     0,     0,     0,     0,     0,    17,    18,
       0,     0,     0,     0,    19,    20,   129,     4,     5,     6,
      21,    22,     7,     0,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,    14,    15,     0,    16,     0,     0,     0,     0,
       0,    17,    18,     0,     0,     0,     0,    19,    20,    84,
       0,     0,     0,    21,    22,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,     0,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    74,    75,    76,     0,     0,    77,
      78,    79,    80,    81,     9,    10,    11,    82,     0,     0,
       0,     0,     0,    22,     0,     0,    12,    13,    14,    15,
       0,    52,    53,    54,    55,    56,    57,    58,     0,    12,
      13,    14,    15,    19,     0,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,    21,    86,     0,     0,    59,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       0,    73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    74,    75,    76,     0,     0,
      77,    78,    79,    80,    81,     0,     0,     0,    82,     0,
       0,     0,     0,     0,    22,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,     0,    73,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    74,    75,    76,     0,     0,    77,    78,    79,
      80,    81,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,     0,
      73,     0,     0,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,    74,    75,    76,     0,     0,    77,
      78,    79,    80,    81,     0,     0,     0,    82,    12,    13,
      14,    15,     0,    16,     0,     0,     0,    91,     0,    17,
      18,     0,     0,     0,     0,    19,    20,     0,     0,     0,
       0,    21,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,     0,    73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      75,    76,     0,     0,    77,    78,    79,    80,    81,     0,
       0,     0,    82,     0,     0,     0,     0,    94,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       0,    73,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     0,     0,     0,    74,    75,    76,     0,     0,
      77,    78,    79,    80,    81,     0,     0,     0,    82,     0,
      75,    76,     0,     0,    77,    78,    79,    80,    81,     0,
       0,     0,    82
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-68)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    36,     4,    36,    20,    55,     8,    55,    41,    55,
       0,    39,    40,    62,    54,    65,    64,    84,    64,    86,
      49,    50,    63,    90,    59,    54,    59,    47,    48,    49,
      50,    55,     7,     7,    54,    11,    12,    13,    22,    41,
      -1,     5,     6,     7,    88,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    21,    74,   126,
      36,    37,    38,    39,    -1,    41,    30,   134,    -1,   136,
      -1,    47,    48,    37,    -1,    -1,    92,    53,    54,    -1,
      -1,    -1,    84,    59,    86,    -1,    88,    -1,    90,    65,
      54,    55,    56,    57,    58,    59,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    -1,    -1,   126,    -1,    -1,   129,    92,    -1,
      -1,    -1,   134,    -1,   136,     3,     4,     5,    -1,    -1,
       8,    -1,    10,    11,    12,    13,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      -1,    59,    60,    61,     3,     4,     5,    -1,    -1,     8,
      -1,    10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    53,    54,    55,     3,     4,     5,
      59,    60,     8,    -1,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    53,    54,     6,
      -1,    -1,    -1,    59,    60,    -1,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    13,    41,    42,    43,    -1,    -1,    46,
      47,    48,    49,    50,    11,    12,    13,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    36,    37,    38,    39,
      -1,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    53,    -1,    -1,    -1,    -1,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    59,     9,    -1,    -1,    63,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      27,    -1,    -1,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    36,    37,
      38,    39,    -1,    41,    -1,    -1,    -1,    64,    -1,    47,
      48,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      -1,    59,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    59,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    -1,
      42,    43,    -1,    -1,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    67,    68,     0,     3,     4,     5,     8,    10,    11,
      12,    13,    36,    37,    38,    39,    41,    47,    48,    53,
      54,    59,    60,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    81,    83,    76,    76,    77,    77,
      77,    76,    77,    77,    77,    77,    65,    77,    80,    77,
      68,    62,    28,    29,    30,    31,    32,    33,    34,    63,
      80,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    27,    41,    42,    43,    46,    47,    48,
      49,    50,    54,    63,     6,    69,     9,    69,    41,    76,
      82,    64,    55,    65,    59,    61,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    80,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    71,     7,    71,    82,    55,
      71,    80,    64,    65,     7,    71,    64,    76,    71,    71
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
      yyerror (YY_("syntax error: cannot back up")); \
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
yyparse (void)
#else
int
yyparse ()

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
#line 124 "grammar.y"
    {
        root = (yyvsp[(1) - (1)].n);
        if (debug) printf("==== EVALUATION PHASE ====\n");
        if (debug) printf("Evaluating root AST node...\n");
        ast_eval_expr(root);
        if (debug) printf("\ndone.\n");
        fclose(yyin);
        if (debug) printf("==== CLEANUP PHASE ====\n");
        cleanup();
    }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 135 "grammar.y"
    {
        if (debug) printf("...\n");
        (yyval.n) = NULL;
    }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 138 "grammar.y"
    {
        if (debug) printf(": %c\n", (yyvsp[(2) - (2)].n)->op);
        (yyval.n) = node(MULTI, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 144 "grammar.y"
    {
        (yyval.n) = node(ENCLOSED_SCOPE, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 149 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (4)].n), node(IFELSE, (yyvsp[(4) - (4)].n), NULL));
    }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 151 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (3)].n), node(IFELSE, (yyvsp[(3) - (3)].n), NULL));
    }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 153 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (6)].n), node(IFELSE, (yyvsp[(4) - (6)].n), (yyvsp[(6) - (6)].n)));
    }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 155 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (5)].n), node(IFELSE, (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n)));
    }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 157 "grammar.y"
    {
        (yyval.n) = node(WHILE, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 159 "grammar.y"
    {
        (yyval.n) = node(WHILE, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 161 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 163 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 168 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (2)].n);
    }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 170 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 175 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 177 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 179 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 181 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 183 "grammar.y"
    {
        (yyval.n) = node(EXPR, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 185 "grammar.y"
    {
        (yyval.n) = node(PRINT, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 190 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 195 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 200 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 205 "grammar.y"
    {
        (yyval.n) = node_str((yyvsp[(1) - (1)].s));
    }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 207 "grammar.y"
    {
        (yyval.n) = node(VARNAME, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 212 "grammar.y"
    {
        (yyval.n) = node(BAND, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 214 "grammar.y"
    {
        (yyval.n) = node(BOR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 216 "grammar.y"
    {
        (yyval.n) = node(BXOR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 218 "grammar.y"
    {
        (yyval.n) = node(BNOT, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 220 "grammar.y"
    {
        (yyval.n) = node(NUM_GT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 222 "grammar.y"
    {
        (yyval.n) = node(NUM_LT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 224 "grammar.y"
    {
        (yyval.n) = node(NUM_EQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 226 "grammar.y"
    {
        (yyval.n) = node(NUM_LTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 228 "grammar.y"
    {
        (yyval.n) = node(NUM_GTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 230 "grammar.y"
    {
        (yyval.n) = node(NUM_NE, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 232 "grammar.y"
    {
        (yyval.n) = node(STR_GT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 234 "grammar.y"
    {
        (yyval.n) = node(STR_LT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 236 "grammar.y"
    {
        (yyval.n) = node(STR_EQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 238 "grammar.y"
    {
        (yyval.n) = node(STR_NE, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 240 "grammar.y"
    {
        (yyval.n) = node(STR_LTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 242 "grammar.y"
    {
        (yyval.n) = node(STR_GTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 244 "grammar.y"
    {
        (yyval.n) = node(CONCAT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 246 "grammar.y"
    {
        (yyval.n) = node(ADD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 248 "grammar.y"
    {
        (yyval.n) = node(SUB, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 250 "grammar.y"
    {
        (yyval.n) = node(MUL, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 252 "grammar.y"
    {
        (yyval.n) = node(DIV, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 254 "grammar.y"
    {
        (yyval.n) = node(SUB, node_int(0), (yyvsp[(2) - (2)].n));
    }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 256 "grammar.y"
    {
        (yyval.n) = node(ADD, node_int(0), (yyvsp[(2) - (2)].n));
    }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 258 "grammar.y"
    {
        (yyval.n) = (yyvsp[(2) - (3)].n);
    }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 260 "grammar.y"
    {
        (yyval.n) = node(ELEMENT, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 262 "grammar.y"
    {
        (yyval.n) = node_str((yyvsp[(1) - (1)].s));
    }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 264 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 266 "grammar.y"
    {
        (yyval.n) = node(VARNAME, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 268 "grammar.y"
    {
        (yyval.n) = node_int((yyvsp[(1) - (1)].i));
    }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 270 "grammar.y"
    {
        (yyval.n) = node_dbl((yyvsp[(1) - (1)].d));
    }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 272 "grammar.y"
    {
        (yyval.n) = node_nothing();
    }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 274 "grammar.y"
    {
        (yyval.n) = node_boolean(1);
    }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 276 "grammar.y"
    {
        (yyval.n) = node_boolean(0);
    }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 278 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 283 "grammar.y"
    {
        (yyval.n) = node(FUNCCALL, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 285 "grammar.y"
    {
        (yyval.n) = node(FUNCCALL, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 290 "grammar.y"
    {
        (yyval.n) = node(LISTEND, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 292 "grammar.y"
    {
        (yyval.n) = node(LISTEND, NULL, NULL);
    }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 297 "grammar.y"
    {
        (yyval.n) = node(LISTEND, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 299 "grammar.y"
    {
        (yyval.n) = node(LISTELEM, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n));
    }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 304 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (6)].n), node(FUNCDEF, (yyvsp[(4) - (6)].n), (yyvsp[(6) - (6)].n)));
    }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 306 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (4)].n), node(FUNCDEF, (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 311 "grammar.y"
    {
        (yyval.n) = node(LISTEND, (yyvsp[(1) - (1)].n), NULL);
    }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 313 "grammar.y"
    {
        (yyval.n) = node(LISTELEM, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n));
    }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 318 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (2)].n), node(ADD, NULL, node_int(1)));
    }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 320 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (2)].n), node(SUB, NULL, node_int(1)));
    }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 322 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(ADD, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 324 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(SUB, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 326 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(MUL, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 328 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(DIV, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 330 "grammar.y"
    {
        (yyval.n) = node(COMPOUND, (yyvsp[(1) - (3)].n), node(CONCAT, NULL, (yyvsp[(3) - (3)].n)));
    }
    break;


/* Line 1787 of yacc.c  */
#line 2340 "y.tab.c"
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
		      yytoken, &yylval);
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
		  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 333 "grammar.y"

