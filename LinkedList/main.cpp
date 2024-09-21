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


	//reviewsList.readCSV(reviewsList, "testing.CSV");
	positiveWordList.readWord("positive-words.txt");
	negativeWordList.readWord("negative-words.txt");
	reviewsList.readCSV("testing.CSV", positiveWordList, negativeWordList);
	reviewsList.print(5);
	reviewsList.updateFrequency(positiveWordList, negativeWordList);


	//reviewsList.sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(8));

	//positiveWordList.radixSortWordsAscending();
	//positiveWordList.reverseList();
	//positiveWordList.printWordsAndFrequency();

	//reviewsList.comparison(positiveWordList, negativeWordList, reviewsList.selectReview(2));

	//reviewsList.print(3);

	//WordList merged = mergeWordList(positiveWordList, negativeWordList);
	//merged.printWordsAndFrequency();
	//merged.radixSortWordsAscending();
	//merged.printWordsAndFrequency();

	summary(reviewsList, positiveWordList, negativeWordList);

	reviewsList.searchRelevant("nice");
	return 0;
}