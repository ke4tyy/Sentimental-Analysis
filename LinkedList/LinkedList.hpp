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
	ReviewNode* next;
	ReviewNode(string review, int rating, int goodCount, int badCount, double sentiment, string goodWords, string badWords);
};

struct WordNode {
	string word;
	int frequency;
	WordNode* next;

	WordNode(string word);
};

class WordList {
public:
	WordNode* head;
	WordNode* tail;
	WordList();
	void addWord(string word, int frequency);
	void addFrequency(string word);
	bool searchWord(string word);
	void readWord(string path);

	void selectionSortWordsAscending();
	void radixSortWordsAscending();
	void quickSortWordsAscending();
	WordNode* recursionList(WordNode* current, WordNode* previous);
	void reverseList();

	void printWordsAndFrequency();


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
	void updateFrequency(WordList& good, WordList& bads);

	void comparison(WordList& good, WordList& bad, ReviewNode* review);
	void sentimentAnalysis(WordList& good, WordList& bad, ReviewNode* reviews);

	void searchRelevant(string searchWord);


	~ReviewList();
};

WordList mergeWordList(WordList& wordlist1, WordList& wordlist2);

void summary(ReviewList& reviews, WordList& good, WordList& bad);

#endif