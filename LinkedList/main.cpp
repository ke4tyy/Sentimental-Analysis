#include "ReviewLL.hpp"
#include "Sorting.hpp"

#include <iostream>

using namespace std;
int main() {
	//declare reviews, positive words, and negative words
	ReviewList reviewsList;
	WordList positiveWordList, negativeWordList;


	cout << endl << "adding positive words";
	positiveWordList.readWord("positive-words.txt");
	cout << endl << "adding negative words";
	negativeWordList.readWord("negative-words.txt");
	reviewsList.readCSV("tripadvisor_hotel_reviews.CSV", positiveWordList, negativeWordList);


	Sorting::radixSort(positiveWordList);
	Sorting::radixSort(negativeWordList);
	Sorting::radixSortAlphabetically(positiveWordList);
	Sorting::radixSortAlphabetically(negativeWordList);

	Sorting::selectionSort(positiveWordList);
	Sorting::selectionSort(negativeWordList);
	Sorting::selectionSortAlphabetically(positiveWordList);
	Sorting::selectionSortAlphabetically(negativeWordList);

	Sorting::bubbleSort(positiveWordList);
	Sorting::bubbleSort(negativeWordList);
	Sorting::bubbleSortAlphabetically(positiveWordList);
	Sorting::bubbleSortAlphabetically(negativeWordList);

	Sorting::mergeSort(positiveWordList);
	Sorting::mergeSort(negativeWordList);
	Sorting::mergeSortAlphabetically(positiveWordList);
	Sorting::mergeSortAlphabetically(negativeWordList);

	Sorting::radixSort(positiveWordList);
	Sorting::radixSort(negativeWordList);
	cout << "Positive Word List: " << endl << string(70, '-') << endl;
	positiveWordList.printWordsAndFrequency();
	cout << string(70, '-') << endl;
	cout << "Negative Word List: " << endl << string(70, '-') << endl;
	negativeWordList.printWordsAndFrequency();

	reviewsList.comparison(reviewsList.selectReview(500));
	reviewsList.sentimentAnalysis(reviewsList.selectReview(500));
	reviewsList.summary(positiveWordList, negativeWordList);

	//reviewsList.sentimentSummary();
	//reviewsList.summary(positiveWordList, negativeWordList);
	//reviewsList.sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(3));

	//reviewsList.comparison(positiveWordList, negativeWordList, reviewsList.selectReview(8));
	//Sorting::selectionSort(positiveWordList);

	//reviewsList.summary(positiveWordList, negativeWordList);
	//reviewsList.sentimentSummary();

	//reviewsList.summary(positiveWordList, negativeWordList);
	//reviewsList.print(10);

	return 0;
}