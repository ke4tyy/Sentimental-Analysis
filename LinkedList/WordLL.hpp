#pragma once

#ifndef WORDLL_HPP
#define WORDLL_HPP

#include <string>
using namespace std;

struct WordNode {
	string word;
	int frequency = 0;
	WordNode* next = nullptr;

	WordNode(string word);
	WordNode();
};

class WordList {
public:
	WordNode* head;
	WordList(); //constructor
	void addWordFromFront(string word); //adds from the front
	void addWordFromEnd(string word); //adds from the back
	void addFrequency(string word); //adds frequency into the word's list when detected
	bool searchWord(string word); //searches the word, if it exists, returns true
	void readWord(string path); //reads the .txt file

	WordNode* findMiddle(WordNode* node); //finds the middle of the list

	void printWordsAndFrequency(); //prints words and their frequency

	void binarySearch(string searchWord); //binary search on the word list
	void linearSearch(string searchWord); //linear search on the word list

	~WordList(); //destructor
};

namespace trimming {
	string trim(string word);
}


#endif