#include "ReviewLL.hpp"
#include "Sorting.hpp"
#include "Analysis.hpp"
#include <iostream>

using namespace std;
int main() {
	//declare reviews, positive words, and negative words
	//ReviewList reviewsList;
	//WordList positiveWordList, negativeWordList;


	//cout << endl << "adding positive words";
	//positiveWordList.readWord("positive-words.txt", insertMethod::fromFront);
	//cout << endl << "adding negative words";
	//negativeWordList.readWord("negative-words.txt", insertMethod::fromFront);
	//reviewsList.readCSV("testing.CSV", positiveWordList, negativeWordList);


	//Sorting::radixSort(positiveWordList);
	//Sorting::radixSort(negativeWordList);
	//Sorting::radixSortAlphabetically(positiveWordList);
	//Sorting::radixSortAlphabetically(negativeWordList);

	//Sorting::selectionSort(positiveWordList);
	//Sorting::selectionSort(negativeWordList);
	//Sorting::selectionSortAlphabetically(positiveWordList);
	//Sorting::selectionSortAlphabetically(negativeWordList);

	//Sorting::bubbleSort(positiveWordList);
	//Sorting::bubbleSort(negativeWordList);
	//Sorting::bubbleSortAlphabetically(positiveWordList);
	//Sorting::bubbleSortAlphabetically(negativeWordList);

	//Sorting::mergeSort(positiveWordList);
	//Sorting::mergeSort(negativeWordList);
	//Sorting::mergeSortAlphabetically(positiveWordList);
	//Sorting::mergeSortAlphabetically(negativeWordList);

	//Sorting::radixSort(positiveWordList);
	//Sorting::radixSort(negativeWordList);
	//cout << "Positive Word List: " << endl << string(70, '-') << endl;
	//positiveWordList.printWordsAndFrequency();
	//cout << string(70, '-') << endl;
	//cout << "Negative Word List: " << endl << string(70, '-') << endl;
	//negativeWordList.printWordsAndFrequency();

	//reviewsList.comparison(reviewsList.selectReview(500));
	//reviewsList.sentimentAnalysis(reviewsList.selectReview(500));
	//
	//Analysis::summary(reviewsList, positiveWordList, negativeWordList);
	//Analysis::sentimentSummary(reviewsList);
	//reviewsList.sentimentSummary();
	//reviewsList.summary(positiveWordList, negativeWordList);
	//reviewsList.sentimentAnalysis(positiveWordList, negativeWordList, reviewsList.selectReview(3));

	//reviewsList.comparison(positiveWordList, negativeWordList, reviewsList.selectReview(8));
	//Sorting::selectionSort(positiveWordList);

	//reviewsList.summary(positiveWordList, negativeWordList);
	//reviewsList.sentimentSummary();

	//reviewsList.summary(positiveWordList, negativeWordList);
	//reviewsList.print(10);

	WordList insertFront1, insertEnd1, insertEndTail1, insertFront2, insertEnd2, insertEndTail2;

	insertFront1.readWord("positive-words.txt", insertMethod::fromFront);
	insertEnd1.readWord("positive-words.txt", insertMethod::fromEnd);
	insertEndTail1.readWord("positive-words.txt", insertMethod::fromEndUsingTail);

	insertFront2.readWord("negative-words.txt", insertMethod::fromFront);
	insertEnd2.readWord("negative-words.txt", insertMethod::fromEnd);
	insertEndTail2.readWord("negative-words.txt", insertMethod::fromEndUsingTail);

	return 0;
}