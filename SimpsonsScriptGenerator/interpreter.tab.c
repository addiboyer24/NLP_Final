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
#include <cstdlib>
#include<bits/stdc++.h>
#include <math.h>

#ifndef YYINITDEPTH

#define YYINITDEPTH 150000

#endif

extern "C" int yylex();
extern "C" int yyparse();
const char* space = " ";

void yyerror(const char *s);

std::map<std::string, int> *counts = new std::map<std::string, int>;

std::map<std::string, std::map<std::string, int>> *firstWordToCounts = new std::map<std::string, std::map<std::string, int>>;

std::map<std::string, std::map<std::string, int>> *characterToWordCounts = new std::map<std::string, std::map<std::string, int>>;

char* empty = new char[0];

// map to store word progression
std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model = new std::map<std::string, std::map<std::string, std::map<std::string, int>>>;

// stores the previous word
//std::string previousWord;

int count = 0;

// Deterministic way to get the next word in the chain..
std::string getHighestProbabilityWord(std::map<std::string, int> &secondToCount){
	int max = INT_MIN;
	std::string current;

	for(auto iter = secondToCount.begin(); iter != secondToCount.end(); iter++){
		if(iter->second > max){
			max = iter->second;
			current = iter->first;
		}
			
	}

	return current;
}

// function used to decide which characters will be in the scene
std::vector<std::string> getSceneCharacters(int numCharacters, std::map<std::string, int> *counts){

	std::vector<std::string> ret;
	// TODO!! select characters less randomly.

	// Get one completely random character "the wildcard"
	srand(time(0)); // make random every time for maximum laughs :)
	//int randCharacter = rand() % counts->size();
	int i = 0;

	std::vector<std::string> secondary;
	std::vector<std::string> primary;
	std::vector<std::string> wild;

	int secondaryCutoff = 50;
	int primaryCutoff = 100;
	int wildCutoff = 25;

	// 1/5 wildcard, 1/5 secondary, 3/5 primary.

	for(auto iter = counts->begin(); iter != counts->end(); iter++){
		if(iter->second >= secondaryCutoff && iter->second <= primaryCutoff)
			secondary.push_back(iter->first);
		
		else if(iter->second >= primaryCutoff)
			primary.push_back(iter->first);
		else{
			if(iter->second > wildCutoff)
				wild.push_back(iter->first);
		}
	}

	int numWildCards = numCharacters / 4;
	int numSecondary = numCharacters / 4;
	int numPrimary = (numCharacters / 4) * 2;

	// account for remainder into numSecondary
	numPrimary += (numCharacters - (numWildCards + numSecondary + numPrimary));

	int randomCharacter;
	std::string character;

	// Pick wildcards
	for(int i = 0; i < numWildCards; i++){
		randomCharacter = rand() % wild.size();
		character = wild[randomCharacter];
		wild[randomCharacter] = wild[wild.size()-1];
		wild.pop_back();
		ret.push_back(character);
	}

	// Pick secondary
	for(int i = 0; i < numSecondary; i++){
		randomCharacter = rand() % secondary.size();
		character = secondary[randomCharacter];
		secondary[randomCharacter] = secondary[secondary.size()-1];
		secondary.pop_back();
		ret.push_back(character);
		
	}

	// Pick primary
	for(int i = 0; i < numPrimary; i++){
		randomCharacter = rand() % primary.size();
		character = primary[randomCharacter];
		primary[randomCharacter] = primary[primary.size()-1];
		primary.pop_back();
		ret.push_back(character);
	}

	return ret;
}

// Function to print the cast of the current script
void printCast(std::vector<std::string> characters){
	std::cout << "*****     THE CAST     *****\n" << std::endl;
	for(int i = 0; i < characters.size(); i++){
		std::cout << characters[i] << std::endl;
		std::cout << std::endl;
	}
	std::cout << "****************************\n" << std::endl;
}

std::string pickWeightedStartingWord(std::map<std::string, int> *firstWordToCounts){

	int tot = 0;
	for(auto iter = firstWordToCounts->begin(); iter != firstWordToCounts->end(); iter++){
		tot += iter->second;
	}

	// Generate a random number between 1 and tot
	// Decrement from that number the counts, until rand is < 0.  Larger values have higher probability of doing this.. :)

	int random = (rand() % tot) + 1;
	std::string ret;
	for(auto iter = firstWordToCounts->begin(); iter != firstWordToCounts->end(); iter++){
		random -= iter->second;
		if(random <= 0){
			ret = iter->first;
			break;
		}
	}

	return ret;
	
}

std::string pickRandomStartingWord(std::map<std::string, int> firstWordToCounts){

	// Just get it randomly..
	std::string ret;
	int i = 0;
	int word = rand() % firstWordToCounts.size();
	
	for(auto iter = firstWordToCounts.begin(); iter != firstWordToCounts.end(); iter++){
		if(i == word)
			ret = iter->first;
		i+=1;
	}
	
	
	return ret;
}

std::string generateCharacterSentence(std::string &character, std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model, std::map<std::string, std::map<std::string, int>> *firstWordToCounts, bool isStochastic){

	std::string start;

	if(!isStochastic){
		// pick starting word randomly
		start = pickRandomStartingWord(firstWordToCounts->find(character)->second);
	}
	else{
		// pick a starting word some other way
		start = pickWeightedStartingWord(&firstWordToCounts->find(character)->second);
	}


	// get first word to second counts map for this character
	auto startToWordCounts = model->find(character)->second;
	
	std::string current = start;
	std::string ret;
	int numWords = 1;
	int minLength = 3;
	ret += current + " ";

	while(current != "."){
		
		// get second word to counts map..
		auto secondToCount = startToWordCounts.find(current)->second;

		if(!isStochastic){
			// if deterministic then get highest probability next word
			current = getHighestProbabilityWord(secondToCount);
		}
		else{
			// else, get a stochastic weighted choice for next word
			current = pickWeightedStartingWord(&secondToCount);
		}

		// append the word to generated sentence
		ret += current + " ";
		


		numWords += 1;

	}

	// return the generated phrase
	return ret;
	

}


float kullbackLeiblerDivergence(std::map<std::string, float> *p, std::map<std::string, float> *q){

	float div = 0.0;
	float pI;
	float qI;

	for(auto iter = p->begin(); iter != p->end(); iter++){
		pI = iter->second;
		qI = q->find(iter->first)->second;

		div += (pI * log(pI/qI));
	}

	return div;
}



std::map<std::string, float> normalizeMultiset(std::map<std::string, std::map<std::string, int>> *characterToWordCounts, std::string &character){
	
	auto multiset = &characterToWordCounts->find(character)->second;

	std::map<std::string, float> *ret = new std::map<std::string, float>;
	int total = 0;
	for(auto iter = multiset->begin(); iter != multiset->end(); iter++){
		total += iter->second;
		ret->insert(std::make_pair(iter->first, iter->second));
	}

	// normalize
	for(auto iter = ret->begin(); iter != ret->end(); iter++){
		iter->second /= total;
	}

	/*
	float tot = 0;
	for(auto iter = ret->begin(); iter != ret->end(); iter++){
		tot += iter->second;
	}

	std::cout << tot << std::endl;
	*/

	return *(ret);

}


void incrementNormalizeMultiset(std::map<std::string, std::map<std::string, int>> *characterToWordCounts, std::map<std::string, float> *intersectingMultiset, std::string &character){
	std::map<std::string, int> *ret = new std::map<std::string, int>;
	auto wordToCounts = characterToWordCounts->find(character)->second;

	int sum = intersectingMultiset->size();
	for(auto iter = wordToCounts.begin(); iter != wordToCounts.end(); iter++){
		intersectingMultiset->find(iter->first)->second += 1;
		sum += 1;
	}

	//std::cout << sum << std::endl;

	// normalize
	for(auto iter = intersectingMultiset->begin(); iter != intersectingMultiset->end(); iter++){
		iter->second /= sum;
	}

	float tot = 0;
	for(auto iter = intersectingMultiset->begin(); iter != intersectingMultiset->end(); iter++){
		tot += iter->second;
	}
}

std::map<std::string, float> getIntersectingMultiset(std::map<std::string, std::map<std::string, int>> *characterToWordCounts, std::string &character1, std::string &character2){

	auto wordToCounts1 = characterToWordCounts->find(character1)->second;

	auto wordToCounts2 = characterToWordCounts->find(character2)->second;

	std::map<std::string, float> *ret = new std::map<std::string, float>;
	
	
	for(auto iter = wordToCounts1.begin(); iter != wordToCounts1.end(); iter++){
		if(ret->find(iter->first) == ret->end()){
			ret->insert(std::make_pair(iter->first, 1));
		}
		
	}

	for(auto iter = wordToCounts2.begin(); iter != wordToCounts2.end(); iter++){
		if(ret->find(iter->first) == ret->end()){
			ret->insert(std::make_pair(iter->first, 1));
		}
		
	}


	//std::cout << ret->size() << std::endl;

	return *(ret);
}

float getKLDivergence(std::string &character1, std::string &character2, std::map<std::string, std::map<std::string, int>> *characterToWordCounts){

	// get normal multiset for p
	auto p = normalizeMultiset(characterToWordCounts, character1);

	// get pseudocounted multiset for q
	auto q = getIntersectingMultiset(characterToWordCounts, character1, character2);
	incrementNormalizeMultiset(characterToWordCounts, &q, character2);

	// calculate kl divergence
	float div = kullbackLeiblerDivergence(&p, &q);


	return div;

}

void printScript(std::vector<std::string> *lines, std::set<std::string> *characters){

	std::cout << "*****     THE CAST     *****\n" << std::endl;
	for(auto iter = characters->begin(); iter != characters->end(); iter++){
		std::cout << (*iter) << std::endl;
		std::cout << std::endl;
	}
	std::cout << "****************************\n" << std::endl;


	for(int i = 0; i < lines->size(); i++){
		std::cout << lines->at(i) << std::endl;
		std::cout << std::endl;
	}
}

std::string getMostSimilarCharacter(std::string &characterToCheck, std::vector<std::string> *characters, std::map<std::string, std::map<std::string, int>> *characterToWordCounts){
	float min = INT_MAX;
	std::string best;
	float div;
	for(int i = 0; i < characters->size(); i++){

		// not the same character as it will be close to 0 KL divergence
		if(characterToCheck != characters->at(i)){
			div = getKLDivergence(characterToCheck, characters->at(i), characterToWordCounts);
		
			if(div < min){
				min = div;
				best = characters->at(i);
			}
		}
		
	}

	
	return best;
}

// function used to generate small talk script once model is trained..
void generateSmallTalk(std::map<std::string, int> *counts, int numLines, int numCharacters, std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model, std::map<std::string, std::map<std::string, int>> *firstWordToCounts, std::map<std::string, std::map<std::string, int>> *characterToWordCounts, bool isStochastic){


	// get the characters for the scene, and display them..
	std::vector<std::string> characters = getSceneCharacters(numCharacters, counts);

	// make them small talk..
	int i = 0;
	int randCharacter;
	std::string next;

	// Start with random character..
	int randomCharacter = rand() % characters.size();
	next = characters[randomCharacter];
	
	std::set<std::string> talked;
	std::vector<std::string> lines;
	std::string line;
	// Print out script line by line..
	while(i < numLines){
		
		
		// generate a sentence
		line = generateCharacterSentence(next, model, firstWordToCounts, isStochastic);

		lines.push_back(next + ": " + line);
		//std::cout << next << ": " << line << std::endl;
		//std::cout << std::endl;

		// every other time
		// get next character by picking the one with lowest KL divergence from prev character :)
		if(i % 2 == 0){
			next = getMostSimilarCharacter(next, &characters, firstWordToCounts);
		}
		else{
			randomCharacter = rand() % characters.size();
			next = characters[randomCharacter];
		}

		// keep track of who's talked for the cast.
		talked.insert(next);
		
		i+=1;
	}

	// Print the script just generated with the Markov chain..
	printScript(&lines, &talked);
	

	
}



// Gets the newest additions to the Markov chain
std::map<std::string, std::vector<std::string>>* getNewestAdditions(std::string &phrase, std::map<std::string, std::map<std::string, int>> *firstWordToCounts, std::string &character, std::map<std::string, std::map<std::string, int>> *characterToWordCounts){
	
	// Parse phrase for individual words..
	char *cstr = new char[phrase.length() + 1];
	strcpy(cstr, phrase.c_str());
	char* token = strtok(cstr, " ");

	std::vector<std::string> *words = new std::vector<std::string>;
	while(token != NULL){
		std::string word(token);
		words->push_back(word);
		token = strtok(NULL, " ");
	}

	// add to character to word counts
	if(characterToWordCounts->find(character) != characterToWordCounts->end()){
		for(int i = 0; i < words->size(); i++){
			if(characterToWordCounts->find(character)->second.find(words->at(i)) != characterToWordCounts->find(character)->second.end()){
				characterToWordCounts->find(character)->second.find(words->at(i))->second += 1;
			}
			else{
				characterToWordCounts->find(character)->second.insert(std::make_pair(words->at(i), 1));
			}
		}
	}
	else{
		// make new dictionary
		std::map<std::string, int> *wordToCount = new std::map<std::string, int>;
		for(int i = 0; i < words->size(); i++){
			if(wordToCount->find(words->at(i)) != wordToCount->end()){
				wordToCount->find(words->at(i))->second += 1;
			}
			else{
				wordToCount->insert(std::make_pair(words->at(i), 1));
			}
		}
		
		characterToWordCounts->insert(std::make_pair(character, *(wordToCount)));
	}

	std::map<std::string, std::vector<std::string>> *ret = new std::map<std::string, std::vector<std::string>>;

	// tally first word..
	std::string start(words->at(0));
	if(firstWordToCounts->find(character) != firstWordToCounts->end()){
		if(firstWordToCounts->find(character)->second.find(start) != firstWordToCounts->find(character)->second.end()){
			firstWordToCounts->find(character)->second.find(start)->second += 1;
		}
		else{
			firstWordToCounts->find(character)->second.insert(std::make_pair(start, 1));
		}
	}
	else{
		std::map<std::string, int> *wordToCounts = new std::map<std::string, int>;
		wordToCounts->insert(std::make_pair(start, 1));
		firstWordToCounts->insert(std::make_pair(character, *(wordToCounts)));
	}

	for(int i = 1; i < words->size(); i++){
		std::string first(words->at(i-1));
		std::string second(words->at(i));

		// check if first word is a key
		if(ret->find(first) != ret->end()){
			ret->find(first)->second.push_back(second);
		}
		else{
			std::vector<std::string> *append = new std::vector<std::string>{second};
			ret->insert(std::make_pair(first, *(append)));
		}
	}

	// return the additions map
	return ret;
}

std::string generateLineForCharacter(std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model, std::string &character){

}

void printModelAtCharacter(std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model, std::string &character, std::map<std::string, std::map<std::string, int>> *firstWordToCounts){
	
	printf("First word counts for %s\n", character.c_str());
	auto wordToCounts = firstWordToCounts->find(character)->second;
	for(auto iter1 = wordToCounts.begin(); iter1 != wordToCounts.end(); iter1++){
		std::cout << iter1->first << " " << iter1->second << std::endl;
	}
	
	
	printf("Markov model for %s\n", character.c_str());
	auto firstToSecondCount = model->find(character)->second;
	for(auto iter2 = firstToSecondCount.begin(); iter2 != firstToSecondCount.end(); iter2++){
			std::cout << iter2->first << "-> ";
			auto secondToCount = iter2->second;

			for(auto iter3 = secondToCount.begin(); iter3 != secondToCount.end(); iter3++){
				std::cout << iter3->first << ": " << iter3->second << ",\t";
			}
			std::cout << std::endl;
		}
	

}

void printModel(std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model){

	int i = 0;

	for(auto iter1 = model->begin(); iter1 != model->end(); iter1++){
		std::string character = iter1->first;
		std::cout << character << std::endl;
		auto firstToSecondCount = iter1->second;

		for(auto iter2 = firstToSecondCount.begin(); iter2 != firstToSecondCount.end(); iter2++){
			std::cout << iter2->first << "-> ";
			auto secondToCount = iter2->second;

			for(auto iter3 = secondToCount.begin(); iter3 != secondToCount.end(); iter3++){
				std::cout << iter3->first << ": " << iter3->second << ",\t";
			}
			std::cout << std::endl;
		}
		
		if(i == 5)
			break;
		i+=1;
		
	}
}
void incorporateAdditions(std::map<std::string, std::map<std::string, std::map<std::string, int>>> *model, std::map<std::string, std::vector<std::string>> *additions, std::string &character){

	// check if character is in model
	if(model->find(character) != model->end()){

		// If so for every starting word in additions check to see if that exists in model
		for(auto iter = additions->begin(); iter != additions->end(); iter++){
			std::string first(iter->first);

			if(model->find(character)->second.find(first) != model->find(character)->second.end()){
				for(int i = 0; i < iter->second.size(); i++){
					std::string second(iter->second[i]);
					if(model->find(character)->second.find(first)->second.find(second) != model->find(character)->second.find(first)->second.end()){
						model->find(character)->second.find(first)->second.find(second)->second += 1;
					}
					else{
						model->find(character)->second.find(first)->second.insert(std::make_pair(second, 1));
					}
				}
			}
			else{
				
				// create second to counts
				std::map<std::string, int> *secondToCounts = new std::map<std::string, int>;
				for(int i = 0; i < iter->second.size(); i++){
					std::string second(iter->second[i]);
					if(secondToCounts->find(second) != secondToCounts->end()){
						secondToCounts->find(second)->second += 1;
					}
					else{
						secondToCounts->insert(std::make_pair(second, 1));
					}
				}

				model->find(character)->second.insert(std::make_pair(first, *(secondToCounts)));
			}
			
		}
	}

	else{ // First time we've seen this character..
		
		// make first:second:count map!
		std::map<std::string, std::map<std::string, int>> *append = new std::map<std::string, std::map<std::string, int>>;
		for(auto iter = additions->begin(); iter != additions->end(); iter++){
			std::string first(iter->first);

			if(append->find(first) != append->end()){
				std::vector<std::string> secondWords = iter->second;
				std::map<std::string, int> secondToCount = append->find(first)->second;
				for(int i = 0; i < secondWords.size(); i++){
					std::string second(secondWords[i]);
					if(secondToCount.find(second) != secondToCount.end()){
						secondToCount.find(second)->second += 1;
					}
					else{
						secondToCount.insert(std::make_pair(second, 1));
					}
				}
			}
			else{
				std::map<std::string, int> *secondToCount = new std::map<std::string, int>;
				for(int i = 0; i < iter->second.size(); i++){
					std::string second(iter->second[i]);
					if(secondToCount->find(second) != secondToCount->end()){
						secondToCount->find(second)->second += 1;
					}
					else{
						secondToCount->insert(std::make_pair(second, 1));
					}
				}

				append->insert(std::make_pair(first, *(secondToCount)));
			}
			
		}

		// append the new piece to model.
		model->insert(std::make_pair(character, *(append)));
		
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


#line 737 "interpreter.tab.c" /* yacc.c:339  */

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
#line 684 "interpreter.y" /* yacc.c:355  */


	int iVal;
	char* sVal;
	

#line 807 "interpreter.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 824 "interpreter.tab.c" /* yacc.c:358  */

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
       0,   754,   754,   754,   760,   763,   788,   809,   813,   818,
     823,   831,   840,   846,   852,   858,   864,   870,   876,   882,
     888,   894,   900,   906,   912,   918,   924,   930,   936,   942,
     948,   954,   960,   966,   972,   978,   984,   990,  1000,  1006,
    1014,  1019,  1026,  1033,  1041,  1049,  1056,  1062,  1068,  1076,
    1081,  1088,  1095,  1102,  1108,  1114,  1120,  1129,  1137,  1146,
    1155,  1163,  1171,  1179,  1187,  1195,  1203,  1208,  1215,  1221,
    1230,  1238,  1244,  1249,  1256,  1263,  1270,  1276,  1282,  1291,
    1297,  1303,  1311,  1319,  1324
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
#line 754 "interpreter.y" /* yacc.c:1646  */
    {
	//std::cout << "sentence EOL quote" << std::endl;
	count += 1;
	(yyvsp[-1].sVal) = empty;
			 }
#line 2000 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 763 "interpreter.y" /* yacc.c:1646  */
    {
	
	// Get character, and line they spoke..
	std::string character((yyvsp[-1].sVal));
	std::string phrase((yyvsp[0].sVal));

	// get the new additions for the Markov chain..
	auto additions = getNewestAdditions(phrase, firstWordToCounts, character, characterToWordCounts);
	
	// tally the character speaking
	if(counts->find(character) != counts->end()){
		counts->find(character)->second += 1;
	}
	else{
		counts->insert(std::make_pair(character, 1));
	}

	// incorporate additions to Markov chain
	incorporateAdditions(model, additions, character);




}
#line 2029 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 788 "interpreter.y" /* yacc.c:1646  */
    {
		
		// Get character, and line they spoke..
		std::string character((yyvsp[-1].sVal));
		std::string phrase((yyvsp[0].sVal));

		// get the new additions for the Markov chain..
		auto additions = getNewestAdditions(phrase, firstWordToCounts, character, characterToWordCounts);

		// tally the character speaking
		if(counts->find(character) != counts->end()){
			counts->find(character)->second += 1;
		}
		else{
			counts->insert(std::make_pair(character, 1));
		}

		// incorporate additions to Markov chain
		incorporateAdditions(model, additions, character);
	}
#line 2054 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 809 "interpreter.y" /* yacc.c:1646  */
    {
		
	}
#line 2062 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 813 "interpreter.y" /* yacc.c:1646  */
    {
		
	}
#line 2070 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 818 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
}
#line 2079 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 823 "interpreter.y" /* yacc.c:1646  */
    { // e.g. she loves cheese, but i love pie
	strcat((yyvsp[-2].sVal), space);
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
	(yyval.sVal) = (yyvsp[-3].sVal);
	//std::cout << "sentencePart COMMA CONJUNCTION simple" << std::endl;
}
#line 2091 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 831 "interpreter.y" /* yacc.c:1646  */
    { // e.g. 
		strcat((yyvsp[-2].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "sentencePart CONJUNCTION COMMA simple" << std::endl;
	}
#line 2103 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 840 "interpreter.y" /* yacc.c:1646  */
    { // SVO, e.g. I love cheese
	strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
	(yyval.sVal) = (yyvsp[-2].sVal);
	//std::cout << "subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 2113 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 846 "interpreter.y" /* yacc.c:1646  */
    { // SV e.g. john conspired
		//std::cout << "subjectPhrase verbPhrase" << std::endl;
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
	}
#line 2123 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 852 "interpreter.y" /* yacc.c:1646  */
    { // SVA e.g. john conspired shamefully
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
#line 2133 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 858 "interpreter.y" /* yacc.c:1646  */
    { // SVOO e.g. John gave Jane a present, john made a cup of tea
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase objectPhrase" << std::endl;
	}
#line 2143 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 864 "interpreter.y" /* yacc.c:1646  */
    { // VO, e.g. call him
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbPhrase objectPhrase" << std::endl;
	}
#line 2153 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 870 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 2163 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 876 "interpreter.y" /* yacc.c:1646  */
    { // ASVA e.g. soon we wake up
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "adverbialPhrase subjectPhrase verbPhrase adverbialPhrase" << std::endl;
	}
#line 2173 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 882 "interpreter.y" /* yacc.c:1646  */
    { // SVC, e.g. her mom is so nice
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
#line 2183 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 888 "interpreter.y" /* yacc.c:1646  */
    { // SVCA, e.g. her mom is so nice lately
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase complementPhrase adverbialPhrase" << std::endl;
	}
#line 2193 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 894 "interpreter.y" /* yacc.c:1646  */
    { // ASVO e.g. lately i love cheese
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "adverbialPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
#line 2203 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 900 "interpreter.y" /* yacc.c:1646  */
    { // SVOC e.g. John made jane angry
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase complementPhrase" << std::endl;
	}
#line 2213 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 906 "interpreter.y" /* yacc.c:1646  */
    { // SVAO e.g. She went up the stairs
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase" << std::endl;
	}
#line 2223 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 912 "interpreter.y" /* yacc.c:1646  */
    { // SVOA e.g. it was a little of both
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
#line 2233 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 918 "interpreter.y" /* yacc.c:1646  */
    { // SVOVO e.g. you think you have it
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 2243 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 924 "interpreter.y" /* yacc.c:1646  */
    { // SVOVOCA e.g. I don't think there's anything left to say
		strcat((yyvsp[-6].sVal), strcat((yyvsp[-5].sVal), strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))))));
		(yyval.sVal) = (yyvsp[-6].sVal);
		//std::cout << "subjectPhrase verbPhrase objectPhrase verbPhrase objectPhrase complementPhrase adverbialPhrase" << std::endl;
	}
#line 2253 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 930 "interpreter.y" /* yacc.c:1646  */
    { // VC e.g. it's only natural
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbPhrase complementPhrase" << std::endl;
	}
#line 2263 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 936 "interpreter.y" /* yacc.c:1646  */
    { // AVSVO e.g. what did he teach you?
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "adverbialPhrase verbPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 2273 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 942 "interpreter.y" /* yacc.c:1646  */
    { // VCSVO e.g. I'd sure like to talk to him
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 2283 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 948 "interpreter.y" /* yacc.c:1646  */
    { // VCSVO e.g. Although I'd sure like to talk to him
		strcat((yyvsp[-5].sVal), strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))))));
		(yyval.sVal) = (yyvsp[-5].sVal);
		//std::cout << "adverbialPhrase verbPhrase complementPhrase subjectPhrase verbPhrase objectPhrase" << std::endl;
	}
#line 2293 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 954 "interpreter.y" /* yacc.c:1646  */
    { // VOC e.g. are you stupid?
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "verbPhrase objectPhrase complementPhrase" << std::endl;
	}
#line 2303 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 960 "interpreter.y" /* yacc.c:1646  */
    { // VOA e.g. I'll tell you what.
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "verbPhrase objectPhrase adverbialPhrase" << std::endl;
	}
#line 2313 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 966 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "verbPhrase objectPhrase objectPhrase" << std::endl;
	}
#line 2323 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 972 "interpreter.y" /* yacc.c:1646  */
    { // SVCO e.g. she makes good pie.
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "subjectPhrase verbPhrase complementPhrase objectPhrase" << std::endl;
	}
#line 2333 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 978 "interpreter.y" /* yacc.c:1646  */
    { // SVAOV i.e. I wonder how he died. 
		strcat((yyvsp[-4].sVal), strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)))));
		(yyval.sVal) = (yyvsp[-4].sVal);
		//std::cout << "subjectPhrase verbPhrase adverbialPhrase objectPhrase verbPhrase" << std::endl;
	}
#line 2343 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 984 "interpreter.y" /* yacc.c:1646  */
    { // e.g. sit down ( you subject is implied)
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbPhrase adverbialPhrase" << std::endl;
	}
#line 2353 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 990 "interpreter.y" /* yacc.c:1646  */
    { // ASVO e.g. now you know better.
		strcat((yyvsp[-3].sVal), strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal))));
		(yyval.sVal) = (yyvsp[-3].sVal);
		//std::cout << "adverbialPhrase subjectPhrase verbPhrase complementPhrase" << std::endl;
	}
#line 2363 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1000 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	(yyval.sVal) = (yyvsp[0].sVal);
	//std::cout << "PRONOUN" << std::endl;
}
#line 2373 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1006 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PRONOUN NOUN" << std::endl;
	}
#line 2385 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1014 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "nounPhrase" << std::endl;
	}
#line 2394 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1019 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "nounPhrase NOUN" << std::endl;
}
#line 2405 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1026 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "nounPhrase ADJECTIVENOUN" << std::endl;
	}
#line 2416 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1033 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "nounPhrase COMMA NOUN" << std::endl;
	}
#line 2428 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1041 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "nounPhrase COMMA PRONOUN" << std::endl;
	}
#line 2440 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1049 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "nounPhrase ARTICLE" << std::endl;
	}
#line 2451 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1056 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "NOUN" << std::endl;
	}
#line 2461 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1062 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ARTICLE" << std::endl;
	}
#line 2471 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1068 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "PREPOSITION" << std::endl;
	}
#line 2481 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1076 "interpreter.y" /* yacc.c:1646  */
    {
	(yyval.sVal) = (yyvsp[0].sVal);
	//std::cout << "verbClause" << std::endl;
}
#line 2490 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1081 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "verbClause VERB" << std::endl;
}
#line 2501 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1088 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbClause NOUNVERB" << std::endl;
	}
#line 2512 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1095 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "verbClause CONTRACTION" << std::endl;
	}
#line 2523 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1102 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "VERB" << std::endl;
	}
#line 2533 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1108 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "CONTRACTION" << std::endl;
	}
#line 2543 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1114 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "NOUNVERB" << std::endl;
	}
#line 2553 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1120 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVENOUNVERB" << std::endl;
	}
#line 2563 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1129 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << " ARTICLE NOUN" << std::endl;
}
#line 2575 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1137 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-2].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "ARTICLE ADJECTIVENOUN NOUNVERB" << std::endl;
	}
#line 2588 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1146 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-2].sVal), space);
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-2].sVal), strcat((yyvsp[-1].sVal), (yyvsp[0].sVal)));
		(yyval.sVal) = (yyvsp[-2].sVal);
		//std::cout << "ARTICLE ADJECTIVE NOUNVERB" << std::endl;
	}
#line 2601 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1155 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "ARTICLE NOUNVERB" << std::endl;
	}
#line 2613 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1163 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "ARTICLE ADVERBNOUN" << std::endl;
	}
#line 2625 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1171 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION NOUN" << std::endl;
	}
#line 2637 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1179 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION ARTICLE" << std::endl;
	}
#line 2649 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1187 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION PRONOUN" << std::endl;
	}
#line 2661 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1195 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION NOUNVERB" << std::endl;
	}
#line 2673 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1203 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "objectNounClause" << std::endl;
	}
#line 2682 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1208 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "objectNounClause NOUN" << std::endl;
}
#line 2693 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1215 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "PRONOUN" << std::endl;
	}
#line 2703 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1221 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "ARTICLE ADJECTIVENOUNVERB" << std::endl;
	}
#line 2715 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1230 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "ADVERB ADJECTIVE" << std::endl; // e.g. so cute
	}
#line 2727 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1238 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVEVERB" << std::endl;
	}
#line 2737 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1244 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "adjectivePhrase" << std::endl;
	}
#line 2746 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1249 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "adjectivePhrase ADJECTIVE" << std::endl;
}
#line 2757 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1256 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "adjectivePhrase ADJECTIVENOUN" << std::endl;
	}
#line 2768 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1263 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "adjectivePhrase ADJECTIVENOUNVERB" << std::endl;
	}
#line 2779 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1270 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVE" << std::endl;
	}
#line 2789 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1276 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVENOUN" << std::endl;
	}
#line 2799 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1282 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADJECTIVENOUNVERB" << std::endl;
	}
#line 2809 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1291 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[0].sVal), space);
	(yyval.sVal) = (yyvsp[0].sVal);
	//std::cout << "ADVERB" << std::endl;
}
#line 2819 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1297 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[0].sVal), space);
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "ADVERBNOUN" << std::endl;
	}
#line 2829 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1303 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION ADJECTIVE" << std::endl;
	}
#line 2841 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1311 "interpreter.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-1].sVal), space);
		strcat((yyvsp[0].sVal), space);
		strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
		(yyval.sVal) = (yyvsp[-1].sVal);
		//std::cout << "PREPOSITION ADVERBNOUN" << std::endl;
	}
#line 2853 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1319 "interpreter.y" /* yacc.c:1646  */
    {
		(yyval.sVal) = (yyvsp[0].sVal);
		//std::cout << "adverbPhrase" << std::endl;
	}
#line 2862 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1324 "interpreter.y" /* yacc.c:1646  */
    {
	strcat((yyvsp[-1].sVal), space);
	strcat((yyvsp[0].sVal), space);
	strcat((yyvsp[-1].sVal), (yyvsp[0].sVal));
	(yyval.sVal) = (yyvsp[-1].sVal);
	//std::cout << "ADVERB ADJECTIVENOUN" << std::endl;
}
#line 2874 "interpreter.tab.c" /* yacc.c:1646  */
    break;


#line 2878 "interpreter.tab.c" /* yacc.c:1646  */
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
#line 1336 "interpreter.y" /* yacc.c:1906  */


int main(int argc, char **argv) {

	std::cout << "\nWelcome to \"The Simpsons Small Talk\" Generator :)" << std::endl;
	std::cout << "Created by: Addison Boyer\n" << std::endl;

	int numLines;
	int numCharacters;
	bool isStochastic;

	if(argc == 5){
		numLines = std::stoi(argv[2]);
		numCharacters = std::stoi(argv[3]);
		isStochastic = (bool)std::stoi(argv[4]);
	}

	extern FILE *yyin;
	FILE *f;
	f = fopen(argv[1], "r");
	if(argc == 5 && f)
		yyin = f;
	
	yyparse();

	// Generate script with given parameters..
	if(argc == 5){
		generateSmallTalk(counts, numLines, numCharacters, model, firstWordToCounts, characterToWordCounts, isStochastic);
	}



}

/* Display error messages */
void yyerror(const char *s) {
	printf("ERROR: %s\n", s);}
