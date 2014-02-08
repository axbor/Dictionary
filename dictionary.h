#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "word.h"

using namespace std;


class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
	static const int letters = 25;
	unordered_set<string> dict;
	vector<Word> words[letters]; 
	void add_trigram_suggestions( std::vector<string>& suggestions, const std::string& word) const;

};

#endif
