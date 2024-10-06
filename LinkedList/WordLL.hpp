#pragma once

#ifndef WORDLL_HPP
#define WORDLL_HPP

#include <string>
using namespace std;

//INSERT METHOD: used to compare between 
//insert from front: insert at head
//insert from end: loop through the end of list and insert
//insert from end using tail: add from tail
enum class insertMethod {
	fromFront, fromEnd, fromEndUsingTail
};

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
	WordNode* tail;
	WordList(); //constructor

	void addWord(string word, insertMethod method); //using the insertMethodto compare the time
	void addFrequency(string word); //adds frequency into the word's list when detected
	bool searchWord(string word); //searches the word, if it exists, returns true
	void readWord(string path, insertMethod method); //reads the .txt file
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