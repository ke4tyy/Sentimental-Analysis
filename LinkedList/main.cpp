#include <iostream>
#include "LinkedList.hpp"

#include <ctime>
#include<chrono>
#include<iostream>

using namespace std;
using namespace std::chrono;
int main() {
	//declare reviews, positive words, and negative words
	ReviewList reviewsList;
	WordList positiveWordList, negativeWordList;


	cout << endl << "adding positive words";
	positiveWordList.readWord("positive-words.txt");
	cout << endl << "adding negative words";
	negativeWordList.readWord("negative-words.txt");
	reviewsList.readCSV("testing.CSV", positiveWordList, negativeWordList);

	//reviewsList.updateFrequency(positiveWordList, negativeWordList);





	positiveWordList.mergeSort();
	negativeWordList.mergeSort();

	positiveWordList.printWordsAndFrequency();

	reviewsList.sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(3));

	reviewsList.comparison(positiveWordList, negativeWordList, reviewsList.selectReview(8));


	summary(reviewsList, positiveWordList, negativeWordList);
	reviewsList.sentimentSummary();

	return 0;
}