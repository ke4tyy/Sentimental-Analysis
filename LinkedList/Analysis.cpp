#include "Analysis.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

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
