#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "LinkedList.hpp"
#include <ctime>
#include <chrono>
using namespace std::chrono;

//default constructor 
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

WordNode::WordNode(string word) {
	this->word = word;
	next = nullptr;
}


//review list
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
		count++;
	}
	return count;
}

ReviewNode* ReviewList::selectReview(int index) {
	ReviewNode* returnNode = head;
	int count = 0;
	if (returnNode != nullptr) {
		while (count < index) {
			returnNode = returnNode->next;
			count++;
		}
		return returnNode;
	}
	cerr << "Error: This index is out of the range!" << endl;
	return returnNode;
}

void ReviewList::readCSV(string path, WordList& good, WordList& bad) {
	ifstream file(path);
	string line;

	if (file.is_open()) {
		getline(file, line);

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
				if (good.searchWord(word)) {
					goodWords += " - " + word + "\n";
					goodCount++;
				}
				else if (bad.searchWord(word)) {
					badWords += " - " + word + "\n";
					badCount++;
				}
			}

			cout << fixed << setprecision(2);
			int raw = goodCount - badCount;
			int max = goodCount + badCount;
			int min = -max;
			double normalized = (raw - min) / static_cast<double>(max - min);

			double sentiment = 1 + (4 * normalized);

			this->addReview(review, rating, goodCount, badCount, sentiment, goodWords, badWords);
		}
		file.close();
	}
	else {
		cerr << "Error reading file" << endl;
	}
}

void ReviewList::print(int amount) {
	ReviewNode* current = head;
	int count = 0;
	while (current != nullptr && count < amount) {
			cout << string(100, '-') << endl;
			cout << "Review: \n" << current->review << "\n \n" << "Rating: " << current->rating << endl << "Sentiment Score: " << current->sentiment << endl;
			cout << string(100, '-') << endl;
			current = current->next;
			count++;
		}
}

string ReviewList::trim(string str) {
	size_t start = 0;
	size_t end = str.length() - 1;

	// Trim from the left (start) - Skip spaces and special characters
	while (start <= end && (isspace(static_cast<unsigned char>(str[start])) || !isalnum(static_cast<unsigned char>(str[start])))) {
		start++;
	}

	// Trim from the right (end) - Skip spaces and special characters
	while (end >= start && (isspace(static_cast<unsigned char>(str[end])) || !isalnum(static_cast<unsigned char>(str[end])))) {
		end--;
	}
	// Convert the trimmed portion to lowercase
	string trimmedStr = (start <= end) ? str.substr(start, end - start + 1) : "";

	// Convert each character to lowercase
	for (char& ch : trimmedStr) {
		ch = tolower(static_cast<unsigned char>(ch));
	}

	return trimmedStr;

}

void ReviewList::updateFrequency(WordList& good, WordList& bad) {
	ReviewNode* temp = head;
	int count = 1;

	while (temp != nullptr) {
		cout << "Current position: " << count << "\n\n";
		cout << temp->review << "\n\n";

		istringstream iss(temp->review);
		string word;

		while (iss >> word) {
			word = trim(word);

			if (good.searchWord(word)) {
				cout << "Good: " << word << endl;
				good.addFrequency(word);
			}
			else if (bad.searchWord(word)) {
				cout << "Bad: " << word << endl;
				bad.addFrequency(word);
			}
		}

		//sorting
		auto start = steady_clock::now();

		good.radixSort();

		auto end = steady_clock::now();

		auto elapsed = duration_cast<microseconds>(end - start).count();
		cout << endl << "sort time : " << elapsed << " microseconds" << endl;

		start = steady_clock::now();
		bad.radixSort();
		end = steady_clock::now();
		elapsed = duration_cast<microseconds>(end - start).count();
		cout << endl << "sort time : " << elapsed << " microseconds" << endl;


		temp = temp->next;
		count++;
	}
}

void ReviewList::comparison(WordList& good, WordList& bad, ReviewNode* reviews) {
	int rating = reviews->rating;
	int comp = round(reviews->sentiment);

	cout << "Sentiment Score (1-5) = " << comp << endl;
	cout << "Rating given by user = " << rating << endl;

	if (comp == rating) {
		cout << "Analysis output: \n User's subjective evaluation matches the sentiment score provided by the analysis. \n There is a consistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
		return;
	}
	cout << "Analysis output: \n User's subjective evaluation does not match the sentiment score provided by the analysis. \n There is an inconsistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
}

void ReviewList::sentimentAnalysis(WordList& good, WordList& bad, ReviewNode* reviews) {
	int rating = reviews->rating;
	int comp = round(reviews->sentiment);
	string rev = "";
	switch (comp) {
	case 1:
		rev = "Very Bad";
		break;
	case 2:
		rev = "Bad";
		break;
	case 3:
		rev = "Neutral";
		break;
	case 4:
		rev = "Good";
		break;
	case 5:
		rev = "Very Good";
		break;
	}
	cout << "Positive Words = " << reviews->good << endl;
	cout << reviews->goodWords;
	cout << "Negative Words = " << reviews->bad << endl;
	cout << reviews->badWords;
	cout << "Sentiment score (1-5) is " << reviews->sentiment << ", thus the rating should be equal to " << comp << "(" << rev << ")" << endl;
}

void ReviewList::searchRelevant(string searchWord) {
	ReviewNode* currentNode = head;
	int wordCount = 0;
	int index = 0;
	while (currentNode != nullptr) {
		istringstream iss(currentNode->review);
		string word;
		bool printedOut = false;
		while (iss >> word) {
			word = trim(word);
			if (word == searchWord) {
				if (!printedOut) {
					cout << "Review with word: " << index+1 << "\n \n";
					cout << currentNode->review << endl << endl;
					cout << string(50, '-') << endl << endl;
					printedOut = true;
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


ReviewList::~ReviewList() {
	ReviewNode* temp;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
}



//word list
WordList::WordList() {
	head = nullptr;
	tail = nullptr;
}

void WordList::addWord(string word, int frequency) {
	WordNode* newNode = new WordNode(word);
	newNode->frequency = frequency;
	if (head == nullptr) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

void WordList::addFrequency(string word) {
	WordNode* current = head;
	while (current != nullptr) {
		if (current->word == word) {
			current->frequency++;
			return;
		}
		current = current->next;
	}
}

bool WordList::searchWord(string word) {
	WordNode* checkNode = head;
	while (checkNode != nullptr) {
		if (checkNode->word == word) {
			cout << "word found! \n word: " << word << endl << "frequency: " << checkNode->frequency << endl;
			return true;
		}
		checkNode = checkNode->next;
	}
	return false;
}

void WordList::readWord(string path) {
	ifstream file(path);
	if (file.is_open()) {
		string word;
		while (getline(file, word)) {
			this->addWord(word, 0);
		}
	}
	else {
		cerr << "Error opening the file." << endl;
	}
}

void WordList::selectionSort() {
	WordNode* first = head;

	while (first != nullptr) {
		WordNode* startNode = first;
		WordNode* currentNode = first->next;

		while (currentNode != nullptr) {
			if (currentNode->frequency < startNode->frequency) {
				startNode = currentNode;
			}
			currentNode = currentNode->next;
		}

		if (startNode != first) {
			swap(first->word, startNode->word);
			swap(first->frequency, startNode->frequency);
		}
		first = first->next;
	}
}

void WordList::radixSort() {
	if (head == nullptr || head->next == nullptr) return; // No need to sort

	// Find the maximum frequency in the linked list
	WordNode* current = head;
	int maxFrequency = current->frequency;
	while (current != nullptr) {
		if (current->frequency > maxFrequency)
			maxFrequency = current->frequency;
		current = current->next;
	}

	// Start at the least significant digit place (units, tens, hundreds, etc.)
	int place = 1; // place = 10^0 for the units place

	// Continue sorting for each digit place until the largest number is fully processed
	while (maxFrequency / place > 0) {
		// Create 10 buckets (for digits 0-9)
		WordNode* outputList[10] = { nullptr };
		WordNode* tails[10] = { nullptr };

		// Reset current to head to traverse the linked list again
		current = head;

		// Place each node in the corresponding bucket based on the current digit
		while (current != nullptr) {
			int digit = (current->frequency / place) % 10;

			// Add node to the bucket
			if (outputList[digit] == nullptr) {
				outputList[digit] = current;
				tails[digit] = current;
			}
			else {
				tails[digit]->next = current;
				tails[digit] = current;
			}

			current = current->next;
		}

		// Reassemble the list by combining the buckets
		WordNode* newHead = nullptr;
		WordNode* newTail = nullptr;

		for (int i = 0; i < 10; i++) {
			if (outputList[i] != nullptr) {
				if (newHead == nullptr) {
					newHead = outputList[i];
					newTail = tails[i];
				}
				else {
					newTail->next = outputList[i];
					newTail = tails[i];
				}
			}
		}

		// Set the last node's next pointer to nullptr to avoid cycles
		newTail->next = nullptr;

		// Update the head pointer to the newly sorted list
		head = newHead;

		// Move to the next digit place (tens, hundreds, etc.)
		place *= 10;
	}
}

void WordList::bubbleSort() {
	if (head == nullptr) {
		return;
	}

	WordNode* current;
	WordNode* previous = nullptr;
	bool swapped;

	do {
		swapped = false;
		current = head;

		while (current->next != previous) {
			if (current->frequency > current->next->frequency) {
				string word = current->word;
				int frequency = current->frequency;

				current->word = current->next->word;
				current->frequency = current->next->frequency;

				current->next->word = word;
				current->next->frequency = frequency;

				swapped = true;
			}
			current = current->next;
		}
		previous = current;
	} while (swapped);
}

// Helper function to merge two sorted linked lists
WordNode* WordList::merge(WordNode* left, WordNode* right) {
	// Base cases
	if (!left) return right;
	if (!right) return left;

	// Choose the smaller node and recursively merge the rest
	if (left->frequency <= right->frequency) {
		left->next = merge(left->next, right);
		return left;
	}
	else {
		right->next = merge(left, right->next);
		return right;
	}
}

// Helper function to find the middle of the list using slow/fast pointer technique
WordNode* WordList::findMiddle(WordNode* head) {
	if (!head) return nullptr;

	WordNode* slow = head;
	WordNode* fast = head->next;

	// Move `slow` by one and `fast` by two steps
	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

// The recursive mergeSort function
WordNode* WordList::mergeSort(WordNode* head) {
	// Base case: If the list is empty or contains only one node, it is already sorted
	if (!head || !head->next) {
		return head;
	}

	// Step 1: Split the list into two halves
	WordNode* middle = findMiddle(head);
	WordNode* secondHalf = middle->next;
	middle->next = nullptr;  // Split the list into two parts

	// Step 2: Recursively sort both halves
	WordNode* left = mergeSort(head);
	WordNode* right = mergeSort(secondHalf);

	// Step 3: Merge the sorted halves
	return merge(left, right);
}

// Wrapper function for mergeSort to sort the entire list
void WordList::mergeSort() {
	head = mergeSort(head);
}




void WordList::printWordsAndFrequency() {
	WordNode* currentNode = head;

	if (head != nullptr) {
		while (currentNode != nullptr) {
			if (currentNode->frequency == 0) {
				currentNode = currentNode->next;
			}
			else {
				cout << currentNode->word << ": " << currentNode->frequency << endl;
				currentNode = currentNode->next;
			}
		}
	}
}

WordNode* WordList::recursionList(WordNode* current, WordNode* previous) {
	if (!current) {
		return previous;
	}

	WordNode* nextNode = current->next;
	current->next = previous;
	return recursionList(nextNode, current);
}

void WordList::reverseList() {
	cout << head->word << endl << tail->word;

	if (head == nullptr) {
		return;
	}

	WordNode* prevHead = head;
	head = recursionList(head, nullptr);
	tail = prevHead;

	cout << head->word << endl << tail->word;

}

WordList::~WordList() {
	WordNode* temp;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
}

WordList mergeWordList(WordList& wordlist1, WordList& wordlist2) {
	WordList mergedList;

	//loop through list 1 first
	WordNode* currentNode = wordlist1.head;
	while (currentNode != nullptr) {
		mergedList.addWord(currentNode->word, currentNode->frequency);
		currentNode = currentNode->next;
	}

	//loop through list 2
	currentNode = wordlist2.head;
	while (currentNode != nullptr) {
		mergedList.addWord(currentNode->word, currentNode->frequency);
		currentNode = currentNode->next;
	}


	return mergedList;
}

void summary(ReviewList& reviews, WordList& good, WordList& bad) {
	ReviewNode* countReview = reviews.head;
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
	cout << "Frequency of each GOOD words used in overall reviews, listed in ascending order based on frequency: " << "\n \n";
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
	cout << "Maximum used BAD word in the reviews : " << maxBadFrequencyWord->word << endl << "frequency : " << maxBadFrequencyWord->frequency << endl;
}
