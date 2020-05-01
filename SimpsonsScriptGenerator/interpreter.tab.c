/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 12 "interpreter.y" /* yacc.c:339  */

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

extern "C" int yylex();
extern "C" int yyparse();

void yyerror(const char *s);

// map to store word progression
std::map<std::string, std::map<std::string, int>> wordsToNextCount;

// stores the previous word
std::string previousWord;

// Helper function to compare const char * for map iterator
class StrCompare {
public:
  bool operator ()(const char*a, const char*b) const {
	return strcmp(a,b) < 0;
  }
};


std::map<char*, int, StrCompare> var_to_int;


#line 99 "interpreter.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "interpreter.tab.h".  */
#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EOL = 258,
    PUNCTUATION = 259,
    COMMA = 260,
    ADJECTIVE = 261,
    ADJECTIVENOUN = 262,
    ADJECTIVEVERB = 263,
    ADVERB = 264,
    NOUN = 265,
    PRONOUN = 266,
    CONTRACTION = 267,
    NOUNVERB = 268,
    VERB = 269,
    PREPOSITION = 270,
    ARTICLE = 271,
    CONJUNCTION = 272,
    ADVERBNOUN = 273,
    CHARACTER = 274,
    QWORD = 275,
    ADJECTIVENOUNVERB = 276
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 46 "interpreter.y" /* yacc.c:355  */


	int iVal;
	char* sVal;
	

#line 168 "interpreter.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 185 "interpreter.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   188

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   115,   119,   122,   126,   130,   136,   140,
     144,   149,   153,   157,   161,   165,   169,   173,   177,   181,
     185,   189,   193,   197,   201,   205,   209,   213,   217,   221,
     225,   229,   233,   237,   273,   277,   281,   285,   289,   293,
     297,   301,   305,   309,   313,   319,   327,   339,   343,   347,
     355,   359,   363,   370,   378,   382,   386,   390,   394,   398,
     402,   406,   410,   414,   418,   422,   426,   439,   443,   447,
     451,   455,   459,   463,   470,   474,   478,   482,   491,   495
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EOL", "PUNCTUATION", "COMMA",
  "ADJECTIVE", "ADJECTIVENOUN", "ADJECTIVEVERB", "ADVERB", "NOUN",
  "PRONOUN", "CONTRACTION", "NOUNVERB", "VERB", "PREPOSITION", "ARTICLE",
  "CONJUNCTION", "ADVERBNOUN", "CHARACTER", "QWORD", "ADJECTIVENOUNVERB",
  "$accept", "quote", "$@1", "sentence", "simple", "compound",
  "sentencePart", "subjectPhrase", "nounPhrase", "verbPhrase",
  "verbClause", "objectPhrase", "objectNounClause", "complementPhrase",
  "adjectivePhrase", "adverbialPhrase", "adverbPhrase", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
};
# endif

#define YYPACT_NINF -37

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-37)))

#define YYTABLE_NINF -59

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -12,    94,     2,    17,    47,   -37,    26,    -4,    54,    51,
      -1,   -37,   -37,    55,   -37,   -37,    29,   156,    53,   130,
     -37,   119,   -37,   -37,   -37,   -37,   -37,   -37,   -37,    65,
     -37,   -37,   -37,    61,   -37,    68,    78,   110,    14,   -37,
     -37,   -37,   -37,   -37,   -37,    80,   -37,   -37,   162,     5,
     110,    88,    66,    33,   -37,   156,   141,   -12,   -37,   -37,
      94,    94,    42,    46,    81,   149,   168,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,    87,    98,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   156,   -37,   -37,   149,   156,    66,
     -37,   -37,    97,   -37,    38,   168,   -37,   -37,   -37,   -37,
     -37,   156,   -37,   -37,   168,   -37,   -37,   168,   156,   179,
     -37,   -37,   -37,   168,     4,   -37,    -1,   -37
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     7,     0,     0,    74,    42,    34,     0,    46,    45,
      44,    43,    75,     0,     5,     6,     0,     0,    36,     0,
      49,     0,    78,     1,     2,    79,    35,    48,    47,     0,
      52,    76,    77,     0,     8,     0,     0,    12,     0,    38,
      37,    41,    72,    73,    68,     0,    65,    58,     0,     0,
      15,    63,    25,    69,    44,     0,     0,     4,    50,    51,
       0,     0,    74,     0,    11,    17,    13,    39,    40,    67,
      59,    61,    62,    60,     0,     0,    53,    56,    57,    66,
      31,    29,    30,    64,     0,    70,    71,     0,     0,     0,
       3,     9,     0,    10,    46,     0,    14,    20,    22,    32,
      18,    21,    55,    54,     0,    19,    16,     0,     0,    23,
      33,    27,    26,     0,     0,    28,     0,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,    56,   -37,   -37,   -16,   -37,   113,   -15,   -37,   -17,
     -37,   -34,   -37,   -29,   -37,   -36,   -37
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    57,     3,    14,    15,    92,    17,    18,    19,
      20,    50,    51,    52,    53,    21,    22
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    66,    23,    64,    56,    31,    55,     1,    65,    27,
      28,    74,    75,     4,    82,    76,    80,    32,    77,   116,
      24,    81,    12,    78,    67,    68,    79,    89,    98,   100,
      96,    99,   101,    34,    35,    97,    26,    84,    87,    85,
      86,    88,   -58,   -58,    91,    93,    36,    95,    69,    25,
      29,   106,    31,   105,    25,   -58,    70,    71,    38,    72,
      39,   109,    73,    40,    32,    30,    29,   104,    33,    41,
     111,   107,    58,   112,   108,    59,     5,     6,   117,   115,
     114,    54,    11,    61,   110,    60,    69,    42,    43,    44,
      62,   113,    46,     7,    94,     9,    63,    49,    83,    12,
     102,    34,    13,     4,     5,     6,     7,     8,     9,    10,
      11,   103,    12,    90,    16,    13,    42,    43,    44,    62,
       0,    46,     0,    47,     0,    63,    49,     0,    12,     5,
       6,     7,     8,     9,    54,    11,    42,    43,    44,    45,
      13,    46,     0,    47,     0,    48,    49,    42,    43,    44,
      45,     5,     6,     0,     0,     0,    54,    11,     4,     0,
      46,     0,    47,     0,    63,    49,     0,    12,     7,     8,
       9,     0,    70,    71,     0,    72,     0,    13,    73,    46,
       0,    47,     0,    48,    49,    42,    43,    44,    45
};

static const yytype_int8 yycheck[] =
{
      17,    37,     0,    37,    21,     6,    21,    19,    37,    13,
      14,     6,     7,     9,    50,    10,    50,    18,    13,    15,
       3,    50,    18,    18,    10,    11,    21,    56,    64,    65,
      64,    65,    66,     4,     5,    64,    10,    52,    55,     6,
       7,    56,     4,     5,    60,    61,    17,    64,     6,     7,
      12,    87,     6,    87,     7,    17,    10,    11,     5,    13,
       7,    95,    16,    10,    18,    14,    12,    84,    13,    16,
     104,    88,     7,   107,    89,    14,    10,    11,   114,   113,
     109,    15,    16,     5,   101,    17,     6,     6,     7,     8,
       9,   108,    11,    12,    13,    14,    15,    16,    10,    18,
      13,     4,    21,     9,    10,    11,    12,    13,    14,    15,
      16,    13,    18,    57,     1,    21,     6,     7,     8,     9,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    10,
      11,    12,    13,    14,    15,    16,     6,     7,     8,     9,
      21,    11,    -1,    13,    -1,    15,    16,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    15,    16,     9,    -1,
      11,    -1,    13,    -1,    15,    16,    -1,    18,    12,    13,
      14,    -1,    10,    11,    -1,    13,    -1,    21,    16,    11,
      -1,    13,    -1,    15,    16,     6,     7,     8,     9
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    23,    25,     9,    10,    11,    12,    13,    14,
      15,    16,    18,    21,    26,    27,    28,    29,    30,    31,
      32,    37,    38,     0,     3,     7,    10,    13,    14,    12,
      14,     6,    18,    13,     4,     5,    17,    31,     5,     7,
      10,    16,     6,     7,     8,     9,    11,    13,    15,    16,
      33,    34,    35,    36,    15,    29,    31,    24,     7,    14,
      17,     5,     9,    15,    33,    35,    37,    10,    11,     6,
      10,    11,    13,    16,     6,     7,    10,    13,    18,    21,
      33,    35,    37,    10,    29,     6,     7,    31,    29,    35,
      23,    26,    28,    26,    13,    31,    33,    35,    37,    33,
      37,    33,    13,    13,    31,    33,    37,    31,    29,    33,
      31,    33,    33,    31,    35,    33,    15,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    22,    24,    23,    23,    25,    25,    25,    26,    27,
      27,    28,    28,    28,    28,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    29,    29,    29,    30,    30,    30,
      30,    30,    30,    30,    30,    31,    31,    31,    31,    31,
      31,    31,    32,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    34,    34,    34,    35,    35,    35,
      36,    36,    36,    36,    37,    37,    37,    37,    37,    38
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     2,     2,     1,     2,     4,
       4,     3,     2,     3,     4,     2,     4,     3,     4,     4,
       4,     4,     4,     5,     7,     2,     5,     5,     6,     3,
       3,     3,     4,     5,     1,     2,     1,     2,     2,     3,
       3,     2,     1,     1,     1,     1,     1,     2,     2,     1,
       3,     3,     2,     2,     3,     3,     2,     2,     1,     2,
       2,     2,     2,     1,     2,     1,     2,     2,     1,     1,
       2,     2,     1,     1,     1,     1,     2,     2,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 115 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "sentence EOL quote" << std::endl;
			 }
#line 1354 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 122 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "CHARACTER simple" << std::endl;
}
#line 1362 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 126 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "CHARACTER compound" << std::endl;
	}
#line 1370 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 130 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "CHARACTER" << std::endl;
		// Generate a sentence..
	}
#line 1379 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 136 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "sentencePart PUNCTUATION" << std::endl;
}
#line 1387 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 140 "interpreter.y" /* yacc.c:1646  */
    { // e.g. she loves cheese, but i love pie
	std::cout << "sentencePart COMMA CONJUNCTION simple" << std::endl;
}
#line 1395 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 144 "interpreter.y" /* yacc.c:1646  */
    { // e.g. 
		std::cout << "sentencePart CONJUNCTION COMMA simple" << std::endl;
	}
#line 1403 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 149 "interpreter.y" /* yacc.c:1646  */
    { // SVO, e.g. I love cheese
	std::cout << "subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1411 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 153 "interpreter.y" /* yacc.c:1646  */
    { // SV e.g. john conspired
		std::cout << "subjectPhrase verbPhrase" << std::endl;
	}
#line 1419 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 157 "interpreter.y" /* yacc.c:1646  */
    { // SVA e.g. john conspired shamefully
		std::cout << "subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
#line 1427 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 161 "interpreter.y" /* yacc.c:1646  */
    { // SVOO e.g. John gave Jane a present, john made a cup of tea
		std::cout << "subjectPhrase verbPhrase objectPhrase objectPhrase" << std::endl;
	}
#line 1435 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 165 "interpreter.y" /* yacc.c:1646  */
    { // VO, e.g. call him
		std::cout << "verbPhrase objectPhrase" << std::endl;
	}
#line 1443 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 169 "interpreter.y" /* yacc.c:1646  */
    { // ASVA e.g. soon we wake up
		std::cout << "adverbialPhrase subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
#line 1451 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 173 "interpreter.y" /* yacc.c:1646  */
    { // SVC, e.g. her mom is so nice
		std::cout << "subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
#line 1459 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 177 "interpreter.y" /* yacc.c:1646  */
    { // SVCA, e.g. her mom is so nice lately
		std::cout << "subjectPhrase verbPhrase complementPhrase adverbialPhrase" << std::endl;
	}
#line 1467 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 181 "interpreter.y" /* yacc.c:1646  */
    { // ASVO e.g. lately i love cheese
		std::cout << "adverbialPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
#line 1475 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 185 "interpreter.y" /* yacc.c:1646  */
    { // SVOC e.g. John made jane angry
		std::cout << "subjectPhrase verbPhrase objectPhrase complementPhrase" << std::endl;
	}
#line 1483 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 189 "interpreter.y" /* yacc.c:1646  */
    { // SVAO e.g. She went up the stairs
		std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase" << std::endl;
	}
#line 1491 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 193 "interpreter.y" /* yacc.c:1646  */
    { // SVOA e.g. it was a little of both
		std::cout << "subjectPhrase verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
#line 1499 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 197 "interpreter.y" /* yacc.c:1646  */
    { // SVOVO e.g. you think you have it
		std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1507 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 201 "interpreter.y" /* yacc.c:1646  */
    { // SVOVOCA e.g. I don't think there's anything left to say
		std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase complementPhrase adverbialPhrase" << std::endl;
	}
#line 1515 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 205 "interpreter.y" /* yacc.c:1646  */
    { // VC e.g. it's only natural
		std::cout << "verbPhrase complementPhrase" << std::endl;
	}
#line 1523 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 209 "interpreter.y" /* yacc.c:1646  */
    { // AVSVO e.g. what did he teach you?
		std::cout << "adverbialPhrase verbPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1531 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 213 "interpreter.y" /* yacc.c:1646  */
    { // VCSVO e.g. I'd sure like to talk to him
		std::cout << "verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1539 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 217 "interpreter.y" /* yacc.c:1646  */
    { // VCSVO e.g. Although I'd sure like to talk to him
		std::cout << "adverbialPhrase verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1547 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 221 "interpreter.y" /* yacc.c:1646  */
    { // VOC e.g. are you stupid?
		std::cout << "verbPhrase objectPhrase complementPhrase" << std::endl;
	}
#line 1555 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 225 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
#line 1563 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 229 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "verbPhrase objectPhrase objectPhrase" << std::endl;
	}
#line 1571 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 233 "interpreter.y" /* yacc.c:1646  */
    { // SVCO e.g. she makes good pie.
		std::cout << "subjectPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
#line 1579 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 237 "interpreter.y" /* yacc.c:1646  */
    { // SVAOV i.e. I wonder how he died. 
		std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase verbPhrase" << std::endl;
	}
#line 1587 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 273 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "PRONOUN" << std::endl;
}
#line 1595 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 277 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PRONOUN NOUN" << std::endl;
	}
#line 1603 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 281 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "nounPhrase" << std::endl;
	}
#line 1611 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 285 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "nounPhrase NOUN" << std::endl;
}
#line 1619 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 289 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "nounPhrase ADJECTIVENOUN" << std::endl;
	}
#line 1627 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 293 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "nounPhrase COMMA NOUN" << std::endl;
	}
#line 1635 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 297 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "nounPhrase COMMA PRONOUN" << std::endl;
	}
#line 1643 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 301 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "nounPhrase ARTICLE" << std::endl;
	}
#line 1651 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 305 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "NOUN" << std::endl;
	}
#line 1659 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 309 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ARTICLE" << std::endl;
	}
#line 1667 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 313 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION" << std::endl;
	}
#line 1675 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 319 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "VERB" << std::endl;
}
#line 1683 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 327 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "NOUNVERB" << std::endl;
	}
#line 1691 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 339 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "CONTRACTION VERB" << std::endl;
	}
#line 1699 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 343 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "CONTRACTION NOUNVERB" << std::endl;
	}
#line 1707 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 347 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "verbClause" << std::endl;
	}
#line 1715 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 355 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "NOUNVERB CONTRACTION ADJECTIVENOUN" << std::endl;
	}
#line 1723 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 359 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ADJECTIVENOUNVERB NOUNVERB VERB" << std::endl;
	}
#line 1731 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 363 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "VERB VERB" << std::endl;
}
#line 1739 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 370 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "NOUN" << std::endl;
}
#line 1747 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 378 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ARTICLE ADJECTIVENOUN NOUNVERB" << std::endl;
	}
#line 1755 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 382 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ARTICLE ADJECTIVE NOUNVERB" << std::endl;
	}
#line 1763 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 386 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ARTICLE NOUNVERB" << std::endl; 
	}
#line 1771 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 390 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ARTICLE ADVERBNOUN" << std::endl;
	}
#line 1779 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 394 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "NOUNVERB" << std::endl;
	}
#line 1787 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 398 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION NOUN" << std::endl;
	}
#line 1795 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 402 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION ARTICLE" << std::endl;
	}
#line 1803 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 406 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION PRONOUN" << std::endl;
	}
#line 1811 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 410 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION NOUNVERB" << std::endl;
	}
#line 1819 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 414 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "objectNounClause" << std::endl;
	}
#line 1827 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 418 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "objectNounClause NOUN" << std::endl;
}
#line 1835 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 422 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PRONOUN" << std::endl;
	}
#line 1843 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 426 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ARTICLE ADJECTIVENOUNVERB" << std::endl;
	}
#line 1851 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 439 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ADVERB ADJECTIVE" << std::endl; // e.g. so cute
	}
#line 1859 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 443 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ADJECTIVEVERB" << std::endl;
	}
#line 1867 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 447 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "adjectivePhrase" << std::endl;
	}
#line 1875 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 451 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "adjectivePhrase ADJECTIVE" << std::endl;
}
#line 1883 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 455 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "adjectivePhrase ADJECTIVENOUN" << std::endl;
	}
#line 1891 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 459 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ADJECTIVE" << std::endl;
	}
#line 1899 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 463 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ADJECTIVENOUN" << std::endl;
	}
#line 1907 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 470 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "ADVERB" << std::endl;
}
#line 1915 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 474 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "ADVERBNOUN" << std::endl;
	}
#line 1923 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 478 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION ADJECTIVE" << std::endl;
	}
#line 1931 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 482 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "PREPOSITION ADVERBNOUN" << std::endl;
	}
#line 1939 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 491 "interpreter.y" /* yacc.c:1646  */
    {
		std::cout << "adverbPhrase" << std::endl;
	}
#line 1947 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 495 "interpreter.y" /* yacc.c:1646  */
    {
	std::cout << "ADVERB ADJECTIVENOUN" << std::endl;
}
#line 1955 "interpreter.tab.c" /* yacc.c:1646  */
    break;


#line 1959 "interpreter.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 503 "interpreter.y" /* yacc.c:1906  */


int main(int argc, char **argv) {
	extern FILE *yyin;
	FILE *f;
	f = fopen(argv[1], "r");
	if(argc == 2 && f)
		yyin = f;
	
	yyparse();
}

/* Display error messages */
void yyerror(const char *s) {
	printf("ERROR: %s\n", s);
}
