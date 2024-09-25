#pragma once

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>
using namespace std;

//singly linked list
//Explanation: Struct, grouping variables as members of a structure
//review node: goodWords and badWords stores all the good and bad words detected in the review, good and bad are the count of good words and bad words
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

class ReviewList {
public: 
	ReviewNode* head;
	ReviewNode* tail;
	ReviewList(); //constructor
	void addReview(string review, int rating, int goodCount, int badCount, double sentiment, string good, string bad); //add review into the linked list
	void readCSV(string path, WordList& good, WordList& bad); //read CSV file
	string trim(string str); //trims any special characters
	double calculateSentiment(int goodCount, int badCount); //calculate the sentiment score
	void sentimentAnalysis(WordList& good, WordList& bad, ReviewNode* reviews); //sentiment analysis on specific review
	void comparison(WordList& good, WordList& bad, ReviewNode* review); //compares sentiment and rating of specific review


	//ADDITIONAL FUNCTIONS
	void print(int amount); //prints the number of reviews out based on the amount given
	int countTotal(); //counts the total of elements in the list
	void sentimentSummary(); //summary based on sentiment score
	ReviewNode* selectReview(int index); //select specific review
	void searchRelevant(string searchWord);
	void summary(WordList& good, WordList& bad); //summary

	~ReviewList();
};





#endif