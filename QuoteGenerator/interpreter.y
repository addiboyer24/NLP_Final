/***
 Purpose: Assign expression values to variables.
 Expressions can either be addition, subtraction,
 multiplication, or division between integers or
 previously assigned variables. The expressions
 should be in a hierarchy that interprets the 
 order of operations correctly. Be able to return
 the stored value of an assigned variable by calling
 the name as a single line command.
**/

%{
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

%}

/*** union of all possible data return types from grammar ***/
%union {

	int iVal;
	char* sVal;
	
}

/*** Define token identifiers for flex regex matches ***/

%token EOL;
%token PUNCTUATION;
%token COMMA;

%token ADJECTIVE;
%token ADJECTIVENOUN;
%token ADJECTIVEVERB;
%token ADVERB;
%token NOUN;
%token PRONOUN;
%token CONTRACTION;
%token NOUNVERB;
%token VERB;
%token PREPOSITION;
%token ARTICLE;
%token CONJUNCTION;
%token ADVERBNOUN;


/*** Define return type for grammar rules ***/

%type<sVal> sentence;
//%type<sVal> word;
%type<sVal> sentencePart;
//%type<sVal> wordCommaSequence;
%type<sVal> subjectPhrase;
%type<sVal> verbPhrase;
%type<sVal> objectPhrase;
%type<sVal> adverbialPhrase;
%type<sVal> complementPhrase;
%type<sVal> adjectivePhrase;
%type<sVal> nounPhrase;
%type<sVal> simple;
%type<sVal> compound;

%type<sVal> PUNCTUATION;
%type<sVal> COMMA;
%type<sVal> ADJECTIVE;
%type<sVal> ADJECTIVENOUN;
%type<sVal> ADJECTIVEVERB;
%type<sVal> ADVERB;
%type<sVal> NOUN;
%type<sVal> PRONOUN;
%type<sVal> CONTRACTION;
%type<sVal> VERB;
%type<sVal> NOUNVERB;
%type<sVal> PREPOSITION;
%type<sVal> ARTICLE;
%type<sVal> CONJUNCTION;
%type<sVal> ADVERBNOUN;

%%


quote: sentence EOL {
	std::cout << "sentence EOL quote" << std::endl;
			 } quote

	 | /* NULL */
	 ;

sentence: simple{
	std::cout << "simple" << std::endl;
}
	|
	compound{
		std::cout << "compound" << std::endl;
	}

// Simple, Compound, Complex, Compound / Complex
simple: sentencePart PUNCTUATION{
	std::cout << "sentencePart PUNCTUATION" << std::endl;
}

compound: sentencePart COMMA CONJUNCTION simple{ // e.g. she loves cheese, but i love pie
	std::cout << "sentencePart COMMA CONJUNCTION simple" << std::endl;
}
	|
	sentencePart CONJUNCTION COMMA simple{ // e.g. 
		std::cout << "sentencePart CONJUNCTION COMMA simple" << std::endl;
	}

// S: Subject, V: Verb, O: Object, A: Adverb, C: Complement
sentencePart: subjectPhrase verbPhrase objectPhrase{ // SVO, e.g. I love cheese
	std::cout << "subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase{ // SV e.g. john conspired
		std::cout << "subjectPhrase verbPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase adverbialPhrase{ // SVA e.g. john conspired shamefully
		std::cout << "subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase objectPhrase{ // SVOO e.g. John gave Jane a present, john made a cup of tea
		std::cout << "subjectPhrase verbPhrase objectPhrase objectPhrase" << std::endl;
	}
	|
	verbPhrase objectPhrase{ // VO, e.g. call him
		std::cout << "verbPhrase objectPhrase" << std::endl;
	}
	|
	adverbialPhrase subjectPhrase verbPhrase adverbialPhrase{ // ASVA e.g. soon we wake up
		std::cout << "adverbialPhrase subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase complementPhrase{ // SVC, e.g. her mom is so nice
		std::cout << "subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase complementPhrase adverbialPhrase{ // SVCA, e.g. her mom is so nice lately
		std::cout << "subjectPhrase verbPhrase complementPhrase adverbialPhrase" << std::endl;
	}
	|
	adverbialPhrase subjectPhrase verbPhrase objectPhrase{ // ASVO e.g. lately i love cheese
		std::cout << "adverbialPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase complementPhrase{ // SVOC e.g. John made jane angry
		std::cout << "subjectPhrase verbPhrase objectPhrase complementPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase adverbialPhrase objectPhrase{ // SVAO e.g. She went up the stairs
		std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase" << std::endl;
	}
	/*
	|
	subjectPhrase verbPhrase objectPhrase complementPhrase subjectPhrase{ // SVOCA e.g. she made her opinion known at the beginning
		std::cout << "subjectPhrase verbPhrase objectPhrase complementPhrase adverbialPhrase" << std::endl;
	}
	
	|
	adverbialPhrase adverbialPhrase subjectPhrase verbPhrase complementPhrase{ // AASVC, i.e. 
		std::cout << "adverbialPhrase adverbialPhrase subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
	
	|
	subjectPhrase verbPhrase complementPhrase adverbialPhrase{ // SVCA e.g. the girl gets drunk fast
		std::cout << "subjectPhrase verbPhrase complementPhrase adverbialPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase adverbialPhrase{ // SVOA e.g. john advertises a job well
		std::cout << "subjectPhrase verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
	*/

// S: Subject
subjectPhrase: PRONOUN{
	std::cout << "PRONOUN" << std::endl;
}
	|
	PRONOUN NOUN{
		std::cout << "PRONOUN NOUN" << std::endl;
	}
	|
	nounPhrase{
		std::cout << "nounPhrase" << std::endl;
	}

nounPhrase: nounPhrase NOUN{
	std::cout << "nounPhrase NOUN" << std::endl;
}
	|
	nounPhrase ADJECTIVENOUN{
		std::cout << "nounPhrase ADJECTIVENOUN" << std::endl;
	}
	|
	nounPhrase COMMA NOUN{
		std::cout << "nounPhrase COMMA NOUN" << std::endl;
	}
	|
	nounPhrase ARTICLE{
		std::cout << "nounPhrase ARTICLE" << std::endl;
	}
	|
	NOUN{
		std::cout << "NOUN" << std::endl;
	}
	|
	ARTICLE{
		std::cout << "ARTICLE" << std::endl;
	}
	|
	PREPOSITION{
		std::cout << "PREPOSITION" << std::endl;
	}

// V: Verb
verbPhrase: VERB{
	std::cout << "VERB" << std::endl;
}
	/*|
	VERB ARTICLE{
		std::cout << "VERB ARTICLE" << std::endl;
	}*/
	|
	NOUNVERB{
		std::cout << "NOUNVERB" << std::endl;
	}
	|
	ADJECTIVEVERB{
		std::cout << "ADJECTIVEVERB" << std::endl;
	}
	|
	CONTRACTION{
		std::cout << "CONTRACTION" << std::endl;
	}
	
// O: Object
objectPhrase: ARTICLE NOUN{
	std::cout << "NOUN" << std::endl;
}
	|
	ARTICLE ADJECTIVENOUN{
		std::cout << "ARTICLE ADJECTIVENOUN" << std::endl;
	}
	|
	ARTICLE NOUNVERB{
		std::cout << "ARTICLE NOUNVERB" << std::endl; 
	}
	|
	PRONOUN{
		std::cout << "PRONOUN" << std::endl;
	}
	/*|
	PRONOUN NOUN{
		std::cout << "PRONOUN NOUN" << std::endl;
	}*/
	|
	NOUNVERB{
		std::cout << "NOUNVERB" << std::endl;
	}
	|
	NOUN{
		std::cout << "NOUN" << std::endl;
	}
	|
	PREPOSITION NOUN{
		std::cout << "PREPOSITION NOUN" << std::endl;
	}
	|
	PREPOSITION ARTICLE{
		std::cout << "PREPOSITION ARTICLE" << std::endl;
	}
	|
	PREPOSITION PRONOUN{
		std::cout << "PREPOSITION PRONOUN" << std::endl;
	}
	|
	PREPOSITION NOUNVERB{
		std::cout << "PREPOSITION NOUNVERB" << std::endl;
	}
	/*|
	nounPhrase{
		std::cout << "nounPhrase" << std::endl;
	}*/

// C: Complement
complementPhrase: ADJECTIVENOUN{
		std::cout << "ADJECTIVENOUN" << std::endl;
	}
	|
	ADVERB ADJECTIVE{
		std::cout << "ADVERB ADJECTIVE" << std::endl; // e.g. so cute
	}
	|
	ADVERB ADJECTIVENOUN{
		std::cout << "ADVERB ADJECTIVENOUN" << std::endl; // e.g. so nice
	}
	|
	ADJECTIVEVERB{
		std::cout << "ADJECTIVEVERB" << std::endl;
	}
	|
	adjectivePhrase{
		std::cout << "adjectivePhrase" << std::endl;
	}

adjectivePhrase: adjectivePhrase ADJECTIVE{
	std::cout << "adjectivePhrase ADJECTIVE" << std::endl;
}
	|
	adjectivePhrase ADJECTIVENOUN{
		std::cout << "adjectivePhrase ADJECTIVENOUN" << std::endl;
	}
	|
	ADJECTIVE{
		std::cout << "ADJECTIVE" << std::endl;
	}
	

// A: Adjunct / Adverbial
adverbialPhrase: ADVERB{
	std::cout << "ADVERB" << std::endl;
}
	|
	ADVERBNOUN{
		std::cout << "ADVERBNOUN" << std::endl;
	}
	/*|
	
	ADVERB ADJECTIVENOUN{
		std::cout << "ADVERB ADJECTIVENOUN" << std::endl;
	}*/
	/*|
	adverbPhrase{
		std::cout << "adverbPhrase" << std::endl;
	}*/




		
%%

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
