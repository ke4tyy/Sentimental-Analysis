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