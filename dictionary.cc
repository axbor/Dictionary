#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"
#include <unordered_set>

using namespace std;


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
		if(word.length() > 25){
			continue;
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
	rank_suggestions(suggestions, word);
	trim_suggestions(suggestions);
	
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

void Dictionary::rank_suggestions(vector<string>& words, const string& word) const{

	if(words.size() == 0){
		return;
	}
	unsigned int editDist;
	unsigned int d[26][26];
	size_t wordLength = word.length();
	vector< pair<int, string> > calculatedWords;
	
	for(vector<string>:: const_iterator compWord = words.begin() ; compWord != words.end() ; ++compWord ){
		string compW = *compWord;
		size_t compWordLength = compW.length();

		
		for( size_t i = 0 ; i < wordLength ; ++i){
			d[i][0] = i;
		}
		for( size_t j = 0 ; j < compWordLength ; ++j){
			d[0][j] = j;
		}
		
		for( size_t i = 1 ; i < wordLength ; ++i){
			for( size_t j = 1 ; j < compWordLength ; ++j){
				
				size_t a = d[i-1][j] +1 ;
				size_t b = d[i-1][j-1] + (word[i-1] == compW[j-1] ? 0 : 1 );
				size_t c = d[i][j-1] +1 ;
				
				d[i][j] = min(a,min(b,c));
			}
		}
		
		editDist = d[wordLength][compWordLength];
		
		calculatedWords.push_back(make_pair(editDist, compW));
		
	}
	
	sort(calculatedWords.begin(), calculatedWords.end());
	words.clear();
	for(auto it = calculatedWords.begin(); it != calculatedWords.end(); ++it){
		words.push_back((*it).second);
	}
	
}




void Dictionary::trim_suggestions(vector<string>& words) const{

	if(words.size() > 5){
		words.erase(words.begin()+5, words.end());
	} 
}
	
	
