#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"
#include <unordered_set>

Dictionary::Dictionary() {
	
	ifstream wordReader;
	
	wordReader.open("words.txt");
	if(wordReader.fail()){
		cout<<"Input file could not be opened" << endl;
	}
	string word;
	int nbrTri;

	while(wordReader >> word >> nbrTri){
		
		vector<string> trigrams;
		
		for( int i = 0 ; i < nbrTri ; ++i){
			string trigram;
			wordReader >> trigram;
			trigrams.push_back(trigram);
			
			
		}
		Word newWord(word, trigrams);
		trigrams.clear();
		dict.insert(word);
		words[word.length()].push_back(newWord);
		}
	
	cout << " done parsing words.txt, added " << dict.size() << endl;
	
	
}

bool Dictionary::contains(const string& word) const {
	
	return (dict.find(word) != dict.end());
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	add_trigram_suggestions(suggestions, word);
	return suggestions;
}


void Dictionary::add_trigram_suggestions(vector<string>& suggestions, const string& word) const{
	
	int start;
	int end;
	int wordLength = word.length();
	unsigned int neededMatches = (wordLength - 2) / 2;

	vector<string> trigrams;
	
	if(wordLength < 3){
		return;
	}
	
	for(int i = 0 ; i < wordLength-2 ; ++i){ // substract all trigrams and att them to a vector
		string trigram;
		trigram = word.substr(i, 3);
		trigrams.push_back( trigram );
	}

	/*
	if(word.length() == 1){
		start = 0;
		end = 1;
		neededMatches = 1;
	} else */
	if( wordLength == letters){
		start = 23;
		end = 24;
	} else {
		start = wordLength - 1 ;
		end = wordLength + 1 ;
	}
	
	for(int i = start ; i <= end ; ++i){
		for(vector<Word>:: const_iterator it = words[i].begin() ; it != words[i].end() ; ++it){
			if(( *it).get_matches(trigrams) >= neededMatches ){
				suggestions.push_back((*it).get_word());
				
			}
		}
	}
	
	
	
		
	
}

