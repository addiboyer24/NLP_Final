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
	int i = 0;

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

		i += 1;
		// don't want infinite loop
		if(i >= 100000)
			break;
		

		//std::cout << "HERE" << std::endl;
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
	$1 = empty;
			 } quote

	 | /* NULL */
	 ;

sentence: CHARACTER simple{
	
	// Get character, and line they spoke..
	std::string character($1);
	std::string phrase($2);

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
	|
	CHARACTER compound{
		
		// Get character, and line they spoke..
		std::string character($1);
		std::string phrase($2);

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
	|
	CHARACTER{
		
	}
	|
	CAST{
		
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
