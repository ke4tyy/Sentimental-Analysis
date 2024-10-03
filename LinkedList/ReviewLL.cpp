#include "ReviewLL.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;


ReviewNode::ReviewNode(string review, int rating, int goodCount, int badCount, double sentiment, string good, string bad) {
	this->review = review;
	this->rating = rating;
	this->good = goodCount;
	this->bad = badCount;
	this->sentiment = sentiment;
	this->goodWords = good;
	this->badWords = bad;
	next = nullptr;
}



//REVIEW LIST FUNCTIONS
ReviewList::ReviewList() {
	head = nullptr;
	tail = nullptr;
}

void ReviewList::addReview(string review, int rating, int goodCount, int badCount, double sentiment, string good, string bad) {
	ReviewNode* newNode = new ReviewNode(review, rating, goodCount, badCount, sentiment, good, bad);
	if (head == nullptr) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

int ReviewList::countTotal() {
	ReviewNode* current = head;
	int count = 0;
	while (current != nullptr) {
		current = current->next;
		count++; // add count
	}
	return count;
}

ReviewNode* ReviewList::selectReview(int index) {
	ReviewNode* returnNode = head;
	int count = 0;
	if (returnNode != nullptr && index >= 0 && index <= countTotal()) {
		while (count < index) {
			returnNode = returnNode->next;
			count++;
		}
		return returnNode; //looped till the desired "index", return the node
	}
	cerr << "Error: This index is out of the range!" << endl;
	return nullptr;
}

void ReviewList::readCSV(string path, WordList& good, WordList& bad) {
	ifstream file(path); //open file
	if (!file.is_open()) {
		cerr << "Error reading file : " << path << endl;
		return;
	}
	string line;
	getline(file, line); //get header line ('Reviews', 'Rating')
	if (line.empty()) {
		cerr << "Error in reading CSV File \n potential reasons: empty or malformed" << endl;
		return;
	}
	auto start = high_resolution_clock::now();
	while (getline(file, line)) {
		size_t lastComma = line.find_last_of(','); //get the last comma that separates review and rating
		string review = line.substr(0, lastComma); //gets review
		string rat = line.substr(lastComma + 1); //gets rating
		int rating = stoi(rat);

		int goodCount = 0;
		int badCount = 0;

		string goodWords = "";
		string badWords = "";
		istringstream iss(review);

		string word;
		while (iss >> word) {
			word = trim(word);
			bool foundInGood = good.searchWord(word);
			bool foundInBad = !foundInGood && bad.searchWord(word); // search bad only if not found in good

			if (foundInGood) {
				goodWords += " - " + word + "\n";
				good.addFrequency(word); //adds frequency into the list
				goodCount++;
			}
			else if (foundInBad) {
				badWords += " - " + word + "\n";
				bad.addFrequency(word);
				badCount++;
			}
		}
		this->addReview(review, rating, goodCount, badCount, calculateSentiment(goodCount, badCount)
			, goodWords, badWords);
	}
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << "Time elapsed : " << elapsed << " microseconds. " << endl;
	file.close();
}

void ReviewList::print(int amount) {
	ReviewNode* current = head;
	int count = 0;
	while (current != nullptr && count < amount) {
		cout << string(100, '-') << endl;
		cout << "Review: \n" << current->review << "\n \n" << "Rating: " << current->rating << endl << "Sentiment Score: " << current->sentiment << endl;
		cout << "Good word counts : " << current->good << endl << current->goodWords << endl;
		cout << "Bad word counts : " << current->bad << endl << current->badWords << endl;
		cout << string(100, '-') << endl;
		current = current->next;
		count++;
	}
}

string ReviewList::trim(string str) {
	size_t start = 0;
	size_t end = str.length() - 1;

	//trims from the left
	while (start <= end && (isspace(static_cast<unsigned char>(str[start])) || !isalnum(static_cast<unsigned char>(str[start])))) {
		start++;
	}

	//trims from the right
	while (end >= start && (isspace(static_cast<unsigned char>(str[end])) || !isalnum(static_cast<unsigned char>(str[end])))) {
		end--;
	}
	//convert the string to lowercase
	string trimmedStr = (start <= end) ? str.substr(start, end - start + 1) : "";
	for (char& ch : trimmedStr) {
		ch = tolower(static_cast<unsigned char>(ch));
	}

	return trimmedStr;

}

double ReviewList::calculateSentiment(int goodCount, int badCount) {
	cout << fixed << setprecision(2);
	int raw = goodCount - badCount;
	int max = goodCount + badCount;
	int min = -max;
	double normalized = (raw - min) / static_cast<double>(max - min);

	double sentiment = 1 + (4 * normalized);
	return sentiment;
}

void ReviewList::comparison(WordList& good, WordList& bad, ReviewNode* reviews) {
	cout << "Comparison Analysis : " << endl << string(70, '-') << endl;
	cout << "Selected Review : " << reviews->review << endl << string(70, '-') << endl;

	int rating = reviews->rating;
	int comp = round(reviews->sentiment);

	cout << "Sentiment Score (1-5) = " << comp << endl;
	cout << "Rating given by user = " << rating << endl;

	if (comp == rating) {
		cout << "Analysis output: \n User's subjective evaluation matches the sentiment score provided by the analysis. \n There is a consistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
		return;
	}
	cout << "Analysis output: \n User's subjective evaluation does not match the sentiment score provided by the analysis. \n There is an inconsistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl << string(70, '-') << endl;
}

void ReviewList::sentimentAnalysis(WordList& good, WordList& bad, ReviewNode* reviews) {

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
	cout << "Positive Words = " << reviews->good << " times " << endl;
	cout << reviews->goodWords;
	cout << "Negative Words = " << reviews->bad << " times " << endl;
	cout << reviews->badWords;
	cout << "Sentiment score (1-5) is " << reviews->sentiment << ", thus the rating should be equal to " << comp << "(" << rev << ")" << endl << string(70, '-') << endl;
}

void ReviewList::searchRelevant(string searchWord) {
	ReviewNode* currentNode = head;
	searchWord = trim(searchWord);
	int wordCount = 0;
	int index = 0;
	while (currentNode != nullptr) {
		istringstream iss(currentNode->review);
		string word;
		bool printedOut = false; //check if the review have been printed out before or no in the same review
		while (iss >> word) {
			word = trim(word);
			if (word == searchWord) {
				if (!printedOut) {
					cout << "Review with word: " << index + 1 << "\n \n";
					cout << currentNode->review << endl << endl; //prints the review
					cout << string(50, '-') << endl << endl;
					printedOut = true; //change to true so that it wont be printed out again
					index++;
				}

				wordCount++;
			}
		}
		currentNode = currentNode->next;
	}
	cout << "Total found reviews with searched word : " << index << endl;
	cout << "Frequency of searched word : " << wordCount << endl;
}

void ReviewList::sentimentSummary() {
	ReviewNode* currentNode = head;
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

void ReviewList::summary(WordList& good, WordList& bad) {
	ReviewNode* countReview = head;
	//making sure that the list is sorted by frequency
	good.radixSort();
	bad.radixSort();
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

//destructor

ReviewList::~ReviewList() {
	ReviewNode* temp;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
}

