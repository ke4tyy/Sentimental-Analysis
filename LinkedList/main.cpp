#include <iostream>
#include "LinkedList.hpp"

using namespace std;

int main() {
	//declare reviews, positive words, and negative words
	LinkedList reviewsList, positiveWordList, negativeWordList;

	readCSV(reviewsList, "tripadvisor_hotel_reviews.CSV");
	readWords(positiveWordList, "positive-words.txt");
	readWords(negativeWordList, "negative-words.txt");

	//positiveWordList.printWords(10);


	//cout << "total reviews: " << reviewsList.countTotal() << endl;
	//cout << "total counts of positive words: " << positiveWordList.countTotal() << endl;
	//cout << "total counts of negative words: " << negativeWordList.countTotal() << endl;

	//cout << "Review: " << reviewsList.selectReview(0) ;
	//cout << "Rating: " << reviewsList.selectRating(0);


	sentimentAnalysis(reviewsList, positiveWordList, negativeWordList, reviewsList.selectReview(90));
	return 0;
}