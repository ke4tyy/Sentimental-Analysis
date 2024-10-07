#include "ReviewLL.hpp"
#include "Sorting.hpp"
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
			word = trimming::trim(word);
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


	system("cls");
	cout << "Finished Loading!" << endl << endl << 
		"Time elapsed : " << endl << 
		elapsed << " microseconds. " << endl << 
		elapsed / 1000 << " milliseconds" << endl << 
		static_cast<double>(elapsed) / 1000000 << " seconds\n\n";

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

double ReviewList::calculateSentiment(int goodCount, int badCount) {
	cout << fixed << setprecision(2);
	int raw = goodCount - badCount;
	int max = goodCount + badCount;
	int min = -max;
	double normalized = (raw - min) / static_cast<double>(max - min);

	double sentiment = 1 + (4 * normalized);
	return sentiment;
}

void ReviewList::searchRelevant(string searchWord) {
	ReviewNode* currentNode = head;
	searchWord = trimming::trim(searchWord);
	int wordCount = 0;
	int index = 0;
	auto start = high_resolution_clock::now();
	bool exists = false; 
	while (currentNode != nullptr) {
		istringstream iss(currentNode->review);
		string word;
		bool printedOut = false; //check if the review have been printed out before or no in the same review
		while (iss >> word) {
			word = trimming::trim(word);
			if (word == searchWord) {
				exists = true;
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
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	if (exists) {
		cout << "Total found reviews with searched word : " << index << endl;
		cout << "Frequency of searched word : " << wordCount << endl;
	}
	else {
		cout << "Word does not exists in the list." << endl;
	}

	cout << "Time taken: " << elapsed << " microseconds" << endl
		<< elapsed / 1000 << " milliseconds" << endl
		<< static_cast<double>(elapsed) / 1000000 << " seconds" << endl;
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

