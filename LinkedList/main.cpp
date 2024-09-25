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
	reviewsList.readCSV("tripadvisor_hotel_reviews.CSV", positiveWordList, negativeWordList);

	//explanation
	//SELECTION SORT
	positiveWordList.selectionSort();
	negativeWordList.selectionSort();
	positiveWordList.selectionSortAlphabetically();
	negativeWordList.selectionSortAlphabetically();

	//BUBBLE SORT
	positiveWordList.bubbleSort();
	negativeWordList.bubbleSort();
	positiveWordList.bubbleSortAlphabetically();
	negativeWordList.bubbleSortAlphabetically();

	//RADIX SORT
	positiveWordList.radixSort();
	negativeWordList.radixSort();
	positiveWordList.radixSortAlphabetically();
	negativeWordList.radixSortAlphabetically();

	//MERGE SORT
	positiveWordList.mergeSort();
	negativeWordList.mergeSort();
	positiveWordList.mergeSortAlphabetically();
	negativeWordList.mergeSortAlphabetically();


	//searching for positive words 
	//start range of the word list
	positiveWordList.linearSearch("amazing");
	positiveWordList.binarySearch("amazing");

	//middle range of word list
	positiveWordList.linearSearch("great");
	positiveWordList.binarySearch("great");

	//end range of word list
	positiveWordList.linearSearch("wonderful");
	positiveWordList.binarySearch("wonderful");

	//searching for negative words
	//start range of the word list
	negativeWordList.linearSearch("absurd");
	negativeWordList.binarySearch("absurd");

	//middle range of word list
	negativeWordList.linearSearch("intimidate");
	negativeWordList.binarySearch("intimidate");

	//end range of word list
	negativeWordList.linearSearch("worse");
	negativeWordList.binarySearch("worse");


	positiveWordList.printWordsAndFrequency();


	reviewsList.sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(3));

	reviewsList.comparison(positiveWordList, negativeWordList, reviewsList.selectReview(8));


	reviewsList.summary(positiveWordList, negativeWordList);
	reviewsList.sentimentSummary();

	reviewsList.summary(positiveWordList, negativeWordList);
	reviewsList.print(10);

	return 0;
}