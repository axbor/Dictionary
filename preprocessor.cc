#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	

	ifstream inFile;
	ofstream outFile;
	
	inFile.open("/usr/share/dict/words");
	if(inFile.fail()){
		cout<<"Failed to open input file" <<  endl;
	}
	
	outFile.open("words.txt");
	if(outFile.fail()){
		cout<<"Failed to open output file"<<endl;
	}
	
	
	while(inFile.good()){ // while there are lines
		string inWord;
		int nbrOfChar;
		
		getline(inFile, inWord);   //maybe use '>>' operator here instead?
		nbrOfChar = inWord.length();
		
		outFile << inWord << ' ' ; // write the word to the outfile, the number of trigrams will be added later
		transform(inWord.begin(), inWord.end() , inWord.begin(), ::tolower); // make everything lower case
		
		
		if(nbrOfChar >= 3){ 
			outFile << (nbrOfChar-2);  //if the word is long enough to contain trigrams, the nbr of trigrams are n-2
			vector<string> trigrams;
			for(int i = 0 ; i < nbrOfChar-2 ; ++i){ // substract all trigrams and att them to a vector
				string trigram;
				trigram = inWord.substr(i, 3);
				trigrams.push_back( trigram );
			}
			 
			sort(trigrams.begin(), trigrams.end()); // sort the trigrams 
		
			
			for( std::vector<string>:: iterator  k = trigrams.begin(); k != trigrams.end(); ++k ){  
				outFile << ' ' << *k	;//writing the trigrams to output file
			}
		}else {
			//outFile << 1 << ' ' << inWord; //if the word length was shorter than three, there are 0 trigrams in the word
			outFile << 0 ;
		}
		
		outFile << endl; 
	} 
		
	inFile.close();
	outFile.close();
	
	
	
	
	
	
	
	
	
	
	
}
