#include <string>
#include <vector>
#include "word.h"


Word::Word(const string& w, const vector<string>& t): word(w), trigrams(t) {
	}

string Word::get_word() const {
	return word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	int compVal;
	int matches = 0;
	vector<string>:: const_iterator thisWord = trigrams.begin();
	vector<string>:: const_iterator otherWord = t.begin();


	while( thisWord != trigrams.end() && otherWord != t.end() ){
		
		compVal = (*thisWord).compare(*otherWord);
		
		if(compVal == 0){
			++matches;
			++otherWord;
			++thisWord;	
		} else if( compVal > 0){
			++otherWord;
		} else{
			++thisWord;
		}
	}
	
	return matches;
}
