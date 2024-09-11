#include <iostream>
#include "LinkedList.hpp"

using namespace std;

int main() {
	//declare reviews, positive words, and negative words
	LinkedList reviewsList, positiveWordList, negativeWordList, wordList;

	reviewsList.readCSV(reviewsList, "tripadvisor_hotel_reviews.CSV");
	positiveWordList.readWords(positiveWordList, "positive-words.txt");
	negativeWordList.readWords(negativeWordList, "negative-words.txt");

	wordList.storeFreq(positiveWordList, negativeWordList, reviewsList, wordList);
	wordList.sortWords();
	wordList.print(wordList.countTotal(), 2);
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