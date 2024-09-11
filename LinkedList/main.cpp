#include <iostream>
#include "LinkedList.hpp"

using namespace std;

int main() {
	//declare reviews, positive words, and negative words
	LinkedList reviewsList, positiveWordList, negativeWordList;

	readCSV(reviewsList, "tripadvisor_hotel_reviews.CSV");
	readWords(positiveWordList, "positive-words.txt");
	readWords(negativeWordList, "negative-words.txt");

	reviewsList.print(5, false);

	positiveWordList.print(20, true);



	//cout << "total reviews: " << reviewsList.countTotal() << endl;
	//cout << "total counts of positive words: " << positiveWordList.countTotal() << endl;
	//cout << "total counts of negative words: " << negativeWordList.countTotal() << endl;

	//cout << "Review: " << reviewsList.selectReview(0) ;
	//cout << "Rating: " << reviewsList.selectRating(0);


	//sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(0));
	return 0;
}