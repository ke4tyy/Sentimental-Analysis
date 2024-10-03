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

	//SORTING BY FREQUENCY
	void selectionSort(); //selection sort by frequency
	void radixSort(); //radix sort by frequency
	void bubbleSort(); //bubble sort by frequency

	//merge sort code
	WordNode* findMiddle(WordNode* node); //finds the middle of the list
	WordNode* merge(WordNode* left, WordNode* right);  //merge
	WordNode* mergeSort(WordNode* node);
	void mergeSort();

	//SORTING BY ALPHABET
	void selectionSortAlphabetically(); //selection sort by alphabet
	void radixSortAlphabetically(); //radix sort by alphabet
	void bubbleSortAlphabetically(); //bubble sort by alphabet

	//merge sort code
	WordNode* mergeAlphabetically(WordNode* left, WordNode* right);
	WordNode* mergeSortAlphabetically(WordNode* node);
	void mergeSortAlphabetically();

	void printWordsAndFrequency(); //prints words and their frequency

	void binarySearch(string searchWord); //binary search on the word list
	void linearSearch(string searchWord); //linear search on the word list

	~WordList(); //destructor
};


#endif