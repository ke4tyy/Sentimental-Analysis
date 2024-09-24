#pragma once

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>
using namespace std;


//Explanation: Struct, grouping variables as members of a structure
struct ReviewNode {
	string review, goodWords, badWords;
	int rating, good, bad;
	double sentiment;
	ReviewNode* next = nullptr;
	ReviewNode(string review, int rating, int goodCount, int badCount, double sentiment, string goodWords, string badWords);
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
	WordList();
	void addWordFromFront(string word);
	void addWordFromEnd(string word);
	void addFrequency(string word);
	bool searchWord(string word);
	void readWord(string path);
	void selectionSort();
	void radixSort();
	void bubbleSort();
	
	WordNode* findMiddle(WordNode* node);
	WordNode* merge(WordNode* left, WordNode* right);
	WordNode* mergeSort(WordNode* node);
	void printWordsAndFrequency();
	void mergeSort();

	~WordList();
};

class ReviewList {
public: 
	ReviewNode* head;
	ReviewNode* tail;
	ReviewList();
	void addReview(string review, int rating, int goodCount, int badCount, double sentiment, string good, string bad);
	int countTotal();
	ReviewNode* selectReview(int index);

	void readCSV(string path, WordList& good, WordList& bad);
	void print(int amount);
	string trim(string str);
	double calculateSentiment(int goodCount, int badCount);
	void comparison(WordList& good, WordList& bad, ReviewNode* review);
	void sentimentAnalysis(WordList& good, WordList& bad, ReviewNode* reviews);

	void searchRelevant(string searchWord);

	void sentimentSummary();

	~ReviewList();
};


void summary(ReviewList& reviews, WordList& good, WordList& bad);



#endif