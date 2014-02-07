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
		
		for( int i = 0 ; i < nbrTri ; ++i){
			// do something with the trigrams
		}
		
		dict.insert(word);
		
	}
	
}

bool Dictionary::contains(const string& word) const {
	return dict.find(word);
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}
