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

FILE *yyin;
extern int yychar;
int debug;

scope *outermost;
scope *current_scope;

void yyerror(const char *str) {
    fprintf(stderr, "error: %s -- unexpected '%c'\n", str, yychar);
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
#line 124 "y.tab.c"

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
     LT = 270,
     GT = 271,
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
     UNARY_MINUS = 289,
     NAME = 290,
     INTEGER = 291,
     STRLIT = 292,
     FLOAT = 293
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
#define LT 270
#define GT 271
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
#define UNARY_MINUS 289
#define NAME 290
#define INTEGER 291
#define STRLIT 292
#define FLOAT 293



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 62 "grammar.y"

    int i;
    char *s;
    double d;
    struct ast_node *n;


/* Line 387 of yacc.c  */
#line 251 "y.tab.c"
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
#line 279 "y.tab.c"

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
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  106

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,     2,     2,     2,     2,     2,
      53,    54,    45,    43,     2,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    50,
      39,    51,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    47,     2,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    14,    18,    24,    28,
      30,    33,    35,    37,    39,    41,    43,    46,    50,    53,
      58,    60,    64,    66,    70,    74,    78,    82,    85,    89,
      93,    97,   101,   105,   109,   113,   117,   121,   125,   129,
     133,   137,   141,   145,   149,   153,   156,   160,   162,   164,
     166,   168,   170,   172,   174,   177,   180,   184,   188,   192
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    -1,    60,    -1,    57,    60,    -1,
      48,    57,    49,    -1,     5,    67,    60,    -1,     5,    67,
      60,     6,    60,    -1,    10,    67,    60,    -1,    58,    -1,
      61,    50,    -1,    59,    -1,    62,    -1,    68,    -1,    63,
      -1,    64,    -1,     4,    67,    -1,    65,    51,    67,    -1,
       3,    65,    -1,     3,    65,    51,    67,    -1,    35,    -1,
      52,    67,    52,    -1,    35,    -1,    52,    67,    52,    -1,
      67,    24,    67,    -1,    67,    25,    67,    -1,    67,    27,
      67,    -1,    41,    67,    -1,    67,    40,    67,    -1,    67,
      39,    67,    -1,    67,    12,    67,    -1,    67,    13,    67,
      -1,    67,    14,    67,    -1,    67,    17,    67,    -1,    67,
      22,    67,    -1,    67,    21,    67,    -1,    67,    18,    67,
      -1,    67,    23,    67,    -1,    67,    19,    67,    -1,    67,
      20,    67,    -1,    67,    42,    67,    -1,    67,    43,    67,
      -1,    67,    44,    67,    -1,    67,    45,    67,    -1,    67,
      46,    67,    -1,    44,    67,    -1,    53,    67,    54,    -1,
      37,    -1,    66,    -1,    36,    -1,    38,    -1,     7,    -1,
       8,    -1,     9,    -1,    65,    28,    -1,    65,    29,    -1,
      65,    30,    67,    -1,    65,    31,    67,    -1,    65,    32,
      67,    -1,    65,    33,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    96,    96,   107,   110,   116,   121,   123,   125,   127,
     132,   134,   139,   141,   143,   145,   147,   152,   157,   162,
     167,   169,   174,   176,   181,   183,   185,   187,   189,   191,
     193,   195,   197,   199,   201,   203,   205,   207,   209,   211,
     213,   215,   217,   219,   221,   223,   225,   227,   229,   231,
     233,   235,   237,   239,   244,   246,   248,   250,   252,   254
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKVAR", "TOKPRINT", "TOKIF", "TOKELSE",
  "TOKNOTHING", "TOKTRUE", "TOKFALSE", "TOKWHILE", "TOKDEF", "EQ", "LTEQ",
  "GTEQ", "LT", "GT", "NE", "SEQ", "SLTEQ", "SGTEQ", "SLT", "SGT", "SNE",
  "AND", "OR", "NOT", "XOR", "INCR", "DECR", "PLUSEQUALS", "MINUSEQUALS",
  "TIMESEQUALS", "DIVEQUALS", "UNARY_MINUS", "NAME", "INTEGER", "STRLIT",
  "FLOAT", "'<'", "'>'", "'!'", "':'", "'+'", "'-'", "'*'", "'/'", "'^'",
  "'{'", "'}'", "';'", "'='", "'`'", "'('", "')'", "$accept", "program",
  "statementlist", "block", "qualifiedblock", "statement",
  "singlestatement", "assignment", "newvar", "declare", "newvarname",
  "varname", "expr", "reassigner", YY_NULL
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,    60,
      62,    33,    58,    43,    45,    42,    47,    94,   123,   125,
      59,    61,    96,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    59,    59,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    62,    63,    64,
      65,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    68,    68,    68,    68,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     3,     5,     3,     1,
       2,     1,     1,     1,     1,     1,     2,     3,     2,     4,
       1,     3,     1,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    20,     0,     0,     0,     2,
       9,    11,     3,     0,    12,    14,    15,     0,    13,    18,
      51,    52,    53,    22,    49,    47,    50,     0,     0,     0,
       0,    48,    16,     0,     0,     0,     0,     1,     4,    10,
      54,    55,     0,     0,     0,     0,     0,     0,    27,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     8,     5,    21,    56,    57,    58,    59,
      17,    19,    23,    46,    30,    31,    32,    33,    36,    38,
      39,    35,    34,    37,    24,    25,    26,    29,    28,    40,
      41,    42,    43,    44,     0,     7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    31,    32,    18
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -41
static const yytype_int16 yypact[] =
{
     115,   -34,   120,   120,   120,   -41,   115,   120,     2,   115,
     -41,   -41,   -41,   -18,   -41,   -41,   -41,   -20,   -41,   -17,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   120,   120,   120,
     120,   -41,   267,    69,    69,    95,   195,   -41,   -41,   -41,
     -41,   -41,   120,   120,   120,   120,   120,   120,   -23,   -41,
     231,   157,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,    27,   -41,   -41,   -41,   267,   267,   267,   267,
     267,   267,   -41,   -41,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   302,   302,   302,   -23,   -23,   -29,
     -40,   -40,   -41,   -41,   115,   -41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,    29,   -41,   -41,    -9,   -41,   -41,   -41,   -41,
      35,   -41,     0,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      38,     5,    37,    33,    34,    70,    71,    36,    40,    41,
      42,    43,    44,    45,    68,    69,    70,    71,     7,    67,
      68,    69,    70,    71,    72,    73,    38,    48,    49,    50,
      51,    46,    39,   104,    47,    35,    19,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,     0,     0,
       0,     0,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     1,     2,     3,     0,     0,     0,     0,     4,
       0,    52,    53,    54,     0,     0,    55,    56,    57,    58,
      59,    60,    61,    62,    63,   105,    64,     0,     1,     2,
       3,     0,     0,     0,     5,     4,     0,     0,    65,    66,
       0,    67,    68,    69,    70,    71,     0,     6,     1,     2,
       3,     7,     0,     0,     0,     4,     0,    20,    21,    22,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    74,     0,     0,     7,     0,     0,
       5,     0,     0,     0,     0,    23,    24,    25,    26,     0,
       0,    27,     0,     6,    28,     0,     0,     7,     0,    52,
      53,    54,    29,    30,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,     0,    67,
      68,    69,    70,    71,     0,     0,     0,    52,    53,    54,
       0,    83,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,     0,    67,    68,    69,
      70,    71,     0,    52,    53,    54,     0,    75,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,     0,    67,    68,    69,    70,    71,     0,    52,
      53,    54,     0,    82,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,     0,    67,
      68,    69,    70,    71,    52,    53,    54,     0,     0,    55,
      56,    57,    58,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,     0,    67,    68,    69,    70,    71
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       9,    35,     0,     3,     4,    45,    46,     7,    28,    29,
      30,    31,    32,    33,    43,    44,    45,    46,    52,    42,
      43,    44,    45,    46,    33,    34,    35,    27,    28,    29,
      30,    51,    50,     6,    51,     6,     1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,     3,     4,     5,    -1,    -1,    -1,    -1,    10,
      -1,    12,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,   104,    27,    -1,     3,     4,
       5,    -1,    -1,    -1,    35,    10,    -1,    -1,    39,    40,
      -1,    42,    43,    44,    45,    46,    -1,    48,     3,     4,
       5,    52,    -1,    -1,    -1,    10,    -1,     7,     8,     9,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    -1,    52,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    41,    -1,    48,    44,    -1,    -1,    52,    -1,    12,
      13,    14,    52,    53,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    12,    13,    14,
      -1,    54,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    -1,    42,    43,    44,
      45,    46,    -1,    12,    13,    14,    -1,    52,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    -1,    42,    43,    44,    45,    46,    -1,    12,
      13,    14,    -1,    52,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,
      43,    44,    45,    46,    12,    13,    14,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    -1,    42,    43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    10,    35,    48,    52,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    68,    65,
       7,     8,     9,    35,    36,    37,    38,    41,    44,    52,
      53,    66,    67,    67,    67,    57,    67,     0,    60,    50,
      28,    29,    30,    31,    32,    33,    51,    51,    67,    67,
      67,    67,    12,    13,    14,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    27,    39,    40,    42,    43,    44,
      45,    46,    60,    60,    49,    52,    67,    67,    67,    67,
      67,    67,    52,    54,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,     6,    60
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
#line 96 "grammar.y"
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
#line 107 "grammar.y"
    {
        if (debug) printf(": %c\n", (yyvsp[(1) - (1)].n)->op);
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 110 "grammar.y"
    {
        if (debug) printf(". %c\n", (yyvsp[(2) - (2)].n)->op);
        (yyval.n) = node(MULTI, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 116 "grammar.y"
    {
        (yyval.n) = node(ENCLOSED_SCOPE, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 121 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (3)].n), node(IFELSE, (yyvsp[(3) - (3)].n), NULL));
    }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 123 "grammar.y"
    {
        (yyval.n) = node(IF, (yyvsp[(2) - (5)].n), node(IFELSE, (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n)));
    }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 125 "grammar.y"
    {
        (yyval.n) = node(WHILE, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 127 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 132 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (2)].n);
    }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 134 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 139 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 141 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 143 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 145 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 147 "grammar.y"
    {
        (yyval.n) = node(PRINT, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 152 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 157 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 162 "grammar.y"
    {
        (yyval.n) = node(CREATE, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 167 "grammar.y"
    {
        (yyval.n) = node_str((yyvsp[(1) - (1)].s));
    }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 169 "grammar.y"
    {
        (yyval.n) = node(VARNAME, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 174 "grammar.y"
    {
        (yyval.n) = node_name((yyvsp[(1) - (1)].s));
    }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 176 "grammar.y"
    {
        (yyval.n) = node(VARNAME, (yyvsp[(2) - (3)].n), NULL);
    }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 181 "grammar.y"
    {
        (yyval.n) = node(BAND, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 183 "grammar.y"
    {
        (yyval.n) = node(BOR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 185 "grammar.y"
    {
        (yyval.n) = node(BXOR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 187 "grammar.y"
    {
        (yyval.n) = node(BNOT, (yyvsp[(2) - (2)].n), NULL);
    }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 189 "grammar.y"
    {
        (yyval.n) = node(NUM_GT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 191 "grammar.y"
    {
        (yyval.n) = node(NUM_LT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 193 "grammar.y"
    {
        (yyval.n) = node(NUM_EQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 195 "grammar.y"
    {
        (yyval.n) = node(NUM_LTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 197 "grammar.y"
    {
        (yyval.n) = node(NUM_GTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 199 "grammar.y"
    {
        (yyval.n) = node(NUM_NE, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 201 "grammar.y"
    {
        (yyval.n) = node(STR_GT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 203 "grammar.y"
    {
        (yyval.n) = node(STR_LT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 205 "grammar.y"
    {
        (yyval.n) = node(STR_EQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 207 "grammar.y"
    {
        (yyval.n) = node(STR_NE, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 209 "grammar.y"
    {
        (yyval.n) = node(STR_LTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 211 "grammar.y"
    {
        (yyval.n) = node(STR_GTEQ, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 213 "grammar.y"
    {
        (yyval.n) = node(CONCAT, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 215 "grammar.y"
    {
        (yyval.n) = node(ADD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 217 "grammar.y"
    {
        (yyval.n) = node(SUB, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 219 "grammar.y"
    {
        (yyval.n) = node(MUL, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 221 "grammar.y"
    {
        (yyval.n) = node(DIV, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 223 "grammar.y"
    {
        (yyval.n) = node(SUB, node_int(0), (yyvsp[(2) - (2)].n));
    }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 225 "grammar.y"
    {
        (yyval.n) = (yyvsp[(2) - (3)].n);
    }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 227 "grammar.y"
    {
        (yyval.n) = node_str((yyvsp[(1) - (1)].s));
    }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 229 "grammar.y"
    {
        (yyval.n) = (yyvsp[(1) - (1)].n);
    }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 231 "grammar.y"
    {
        (yyval.n) = node_int((yyvsp[(1) - (1)].i));
    }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 233 "grammar.y"
    {
        (yyval.n) = node_dbl((yyvsp[(1) - (1)].d));
    }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 235 "grammar.y"
    {
        (yyval.n) = node_nothing();
    }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 237 "grammar.y"
    {
        (yyval.n) = node_boolean(1);
    }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 239 "grammar.y"
    {
        (yyval.n) = node_boolean(0);
    }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 244 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (2)].n), node(ADD, node(VARNAME, (yyvsp[(1) - (2)].n), NULL), node_int(1)));
    }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 246 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (2)].n), node(SUB, node(VARNAME, (yyvsp[(1) - (2)].n), NULL), node_int(1)));
    }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 248 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), node(ADD, node(VARNAME, (yyvsp[(1) - (3)].n), NULL), (yyvsp[(3) - (3)].n)));
    }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 250 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), node(SUB, node(VARNAME, (yyvsp[(1) - (3)].n), NULL), (yyvsp[(3) - (3)].n)));
    }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 252 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), node(MUL, node(VARNAME, (yyvsp[(1) - (3)].n), NULL), (yyvsp[(3) - (3)].n)));
    }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 254 "grammar.y"
    {
        (yyval.n) = node(ASSIGN, (yyvsp[(1) - (3)].n), node(DIV, node(VARNAME, (yyvsp[(1) - (3)].n), NULL), (yyvsp[(3) - (3)].n)));
    }
    break;


/* Line 1787 of yacc.c  */
#line 2083 "y.tab.c"
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
#line 257 "grammar.y"

