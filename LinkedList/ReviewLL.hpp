#pragma once

#ifndef REVIEWLL_HPP
#define REVIEWLL_HPP

#include "WordLL.hpp"
using namespace std;

struct ReviewNode {
	string review, goodWords, badWords;
	int rating, good, bad;
	double sentiment;
	ReviewNode* next = nullptr;
	ReviewNode(string review, int rating, int goodCount, int badCount, double sentiment, string goodWords, string badWords);
};

class ReviewList {
public:
	ReviewNode* head;
	ReviewNode* tail;
	ReviewList(); //constructor
	void addReview(string review, int rating, int goodCount, int badCount, double sentiment, string good, string bad); //add review into the linked list
	void readCSV(const string& path, WordList& good, WordList& bad); //read CSV file
	double calculateSentiment(int goodCount, int badCount); //calculate the sentiment score
	
	//ADDITIONAL FUNCTIONS
	void print(int amount); //prints the number of reviews out based on the amount given
	int countTotal(); //counts the total of elements in the list
	ReviewNode* selectReview(int index); //select specific review
	void searchRelevant(string searchWord); //search for relevant reviews
	~ReviewList(); //destructor
};


#endif