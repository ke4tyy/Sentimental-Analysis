#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "LinkedList.hpp"

Node::Node(string content, int rat = -1) {
	review = "";
	word = "";
	rating = rat;

	next = nullptr; //first register as end before setting the next

	if (rat == -1) {
		word = content;
	}
	else if (rat == 0) {
		word = content;
		frequency = 1;
	}
	else {
		review = content;
	}
}
//default constructor 
ReviewNode::ReviewNode(string review, int rating) {
	this->review = review;
	this->rating = rating;

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

void ReviewList::addReview(string review, int rating) {
	ReviewNode* newNode = new ReviewNode(review, rating);
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

string ReviewList::selectReview(int index) {
	ReviewNode* returnNode = head;
	int count = 0;
	if (returnNode != nullptr) {
		while (count < index) {
			returnNode = returnNode->next;
			count++;
		}
		return returnNode->review;
	}
	cerr << "Error: This index is out of the range!" << endl;
	return "null";
}

void ReviewList::readCSV(string path) {
	ifstream file(path);
	string line;

	if (file.is_open()) {
		getline(file, line);

		while (getline(file, line)) {
			size_t lastComma = line.find_last_of(','); //get the last comma that separates review and rating
			string review = line.substr(0, lastComma); //gets review
			string rat = line.substr(lastComma + 1); //gets rating

			int rating = stoi(rat);
			this->addReview(review, rating);
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
			cout << "Review: \n" << current->review << "\n \n" << "Rating: " << current->rating << endl;
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

	while (temp->next != nullptr) {
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
		temp = temp->next;
		count++;
	}
}


void ReviewList::sentimentAnalysis(WordList good, WordList bad, const string& review) {
	cout << review << endl;
	cout << fixed << setprecision(2);
	int goodCount = 0;
	int badCount = 0;

	istringstream iss(review);

	string word;
	string goodWords = "";
	string badWords = "";
	while (iss >> word) {
		word = trim(word);
		if (good.searchWord(word)) {
			goodCount++;
			goodWords += " - " + word + "\n";
		}
		else if (bad.searchWord(word)) {
			badCount++;
			badWords += " - " + word + "\n";
		}
	}

	int raw = goodCount - badCount;
	int max = goodCount + badCount;
	int min = -max;
	double normalized = (raw - min) / static_cast<double>(max - min);

	double sentiment = 1 + (4 * normalized);
	string rev = "";

	int comp = round(sentiment);
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
	cout << "Positive Words = " << goodCount << endl;
	cout << goodWords;
	cout << "Negative Words = " << badCount << endl;
	cout << badWords;
	cout << "Sentiment score (1-5) is " << sentiment << ", thus the rating should be equal to " << comp << "(" << rev << ")";
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

WordNode* WordList::getHead() {
	return head;
}
WordNode* WordList::getTail() {
	return tail;
}

void WordList::addWord(string word) {
	WordNode* newNode = new WordNode(word);
	newNode->frequency = 0;
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
			this->addWord(word);
		}
	}
	else {
		cerr << "Error opening the file." << endl;
	}
}

WordList::~WordList() {
	WordNode* temp;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
}









//set head to null
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}










//assigning pointer location to the node
//concept explanation

//building block for addReview and addWord
void LinkedList::addNode(Node* newNode) {
	if (head == nullptr) { //to add the first node
		head = tail = newNode; //set head and tail at the same time
	}
	else { //else change the tail to new node
		tail->next = newNode;
		tail = newNode;
	}
}





int LinkedList::selectRating(int index) {
	Node* temp = head;
	int current = 0;
	if (temp != nullptr) {
		while (current < index) {
			temp = temp->next;
			current++;
		}
		return temp->rating;
	}
}

//destructor of the whole linked list
LinkedList::~LinkedList() {
	Node* temp;
	while (head != nullptr) {
		temp = head;
		head = head -> next;
		delete temp;
	}
}

//used for CSV trimming, because many commas in the review, stacking with the rating
//need change cuz chatgpt generated






void LinkedList::selectionSortWordsAscending() {
	Node* first = head;

	while (first != nullptr) {
		Node* startNode = first;
		Node* currentNode = first->next;

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

void LinkedList::radixSortWordsAscending() {
	if (head == nullptr || head->next == nullptr) return; // No need to sort

	// Find the maximum frequency in the linked list
	Node* current = head;
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
		Node* outputList[10] = { nullptr };
		Node* tails[10] = { nullptr };

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
		Node* newHead = nullptr;
		Node* newTail = nullptr;

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

void LinkedList::quickSortWordsAscending() {
	if (head == nullptr || head->next == nullptr) return; // No need to sort

	// Find the tail of the linked list
	Node* tail = head;
	while (tail != nullptr && tail->next != nullptr) {
		tail = tail->next;
	}

	// Quick Sort logic
	Node* start = head;
	Node* end = tail;

	// Stack-based quicksort approach without separate partition function
	while (start != end && start->next != end) {
		Node* pivot = start;
		Node* current = start->next;
		Node* prev = start;

		// Partitioning the list using the pivot
		while (current != end->next) {
			if (current->frequency < pivot->frequency) {
				prev = prev->next;
				swap(prev->word, current->word);
				swap(prev->frequency, current->frequency);
			}
			current = current->next;
		}

		// Swapping the pivot element with the partition point
		swap(pivot->word, prev->word);
		swap(pivot->frequency, prev->frequency);

		// Now the list is partitioned; quicksort left and right sub-lists
		Node* leftTail = prev;
		Node* rightStart = prev->next;

		// Recursive-like loop for the left side
		if (start != leftTail) {
			tail = leftTail;
			end = leftTail;
		}
		else {
			start = rightStart;
			end = tail;
		}
	}
}




Node* LinkedList::recursionList(Node* currentNode, Node* previousNode) {
	if (!currentNode) {
		return previousNode;
	}

	Node* nextNode = currentNode->next;
	currentNode->next = previousNode;
	return recursionList(nextNode, currentNode);
}

void LinkedList::reverseList() {
	head = recursionList(head);
}
