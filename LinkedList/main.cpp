#include <iostream>
#include "LinkedList.hpp"

#include <ctime>
#include<chrono>
#include<iostream>

using namespace std;
using namespace std::chrono;
int main() {
	//declare reviews, positive words, and negative words
	LinkedList reviewsList, positiveWordList, negativeWordList, wordList;

	reviewsList.readCSV(reviewsList, "testing.CSV");
	//reviewsList.readCSV(reviewsList, "testing.CSV");
	positiveWordList.readWords(positiveWordList, "positive-words.txt");
	negativeWordList.readWords(negativeWordList, "negative-words.txt");

	wordList.storeFreq(positiveWordList, negativeWordList, reviewsList, wordList);
	auto start = high_resolution_clock::now();
	wordList.quickSortWordsAscending();
	auto end = high_resolution_clock::now();
	////wordList.reverseList();
	wordList.print(wordList.countTotal(), 2);

	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << elapsed << " microseconds.";
	//reviewsList.print(5, false);

	//positiveWordList.print(20, true);


	//cout << "total reviews: " << reviewsList.countTotal() << endl;
	//cout << "total counts of positive words: " << positiveWordList.countTotal() << endl;
	//cout << "total counts of negative words: " << negativeWordList.countTotal() << endl;

	//cout << "Review: " << reviewsList.selectReview(0) ;
	//cout << "Rating: " << reviewsList.selectRating(0);


	//sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(0));
	return 0;
}