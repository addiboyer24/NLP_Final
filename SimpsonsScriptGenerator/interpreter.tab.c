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

#ifndef YYINITDEPTH

#define YYINITDEPTH 150000

#endif

extern "C" int yylex();
extern "C" int yyparse();
const char* space = " ";

void yyerror(const char *s);

std::map<std::string, int> *counts = new std::map<std::string, int>;

// map to store word progression
std::map<std::string, std::map<std::string, std::map<std::string, int>>> model;

// stores the previous word
//std::string previousWord;

int count = 0;
// function used to generate small talk script once model is trained..
void generateSmallTalk(std::map<std::string, int> *counts, int numLines, int numCharacters){
	printf("\n\nGenerating small talk with %d lines and %d characters\n", numLines, numCharacters);
	printf("Model trained on %d lines..\n", count);
	std::cout << "**THE SIMPSONS SMALL TALK CAST**" << std::endl;
	for(auto iter = counts->begin(); iter != counts->end(); iter++){
		if(iter->second >= 100)
			std::cout << iter->first << ": " << iter->second << std::endl;
	}
	std::cout << "*********************************" << std::endl;

}
// Function to vectorize sentence into words
std::vector<char*> vectorizeSentence(char* sentence){
	std::vector<char*> ret;

	char* token = strtok(sentence, " ");
	while(token != NULL){
		ret.push_back(token);
		token = strtok(NULL, " ");
	}

	return ret;
}

void printModelAtCharacter(std::map<std::string, std::map<std::string, std::map<std::string, int>>> &model, std::string character){
	std::cout << character << std::endl;
	auto firstToSecondCounts = model.find(character)->second;
	
	for(auto iter1 = firstToSecondCounts.begin(); iter1 != firstToSecondCounts.end(); iter1++){
		std::string first = iter1->first;
		auto secondToCounts = iter1->second;
		
		std::cout << "First: " << first << "\t";

		for(auto iter2 = secondToCounts.begin(); iter2 != secondToCounts.end(); iter2++){
			std::string word = iter2->first;
			int count = iter2->second;
			std::cout << word << ":" << count << ",\t";
		}

		std::cout << std::endl;
	}
}

void printCast(std::map<std::string, int> *counts){
	for(auto iter = counts->begin(); iter != counts->end(); iter++){
		std::cout << iter->first << ": " << iter->second << std::endl;
	}
}

std::map<std::string, std::vector<std::string>>* getAdditions(char* sentence){

	std::vector<char*> words = vectorizeSentence(sentence);

	std::map<std::string, std::vector<std::string>> *ret = new std::map<std::string, std::vector<std::string>>;

	for(int i = 1; i < words.size(); i++){
		std::string first(words.at(i-1));
		std::string second(words.at(i));

		// make a map of word to vector of second words..
		if(ret->find(first) != ret->end()){
			ret->find(first)->second.push_back(second);
		}
		else{
			std::vector<std::string> insert = {second};
			ret->insert(std::make_pair(first, insert));
		}
	}

	return ret;
}

void augmentModel(std::map<std::string, std::map<std::string, std::map<std::string, int>>> &map, std::map<std::string, std::vector<std::string>> additions, std::string character){

	// Character already seen.
	if(map.find(character) != map.end()){
		
		// For every new addition
		for(auto iter1 = additions.begin(); iter1 != additions.end(); iter1++){
			std::string first = iter1->first;

			// has seen "first" as the first word.
			if(map.find(character)->second.find(first) != map.find(character)->second.end()){
				for(auto iter2 = map.find(character)->second.find(first)->second.begin(); iter2 != map.find(character)->second.find(first)->second.end(); iter2++){
					std::string second = iter2->first;

					// has seen second before so increment
					if(map.find(character)->second.find(first)->second.find(second) != map.find(character)->second.find(first)->second.end()){
						map.find(character)->second.find(first)->second.find(second)->second += 1;
					}
					else{
						map.find(character)->second.find(first)->second.insert(std::make_pair(second, 1));
					}
				}
			}
			else{
				// create a new second to count map
				std::map<std::string, int> secondToCount;
				for(int i = 0; i < iter1->second.size(); i++){
					if(secondToCount.find(iter1->second[i]) != secondToCount.end()){
						secondToCount.find(iter1->second[i])->second += 1;
					}
					else{
						secondToCount.insert(std::make_pair(iter1->second[i], 1));
					}
				}

				map.find(character)->second.insert(std::make_pair(first, secondToCount));
				
			}
		}
	}
	else{
		std::map<std::string, std::map<std::string, int>> append;
		for(auto iter = additions.begin(); iter != additions.end(); iter++){
			std::string key = iter->first;
			std::vector<std::string> words = iter->second;
			std::map<std::string, int> secondToCount;

			for(int i = 0; i < words.size(); i++){
				if(secondToCount.find(words[i]) != secondToCount.end()){
					secondToCount.find(words[i])->second += 1;
				}
				else{
					secondToCount.insert(std::make_pair(words[i], 1));
				}
			}

			append.insert(std::make_pair(key, secondToCount));
		}

		map.insert(std::make_pair(character, append));
	}
}

void printMap(std::map<std::string, int> &map){
	for(auto iter = map.begin(); iter != map.end(); iter++){
		std::cout << iter->first << " " << iter->second << std::endl;
	}
}

// Helper function to compare const char * for map iterator
class StrCompare {
public:
  bool operator ()(const char*a, const char*b) const {
	return strcmp(a,b) < 0;
  }
};



std::map<char*, int, StrCompare> var_to_int;


#line 253 "interpreter.tab.c" /* yacc.c:339  */

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
    ADJECTIVENOUNVERB = 276,
    CAST = 277
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 200 "interpreter.y" /* yacc.c:355  */


	int iVal;
	char* sVal;
	

#line 323 "interpreter.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 340 "interpreter.tab.c" /* yacc.c:358  */

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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  23
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   271,   271,   271,   276,   279,   300,   318,   329,   334,
     339,   347,   356,   362,   368,   374,   380,   386,   392,   398,
     404,   410,   416,   422,   428,   434,   440,   446,   452,   458,
     464,   470,   476,   482,   488,   494,   500,   506,   516,   522,
     530,   535,   542,   549,   557,   565,   572,   578,   584,   592,
     597,   604,   611,   618,   624,   630,   636,   645,   653,   662,
     671,   679,   687,   695,   703,   711,   719,   724,   731,   737,
     746,   754,   760,   765,   772,   779,   786,   792,   798,   807,
     813,   819,   827,   835,   840
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
  "CAST", "$accept", "quote", "$@1", "sentence", "simple", "compound",
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
     275,   276,   277
};
# endif

#define YYPACT_NINF -31

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-31)))

#define YYTABLE_NINF -79

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   143,   -31,     4,    -1,     5,   -31,     8,   -31,   -31,
     -31,    16,   -31,   -31,   -31,   -31,   -31,    10,    55,    39,
     107,    68,   165,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,    11,    37,   107,    25,   -31,   -31,   -31,   -31,   -31,
     -31,   104,   -31,   156,   130,   -31,    91,    40,    62,    18,
     -31,   -31,   -31,   -31,   -31,    55,   123,    29,   143,   143,
      91,   173,   131,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
      41,    70,   -31,   -31,   -31,   -31,    53,   131,   -31,   -31,
     -31,   -31,    55,   -31,   -31,   -31,   107,    46,    55,    62,
     -31,   -31,    83,   -31,   131,   -31,   -31,   -31,   -31,   -31,
      79,    55,   -31,   -31,   -31,   131,   -31,   -31,   -31,   131,
      55,     0,   -31,   -31,   -31,   131,     2,   -31,    16,   -31
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     7,     8,     0,     0,    79,    46,    38,    54,    55,
      53,    48,    47,    80,    56,     5,     6,     0,     0,    40,
       0,    49,     0,    83,     1,     2,    84,    39,    81,    82,
       9,     0,     0,    13,     0,    42,    41,    45,    76,    77,
      71,    79,    68,     0,     0,    78,    16,    66,    27,    72,
      36,    52,    51,    50,    48,     0,     0,     4,     0,     0,
      12,    19,    14,    43,    44,    70,    62,    64,    65,    63,
       0,     0,    57,    60,    61,    69,    56,     0,    33,    31,
      32,    67,     0,    73,    74,    75,     0,     0,     0,     0,
       3,    10,     0,    11,     0,    15,    22,    24,    34,    20,
       0,    23,    59,    58,    17,     0,    21,    37,    18,     0,
       0,    25,    35,    29,    28,     0,     0,    30,     0,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,    34,   -31,   -31,     3,   -31,    93,    -3,   -31,   -17,
     -31,   -30,   -31,   -23,   -31,   -20,   -31
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,    57,     4,    15,    16,    92,    18,    19,    20,
      21,    46,    47,    48,    49,    22,    23
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      50,    33,    25,    60,    24,    56,    38,    39,    40,    87,
      61,     5,    26,    62,    30,    31,    78,   118,    27,    55,
      13,    45,    28,    79,    83,    84,    80,    32,    58,    77,
      95,    98,   101,    89,    29,    63,    64,    96,    86,    85,
      97,    99,    59,    94,    34,    82,    35,   104,     1,    36,
      81,     2,    65,    88,   102,    37,   106,   -78,   -78,   -78,
     -78,    91,    93,   107,   111,   105,   108,     8,     9,    10,
     -78,   109,     6,     7,   -78,   113,    14,    54,    12,   114,
      51,    52,    53,   103,   112,   117,   110,    30,   116,    66,
      67,    90,    68,   115,    17,    69,   119,    38,    39,    40,
      41,     0,    42,     8,     9,    10,    43,    44,     0,    13,
      65,    26,    76,    38,    39,    40,    41,     0,    42,     0,
       0,     0,    43,    44,     0,    13,     0,     0,    45,    38,
      39,    40,    87,     6,     7,     0,    70,    71,    54,    12,
      72,     0,    42,    73,    45,     0,   100,    44,    74,     0,
       0,    75,     5,     6,     7,     8,     9,    10,    11,    12,
       0,    13,    28,     0,    14,     0,    66,    67,     0,    68,
       0,     0,    69,     0,    29,     6,     7,     8,     9,    10,
      54,    12,     5,     0,    42,     0,    14,     0,    43,    44,
       0,    13
};

static const yytype_int8 yycheck[] =
{
      20,    18,     3,    33,     0,    22,     6,     7,     8,     9,
      33,     9,     7,    33,     4,     5,    46,    15,    10,    22,
      18,    21,     6,    46,     6,     7,    46,    17,    17,    46,
      60,    61,    62,    56,    18,    10,    11,    60,    55,    21,
      60,    61,     5,    60,     5,    48,     7,    77,    19,    10,
      10,    22,     6,    56,    13,    16,    86,     4,     5,     6,
       7,    58,    59,    86,    94,    82,    86,    12,    13,    14,
      17,    88,    10,    11,    21,   105,    21,    15,    16,   109,
      12,    13,    14,    13,   101,   115,    89,     4,   111,    10,
      11,    57,    13,   110,     1,    16,   116,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    -1,    18,
       6,     7,    21,     6,     7,     8,     9,    -1,    11,    -1,
      -1,    -1,    15,    16,    -1,    18,    -1,    -1,    21,     6,
       7,     8,     9,    10,    11,    -1,     6,     7,    15,    16,
      10,    -1,    11,    13,    21,    -1,    15,    16,    18,    -1,
      -1,    21,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    18,     6,    -1,    21,    -1,    10,    11,    -1,    13,
      -1,    -1,    16,    -1,    18,    10,    11,    12,    13,    14,
      15,    16,     9,    -1,    11,    -1,    21,    -1,    15,    16,
      -1,    18
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    22,    24,    26,     9,    10,    11,    12,    13,
      14,    15,    16,    18,    21,    27,    28,    29,    30,    31,
      32,    33,    38,    39,     0,     3,     7,    10,     6,    18,
       4,     5,    17,    32,     5,     7,    10,    16,     6,     7,
       8,     9,    11,    15,    16,    21,    34,    35,    36,    37,
      38,    12,    13,    14,    15,    30,    32,    25,    17,     5,
      34,    36,    38,    10,    11,     6,    10,    11,    13,    16,
       6,     7,    10,    13,    18,    21,    21,    32,    34,    36,
      38,    10,    30,     6,     7,    21,    32,     9,    30,    36,
      24,    27,    29,    27,    32,    34,    36,    38,    34,    38,
      15,    34,    13,    13,    34,    32,    34,    36,    38,    32,
      30,    34,    32,    34,    34,    32,    36,    34,    15,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    23,    25,    24,    24,    26,    26,    26,    26,    27,
      28,    28,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    30,    30,
      30,    31,    31,    31,    31,    31,    31,    31,    31,    32,
      33,    33,    33,    33,    33,    33,    33,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    35,    35,    35,
      36,    36,    36,    37,    37,    37,    37,    37,    37,    38,
      38,    38,    38,    38,    39
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     2,     2,     1,     1,     2,
       4,     4,     3,     2,     3,     4,     2,     4,     4,     3,
       4,     4,     4,     4,     4,     5,     7,     2,     5,     5,
       6,     3,     3,     3,     4,     5,     2,     4,     1,     2,
       1,     2,     2,     3,     3,     2,     1,     1,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     2,     3,     3,
       2,     2,     2,     2,     2,     2,     1,     2,     1,     2,
       2,     1,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     2,     2,     1,     2
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
#line 271 "interpreter.y" /* yacc.c:1646  */
    {
	//std::cout << "sentence EOL quote" << std::endl;
	count += 1;
			 }
#line 1515 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 279 "interpreter.y" /* yacc.c:1646  */
    {
	//std::cout << $1 << " simple" << std::endl;
	//std::cout << $1 << $2 << std::endl;
	std::string character((yyvsp[-1].sVal));

	// keep track of who's talking most..
	if(counts->find(character) != counts->end()){
		counts->find(character)->second += 1;
	}
	else{
		counts->insert(std::make_pair(character, 1));
	}
	
	//auto additions = getAdditions($2);
	//augmentModel(model, additions, character);
	//printModelAtCharacter(model, character);



}
#line 1540 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 300 "interpreter.y" /* yacc.c:1646  */
    {
		//std::cout << $1 << $2 << std::endl;
		std::string character((yyvsp[-1].sVal));

		// keep track of who's talking most..
		if(counts->find(character) != counts->end()){
		counts->find(character)->second += 1;
		}
		else{
			counts->insert(std::make_pair(character, 1));
		}

		//auto additions = getAdditions($2);
		//augmentModel(model, additions, character);
		//printModelAtCharacter(model, character);
		//std::cout << $1 << " compound" << std::endl;
	}
#line 1562 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 318 "interpreter.y" /* yacc.c:1646  */
    {
		//std::cout << "CHARACTER" << std::endl;
		// Generate a sentence..
		std::cout << (yyvsp[0].sVal) << " says something here.." << std::endl;

		for(auto iter = counts->begin(); iter != counts->end(); iter++){
			std::cout << iter->first << ": " << iter->second << std::endl;
		}

	}
#line 1577 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 329 "interpreter.y" /* yacc.c:1646  */
    {
		printCast(counts);
	}
#line 1585 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 334 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
}
#line 1594 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 339 "interpreter.y" /* yacc.c:1646  */
    { // e.g. she loves cheese, but i love pie
	strcat((yyvsp[-2].sVal), space);
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
	(yyval.sVal) = (yyvsp[-3].sVal);
	//std::cout << "sentencePart COMMA CONJUNCTION simple" << std::endl;
}
#line 1606 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 347 "interpreter.y" /* yacc.c:1646  */
    { // e.g. 
		strcat((yyvsp[-2].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "sentencePart CONJUNCTION COMMA simple" << std::endl;
	}
#line 1618 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 356 "interpreter.y" /* yacc.c:1646  */
    { // SVO, e.g. I love cheese
	strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
	(yyval.sVal) = (yyvsp[-2].sVal);
	//std::cout << "subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1628 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 362 "interpreter.y" /* yacc.c:1646  */
    { // SV e.g. john conspired
		//std::cout << "subjectPhrase verbPhrase" << std::endl;
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
	}
#line 1638 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 368 "interpreter.y" /* yacc.c:1646  */
    { // SVA e.g. john conspired shamefully
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
#line 1648 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 374 "interpreter.y" /* yacc.c:1646  */
    { // SVOO e.g. John gave Jane a present, john made a cup of tea
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase objectPhrase" << std::endl;
	}
#line 1658 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 380 "interpreter.y" /* yacc.c:1646  */
    { // VO, e.g. call him
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbPhrase objectPhrase" << std::endl;
	}
#line 1668 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 386 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1678 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 392 "interpreter.y" /* yacc.c:1646  */
    { // ASVA e.g. soon we wake up
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "adverbialPhrase subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
#line 1688 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 398 "interpreter.y" /* yacc.c:1646  */
    { // SVC, e.g. her mom is so nice
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
#line 1698 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 404 "interpreter.y" /* yacc.c:1646  */
    { // SVCA, e.g. her mom is so nice lately
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase complementPhrase adverbialPhrase" << std::endl;
	}
#line 1708 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 410 "interpreter.y" /* yacc.c:1646  */
    { // ASVO e.g. lately i love cheese
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "adverbialPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
#line 1718 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 416 "interpreter.y" /* yacc.c:1646  */
    { // SVOC e.g. John made jane angry
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase complementPhrase" << std::endl;
	}
#line 1728 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 422 "interpreter.y" /* yacc.c:1646  */
    { // SVAO e.g. She went up the stairs
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase" << std::endl;
	}
#line 1738 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 428 "interpreter.y" /* yacc.c:1646  */
    { // SVOA e.g. it was a little of both
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
#line 1748 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 434 "interpreter.y" /* yacc.c:1646  */
    { // SVOVO e.g. you think you have it
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1758 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 440 "interpreter.y" /* yacc.c:1646  */
    { // SVOVOCA e.g. I don't think there's anything left to say
		strcat((yyvsp[-6].sVal), strcat((yyvsp[-5].sVal), strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))))));
		(yyval.sVal) = (yyvsp[-6].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase complementPhrase adverbialPhrase" << std::endl;
	}
#line 1768 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 446 "interpreter.y" /* yacc.c:1646  */
    { // VC e.g. it's only natural
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbPhrase complementPhrase" << std::endl;
	}
#line 1778 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 452 "interpreter.y" /* yacc.c:1646  */
    { // AVSVO e.g. what did he teach you?
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "adverbialPhrase verbPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1788 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 458 "interpreter.y" /* yacc.c:1646  */
    { // VCSVO e.g. I'd sure like to talk to him
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1798 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 464 "interpreter.y" /* yacc.c:1646  */
    { // VCSVO e.g. Although I'd sure like to talk to him
		strcat((yyvsp[-5].sVal), strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))))));
		(yyval.sVal) = (yyvsp[-5].sVal);
		//std::cout << "adverbialPhrase verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 1808 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 470 "interpreter.y" /* yacc.c:1646  */
    { // VOC e.g. are you stupid?
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "verbPhrase objectPhrase complementPhrase" << std::endl;
	}
#line 1818 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 476 "interpreter.y" /* yacc.c:1646  */
    { // VOA e.g. I'll tell you what.
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
#line 1828 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 482 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "verbPhrase objectPhrase objectPhrase" << std::endl;
	}
#line 1838 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 488 "interpreter.y" /* yacc.c:1646  */
    { // SVCO e.g. she makes good pie.
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
#line 1848 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 494 "interpreter.y" /* yacc.c:1646  */
    { // SVAOV i.e. I wonder how he died. 
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase verbPhrase" << std::endl;
	}
#line 1858 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 500 "interpreter.y" /* yacc.c:1646  */
    { // e.g. sit down ( you subject is implied)
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbPhrase adverbialPhrase" << std::endl;
	}
#line 1868 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 506 "interpreter.y" /* yacc.c:1646  */
    { // ASVO e.g. now you know better.
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "adverbialPhrase subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
#line 1878 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 516 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	(yyval.sVal) = (yyvsp[0].sVal);
	//std::cout << "PRONOUN" << std::endl;
}
#line 1888 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 522 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PRONOUN NOUN" << std::endl;
	}
#line 1900 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 530 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "nounPhrase" << std::endl;
	}
#line 1909 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 535 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "nounPhrase NOUN" << std::endl;
}
#line 1920 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 542 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "nounPhrase ADJECTIVENOUN" << std::endl;
	}
#line 1931 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 549 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "nounPhrase COMMA NOUN" << std::endl;
	}
#line 1943 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 557 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "nounPhrase COMMA PRONOUN" << std::endl;
	}
#line 1955 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 565 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "nounPhrase ARTICLE" << std::endl;
	}
#line 1966 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 572 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "NOUN" << std::endl;
	}
#line 1976 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 578 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ARTICLE" << std::endl;
	}
#line 1986 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 584 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "PREPOSITION" << std::endl;
	}
#line 1996 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 592 "interpreter.y" /* yacc.c:1646  */
    {
	(yyval.sVal) = (yyvsp[0].sVal);
	//std::cout << "verbClause" << std::endl;
}
#line 2005 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 597 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "verbClause VERB" << std::endl;
}
#line 2016 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 604 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbClause NOUNVERB" << std::endl;
	}
#line 2027 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 611 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbClause CONTRACTION" << std::endl;
	}
#line 2038 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 618 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "VERB" << std::endl;
	}
#line 2048 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 624 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "CONTRACTION" << std::endl;
	}
#line 2058 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 630 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "NOUNVERB" << std::endl;
	}
#line 2068 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 636 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVENOUNVERB" << std::endl;
	}
#line 2078 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 645 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << " ARTICLE NOUN" << std::endl;
}
#line 2090 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 653 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-2].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "ARTICLE ADJECTIVENOUN NOUNVERB" << std::endl;
	}
#line 2103 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 662 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-2].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "ARTICLE ADJECTIVE NOUNVERB" << std::endl;
	}
#line 2116 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 671 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "ARTICLE NOUNVERB" << std::endl; 
	}
#line 2128 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 679 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "ARTICLE ADVERBNOUN" << std::endl;
	}
#line 2140 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 687 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION NOUN" << std::endl;
	}
#line 2152 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 695 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION ARTICLE" << std::endl;
	}
#line 2164 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 703 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION PRONOUN" << std::endl;
	}
#line 2176 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 711 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION NOUNVERB" << std::endl;
	}
#line 2188 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 719 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "objectNounClause" << std::endl;
	}
#line 2197 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 724 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "objectNounClause NOUN" << std::endl;
}
#line 2208 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 731 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "PRONOUN" << std::endl;
	}
#line 2218 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 737 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "ARTICLE ADJECTIVENOUNVERB" << std::endl;
	}
#line 2230 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 746 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "ADVERB ADJECTIVE" << std::endl; // e.g. so cute
	}
#line 2242 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 754 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVEVERB" << std::endl;
	}
#line 2252 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 760 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "adjectivePhrase" << std::endl;
	}
#line 2261 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 765 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "adjectivePhrase ADJECTIVE" << std::endl;
}
#line 2272 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 772 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "adjectivePhrase ADJECTIVENOUN" << std::endl;
	}
#line 2283 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 779 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "adjectivePhrase ADJECTIVENOUNVERB" << std::endl;
	}
#line 2294 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 786 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVE" << std::endl;
	}
#line 2304 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 792 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVENOUN" << std::endl;
	}
#line 2314 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 798 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVENOUNVERB" << std::endl;
	}
#line 2324 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 807 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	(yyval.sVal) = (yyvsp[0].sVal);
	//std::cout << "ADVERB" << std::endl;
}
#line 2334 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 813 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADVERBNOUN" << std::endl;
	}
#line 2344 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 819 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION ADJECTIVE" << std::endl;
	}
#line 2356 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 827 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION ADVERBNOUN" << std::endl;
	}
#line 2368 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 835 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "adverbPhrase" << std::endl;
	}
#line 2377 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 840 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "ADVERB ADJECTIVENOUN" << std::endl;
}
#line 2389 "interpreter.tab.c" /* yacc.c:1646  */
    break;


#line 2393 "interpreter.tab.c" /* yacc.c:1646  */
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
#line 852 "interpreter.y" /* yacc.c:1906  */


int main(int argc, char **argv) {

	std::cout << "Welcome to \"The Simpsons\" Small Talk Generator :)" << std::endl;
	std::cout << "Created by: Addison Boyer" << std::endl;

	int numLines;
	int numCharacters;

	if(argc == 4){
		numLines = std::stoi(argv[2]);
		numCharacters = std::stoi(argv[3]);
	}

	extern FILE *yyin;
	FILE *f;
	f = fopen(argv[1], "r");
	if(argc == 4 && f)
		yyin = f;
	
	yyparse();

	generateSmallTalk(counts, numLines, numCharacters);



}

/* Display error messages */
void yyerror(const char *s) {
	printf("ERROR: %s\n", s);}
