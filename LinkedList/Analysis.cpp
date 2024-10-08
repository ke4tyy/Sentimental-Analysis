#include "Analysis.hpp"
#include "Sorting.hpp"
#include "WordLL.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

void Analysis::sentimentSummary(ReviewList& list) {
	ReviewNode* currentNode = list.head;
	int count = 0;
	double veryNegativeCount = 0;
	double NegativeCount = 0;
	double NeutralCount = 0;
	double PositiveCount = 0;
	double veryPositiveCount = 0;
	double averageSentiment = 0;
	double match = 0;
	double doesntMatch = 0;


	while (currentNode != nullptr) {
		count++;
		if (currentNode->sentiment <= 1) {
			veryNegativeCount++;
		}
		else if (currentNode->sentiment <= 2) {
			NegativeCount++;
		}
		else if (currentNode->sentiment <= 3) {
			NeutralCount++;
		}
		else if (currentNode->sentiment <= 4) {
			PositiveCount++;
		}
		else {
			veryPositiveCount++;
		}

		if (currentNode->rating == round(currentNode->sentiment)) {
			match++;
		}
		else {
			doesntMatch++;
		}

		averageSentiment += currentNode->sentiment;
		currentNode = currentNode->next;
	}
	averageSentiment /= count;
	cout << fixed << setprecision(2);

	cout << "Average sentiment score : " << averageSentiment << endl << string(70, '-') << endl;

	veryNegativeCount = (veryNegativeCount / count) * 100;
	NegativeCount = (NegativeCount / count) * 100;
	NeutralCount = (NeutralCount / count) * 100;
	PositiveCount = (PositiveCount / count) * 100;
	veryPositiveCount = (veryPositiveCount / count) * 100;
	match = (match / count) * 100;
	doesntMatch = (doesntMatch / count) * 100;

	cout << veryNegativeCount << "% of reviews are very negative (1)" << endl;
	cout << NegativeCount << "% of reviews are negative (2)" << endl;
	cout << NeutralCount << "% of reviews are neutral (3)" << endl;
	cout << PositiveCount << "% of reviews are positive (4)" << endl;
	cout << veryPositiveCount << "% of reviews are very positive (5)" << endl;
	cout << string(70, '-') << endl;

	cout << match << "% of reviews have sentiment score that matches the user's rating" << endl;
	cout << doesntMatch << "% of reviews have sentiment score that does not match the user's rating" << endl;

}

void Analysis::summary(ReviewList& list, WordList& good, WordList& bad) {
	ReviewNode* countReview = list.head;
	int reviewCount = 0;
	while (countReview != nullptr) {
		reviewCount++;
		countReview = countReview->next;
	}

	WordNode* countWordsFreq = good.head;

	WordNode* maxGoodFrequencyWord = good.head;
	int goodWordsFrequency = 0;
	while (countWordsFreq != nullptr) {
		if (maxGoodFrequencyWord->frequency < countWordsFreq->frequency) {
			maxGoodFrequencyWord = countWordsFreq;
		}
		goodWordsFrequency += countWordsFreq->frequency;
		countWordsFreq = countWordsFreq->next;
	}

	WordNode* maxBadFrequencyWord = bad.head;
	countWordsFreq = bad.head;
	int badWordsFrequency = 0;
	while (countWordsFreq != nullptr) {
		if (maxBadFrequencyWord->frequency < countWordsFreq->frequency) {
			maxBadFrequencyWord = countWordsFreq;
		}
		badWordsFrequency += countWordsFreq->frequency;
		countWordsFreq = countWordsFreq->next;
	}

	//frequency of good counts
	cout << string(70, '-') << endl << "Frequency of each GOOD words used in overall reviews, listed in ascending order based on frequency: " << "\n \n";
	int goodstart, badstart, goodend, badend;
	goodstart = badstart = 0;
	goodend = badend = 10;

	good.printWordsAndFrequency();
	cout << endl << string(70, '-') << endl;

	//frequency of bad counts
	cout << "Frequency of each BAD words used in overall reviews, listed in ascending order based on frequency: " << "\n \n";
	bad.printWordsAndFrequency();
	cout << endl << string(70, '-') << endl;

	//print summary
	cout << "Total Reviews: " << reviewCount << endl;
	cout << "Total Occurence of positive words: " << goodWordsFrequency << endl;
	cout << "Total Occurence of negative words: " << badWordsFrequency << endl;
	cout << endl << string(70, '-') << endl;

	//max used words
	cout << "Maximum used GOOD word in the reviews : " << maxGoodFrequencyWord->word << endl << "frequency : " << maxGoodFrequencyWord->frequency << endl;
	cout << "Maximum used BAD word in the reviews : " << maxBadFrequencyWord->word << endl << "frequency : " << maxBadFrequencyWord->frequency << endl << string(70, '-') << endl;
}

void Analysis::sentimentAnalysis(ReviewNode* reviews) {
	if (reviews == nullptr) return;
	cout << "Sentiment Analysis : " << endl << string(70, '-') << endl;
	cout << "Selected Review : " << reviews->review << endl << string(70, '-') << endl;
	int rating = reviews->rating;
	int comp = round(reviews->sentiment);
	string rev = "";
	//finds category
	switch (comp) {
	case 1:
		rev = "Very Negative";
		break;
	case 2:
		rev = "Negative";
		break;
	case 3:
		rev = "Neutral";
		break;
	case 4:
		rev = "Positive";
		break;
	case 5:
		rev = "Very Positive";
		break;
	}
	cout << endl << "Positive Words = " << reviews->good << " times " << endl;
	cout << reviews->goodWords;
	cout << endl << "Negative Words = " << reviews->bad << " times " << endl;
	cout << reviews->badWords;
	cout << endl << "Sentiment score (1-5) is " << reviews->sentiment << ", thus the rating should be equal to " << comp << "(" << rev << ")" << endl << string(70, '-') << endl;
}

void Analysis::comparison(ReviewNode* reviews) {
	if (reviews == nullptr) {
		cout << "This index is out of range!" << endl;
		return;
	}	cout << "Comparison Analysis : " << endl << string(70, '-') << endl;
	cout << "Selected Review : " << reviews->review << endl << string(70, '-') << endl;

	int rating = reviews->rating;
	int comp = round(reviews->sentiment);

	cout << "Sentiment Score (1-5) = " << comp << endl;
	cout << "Rating given by user = " << rating << endl << endl;

	if (comp == rating) {
		cout << "Analysis output: \n User's subjective evaluation matches the sentiment score provided by the analysis. \n There is a consistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
		return;
	}
	cout << "Analysis output: \n User's subjective evaluation does not match the sentiment score provided by the analysis. \n There is an inconsistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl << string(70, '-') << endl;
}

WordList* Analysis::copyList(WordList& list) {
	WordList* newList = new WordList;

	//error handling
	if (list.head == nullptr) return newList;

	// copy each node
	WordNode* current = list.head;
	while (current != nullptr) {
		newList->addWord(current->word, current->frequency, insertMethod::fromEndUsingTail);
		current = current->next;
	}
	return newList;
}

void Analysis::compareSort(WordList& list, bool alphabetically) {
	WordList* radix = Analysis::copyList(list);
	WordList* selection = Analysis::copyList(list);
	WordList* merge = Analysis::copyList(list);
	WordList* bubble = Analysis::copyList(list);

	if (alphabetically) {
		Sorting::radixSortAlphabetically(*radix);
		Sorting::mergeSortAlphabetically(*merge);
		Sorting::selectionSortAlphabetically(*selection);
		Sorting::bubbleSortAlphabetically(*bubble);
	}
	else {
		Sorting::radixSort(*radix);
		Sorting::mergeSort(*merge);
		Sorting::selectionSort(*selection);
		Sorting::bubbleSort(*bubble);
	}
}

void Analysis::compareInsertion(WordList& list) {
	WordList* front = new WordList;
	WordList* end = new WordList;
	WordList* endTail = new WordList;

	if (list.head == nullptr) return;

	WordNode* current = list.head;
	
	auto frontStart = high_resolution_clock::now();
	while (current != nullptr) {
		front->addWord(current->word, current->frequency, insertMethod::fromFront);
		current = current->next;
	}
	auto frontEnd = high_resolution_clock::now();
	auto frontElapsed = duration_cast<microseconds>(frontEnd - frontStart).count();
	cout << "Insert from front time: " << frontElapsed << " microseconds" << endl;
	current = list.head;

	auto endStart = high_resolution_clock::now();
	while (current != nullptr) {
		front->addWord(current->word, current->frequency, insertMethod::fromEnd);
		current = current->next;
	}
	auto endEnd = high_resolution_clock::now();
	auto endElapsed = duration_cast<microseconds>(endEnd - endStart).count();
	cout << "Insert from end time: " << endElapsed << " microseconds" << endl;
	current = list.head;


	auto tailStart = high_resolution_clock::now();
	while (current != nullptr) {
		front->addWord(current->word, current->frequency, insertMethod::fromEndUsingTail);
		current = current->next;
	}
	auto tailEnd = high_resolution_clock::now();
	auto tailElapsed = duration_cast<microseconds>(tailEnd - tailStart).count();
	cout << "Insert from end time: " << tailElapsed << " microseconds" << endl;
}