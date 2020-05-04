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
%token CHARACTER;
%token QWORD;
%token ADJECTIVENOUNVERB;
%token CAST;


/*** Define return type for grammar rules ***/

%type<sVal> sentence;
%type<sVal> sentencePart;
%type<sVal> subjectPhrase;
%type<sVal> verbPhrase;
%type<sVal> objectPhrase;
%type<sVal> adverbialPhrase;
%type<sVal> complementPhrase;
%type<sVal> adjectivePhrase;
%type<sVal> nounPhrase;
%type<sVal> simple;
%type<sVal> compound;
%type<sVal> adverbPhrase;
%type<sVal> verbClause;
%type<sVal> objectNounClause;

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
%type<sVal> ADJECTIVENOUNVERB;
%type<sVal> CHARACTER;
%type<sVal> CAST;

%%


quote: sentence EOL {
	//std::cout << "sentence EOL quote" << std::endl;
	count += 1;
			 } quote

	 | /* NULL */
	 ;

sentence: CHARACTER simple{
	//std::cout << $1 << " simple" << std::endl;
	//std::cout << $1 << $2 << std::endl;
	std::string character($1);

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
	|
	CHARACTER compound{
		//std::cout << $1 << $2 << std::endl;
		std::string character($1);

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
	|
	CHARACTER{
		//std::cout << "CHARACTER" << std::endl;
		// Generate a sentence..
		std::cout << $1 << " says something here.." << std::endl;

		for(auto iter = counts->begin(); iter != counts->end(); iter++){
			std::cout << iter->first << ": " << iter->second << std::endl;
		}

	}
	|
	CAST{
		printCast(counts);
	}

// Simple, Compound, Complex, Compound / Complex
simple: sentencePart PUNCTUATION{
	strcat($1, $2);
	$$ = $1;
}

compound: sentencePart COMMA CONJUNCTION simple{ // e.g. she loves cheese, but i love pie
	strcat($2, space);
	strcat($3, space);
	strcat($1, strcat($2, strcat($3, $4)));
	$$ = $1;
	//std::cout << "sentencePart COMMA CONJUNCTION simple" << std::endl;
}
	|
	sentencePart CONJUNCTION COMMA simple{ // e.g. 
		strcat($2, space);
		strcat($3, space);
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "sentencePart CONJUNCTION COMMA simple" << std::endl;
	}

// S: Subject, V: Verb, O: Object, A: Adverb, C: Complement
sentencePart: subjectPhrase verbPhrase objectPhrase{ // SVO, e.g. I love cheese
	strcat($1, strcat($2, $3));
	$$ = $1;
	//std::cout << "subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase{ // SV e.g. john conspired
		//std::cout << "subjectPhrase verbPhrase" << std::endl;
		strcat($1, $2);
		$$ = $1;
	}
	|
	subjectPhrase verbPhrase adverbialPhrase{ // SVA e.g. john conspired shamefully
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase objectPhrase{ // SVOO e.g. John gave Jane a present, john made a cup of tea
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase objectPhrase objectPhrase" << std::endl;
	}
	|
	verbPhrase objectPhrase{ // VO, e.g. call him
		strcat($1, $2);
		$$ = $1;
		//std::cout << "verbPhrase objectPhrase" << std::endl;
	}
	|
	verbPhrase objectPhrase verbPhrase objectPhrase{
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	adverbialPhrase subjectPhrase verbPhrase adverbialPhrase{ // ASVA e.g. soon we wake up
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "adverbialPhrase subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase complementPhrase{ // SVC, e.g. her mom is so nice
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase complementPhrase adverbialPhrase{ // SVCA, e.g. her mom is so nice lately
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase complementPhrase adverbialPhrase" << std::endl;
	}
	|
	adverbialPhrase subjectPhrase verbPhrase objectPhrase{ // ASVO e.g. lately i love cheese
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "adverbialPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase complementPhrase{ // SVOC e.g. John made jane angry
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase objectPhrase complementPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase adverbialPhrase objectPhrase{ // SVAO e.g. She went up the stairs
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase adverbialPhrase{ // SVOA e.g. it was a little of both
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase{ // SVOVO e.g. you think you have it
		strcat($1, strcat($2, strcat($3, strcat($4, $5))));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase complementPhrase adverbialPhrase{ // SVOVOCA e.g. I don't think there's anything left to say
		strcat($1, strcat($2, strcat($3, strcat($4, strcat($5, strcat($6, $7))))));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase complementPhrase adverbialPhrase" << std::endl;
	}
	|
	verbPhrase complementPhrase{ // VC e.g. it's only natural
		strcat($1, $2);
		$$ = $1;
		//std::cout << "verbPhrase complementPhrase" << std::endl;
	}
	|
	adverbialPhrase verbPhrase subjectPhrase verbPhrase objectPhrase{ // AVSVO e.g. what did he teach you?
		strcat($1, strcat($2, strcat($3, strcat($4, $5))));
		$$ = $1;
		//std::cout << "adverbialPhrase verbPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase{ // VCSVO e.g. I'd sure like to talk to him
		strcat($1, strcat($2, strcat($3, strcat($4, $5))));
		$$ = $1;
		//std::cout << "verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	adverbialPhrase verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase{ // VCSVO e.g. Although I'd sure like to talk to him
		strcat($1, strcat($2, strcat($3, strcat($4, strcat($5, $6)))));
		$$ = $1;
		//std::cout << "adverbialPhrase verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
	|
	verbPhrase objectPhrase complementPhrase{ // VOC e.g. are you stupid?
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "verbPhrase objectPhrase complementPhrase" << std::endl;
	}
	|
	verbPhrase objectPhrase adverbialPhrase{ // VOA e.g. I'll tell you what.
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
	|
	verbPhrase objectPhrase objectPhrase{
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "verbPhrase objectPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase complementPhrase objectPhrase{ // SVCO e.g. she makes good pie.
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
	|
	subjectPhrase verbPhrase adverbialPhrase objectPhrase verbPhrase{ // SVAOV i.e. I wonder how he died. 
		strcat($1, strcat($2, strcat($3, strcat($4, $5))));
		$$ = $1;
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase verbPhrase" << std::endl;
	}
	|
	verbPhrase adverbialPhrase{ // e.g. sit down ( you subject is implied)
		strcat($1, $2);
		$$ = $1;
		//std::cout << "verbPhrase adverbialPhrase" << std::endl;
	}
	|
	adverbialPhrase subjectPhrase verbPhrase complementPhrase{ // ASVO e.g. now you know better.
		strcat($1, strcat($2, strcat($3, $4)));
		$$ = $1;
		//std::cout << "adverbialPhrase subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
	
	
	

// S: Subject
subjectPhrase: PRONOUN{
	strcat($1, space);
	$$ = $1;
	//std::cout << "PRONOUN" << std::endl;
}
	|
	PRONOUN NOUN{
	strcat($1, space);
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
		//std::cout << "PRONOUN NOUN" << std::endl;
	}
	|
	nounPhrase{
		$$ = $1;
		//std::cout << "nounPhrase" << std::endl;
	}

nounPhrase: nounPhrase NOUN{
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << "nounPhrase NOUN" << std::endl;
}
	|
	nounPhrase ADJECTIVENOUN{
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "nounPhrase ADJECTIVENOUN" << std::endl;
	}
	|
	nounPhrase COMMA NOUN{
		strcat($3, space);
		strcat($2, space);
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "nounPhrase COMMA NOUN" << std::endl;
	}
	|
	nounPhrase COMMA PRONOUN{
		strcat($3, space);
		strcat($2, space);
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "nounPhrase COMMA PRONOUN" << std::endl;
	}
	|
	nounPhrase ARTICLE{
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "nounPhrase ARTICLE" << std::endl;
	}
	|
	NOUN{
		strcat($1, space);
		$$ = $1;
		//std::cout << "NOUN" << std::endl;
	}
	|
	ARTICLE{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ARTICLE" << std::endl;
	}
	|
	PREPOSITION{
		strcat($1, space);
		$$ = $1;
		//std::cout << "PREPOSITION" << std::endl;
	}
	

// V: Verb
verbPhrase: verbClause{
	$$ = $1;
	//std::cout << "verbClause" << std::endl;
}

verbClause: verbClause VERB{
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << "verbClause VERB" << std::endl;
}
	|
	verbClause NOUNVERB{
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "verbClause NOUNVERB" << std::endl;
	}
	|
	verbClause CONTRACTION{
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "verbClause CONTRACTION" << std::endl;
	}
	|
	VERB{
		strcat($1, space);
		$$ = $1;
		//std::cout << "VERB" << std::endl;
	}
	|
	CONTRACTION{
		strcat($1, space);
		$$ = $1;
		//std::cout << "CONTRACTION" << std::endl;
	}
	|
	NOUNVERB{
		strcat($1, space);
		$$ = $1;
		//std::cout << "NOUNVERB" << std::endl;
	}
	|
	ADJECTIVENOUNVERB{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ADJECTIVENOUNVERB" << std::endl;
	}

	
	
// O: Object
objectPhrase: ARTICLE NOUN{
	strcat($1, space);
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << " ARTICLE NOUN" << std::endl;
}
	|
	ARTICLE ADJECTIVENOUN NOUNVERB{
		strcat($1, space);
		strcat($2, space);
		strcat($3, space);
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "ARTICLE ADJECTIVENOUN NOUNVERB" << std::endl;
	}
	|
	ARTICLE ADJECTIVE NOUNVERB{
		strcat($1, space);
		strcat($2, space);
		strcat($3, space);
		strcat($1, strcat($2, $3));
		$$ = $1;
		//std::cout << "ARTICLE ADJECTIVE NOUNVERB" << std::endl;
	}
	|
	ARTICLE NOUNVERB{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "ARTICLE NOUNVERB" << std::endl; 
	}
	|
	ARTICLE ADVERBNOUN{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "ARTICLE ADVERBNOUN" << std::endl;
	}
	|
	PREPOSITION NOUN{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "PREPOSITION NOUN" << std::endl;
	}
	|
	PREPOSITION ARTICLE{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "PREPOSITION ARTICLE" << std::endl;
	}
	|
	PREPOSITION PRONOUN{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "PREPOSITION PRONOUN" << std::endl;
	}
	|
	PREPOSITION NOUNVERB{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "PREPOSITION NOUNVERB" << std::endl;
	}
	|
	objectNounClause{
		$$ = $1;
		//std::cout << "objectNounClause" << std::endl;
	}

objectNounClause: objectNounClause NOUN{
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << "objectNounClause NOUN" << std::endl;
}
	|
	PRONOUN{
		strcat($1, space);
		$$ = $1;
		//std::cout << "PRONOUN" << std::endl;
	}
	|
	ARTICLE ADJECTIVENOUNVERB{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "ARTICLE ADJECTIVENOUNVERB" << std::endl;
	}

// C: Complement
complementPhrase: ADVERB ADJECTIVE{
	strcat($1, space);
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << "ADVERB ADJECTIVE" << std::endl; // e.g. so cute
	}
	|
	ADJECTIVEVERB{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ADJECTIVEVERB" << std::endl;
	}
	|
	adjectivePhrase{
		$$ = $1;
		//std::cout << "adjectivePhrase" << std::endl;
	}

adjectivePhrase: adjectivePhrase ADJECTIVE{
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << "adjectivePhrase ADJECTIVE" << std::endl;
}
	|
	adjectivePhrase ADJECTIVENOUN{
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "adjectivePhrase ADJECTIVENOUN" << std::endl;
	}
	|
	adjectivePhrase ADJECTIVENOUNVERB{
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "adjectivePhrase ADJECTIVENOUNVERB" << std::endl;
	}
	|
	ADJECTIVE{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ADJECTIVE" << std::endl;
	}
	|
	ADJECTIVENOUN{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ADJECTIVENOUN" << std::endl;
	}
	|
	ADJECTIVENOUNVERB{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ADJECTIVENOUNVERB" << std::endl;
	}
	
	

// A: Adjunct / Adverbial
adverbialPhrase: ADVERB{
	strcat($1, space);
	$$ = $1;
	//std::cout << "ADVERB" << std::endl;
}
	|
	ADVERBNOUN{
		strcat($1, space);
		$$ = $1;
		//std::cout << "ADVERBNOUN" << std::endl;
	}
	|
	PREPOSITION ADJECTIVE{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "PREPOSITION ADJECTIVE" << std::endl;
	}
	|
	PREPOSITION ADVERBNOUN{
		strcat($1, space);
		strcat($2, space);
		strcat($1, $2);
		$$ = $1;
		//std::cout << "PREPOSITION ADVERBNOUN" << std::endl;
	}
	|
	adverbPhrase{
		$$ = $1;
		//std::cout << "adverbPhrase" << std::endl;
	}

adverbPhrase: ADVERB ADJECTIVENOUN{
	strcat($1, space);
	strcat($2, space);
	strcat($1, $2);
	$$ = $1;
	//std::cout << "ADVERB ADJECTIVENOUN" << std::endl;
}




		
%%

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
