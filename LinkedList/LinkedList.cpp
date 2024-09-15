#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "LinkedList.hpp"

//default constructor 
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


//add Review function
void LinkedList::addReview(string rev, int rat) {
	Node* newNode = new Node(rev, rat);
	addNode(newNode);
}

//add Word function
void LinkedList::addWord(string w) {
	Node* newNode = new Node(w, -1);
	addNode(newNode);
}

void LinkedList::addWordAndFreq(string w) {
	Node* temp = head;
	while (temp != nullptr) {
		if (temp->word == w) {
			temp->frequency++;
			return;
		}
		temp = temp->next;
	}
	Node* newNode = new Node(w, 0);
	addNode(newNode);
}

//printing reviews or word based on the boolean value

void LinkedList::print(int amount, int choice) {
	Node* temp = head;
	int count = 0;
	while (temp != nullptr && count < amount) {
		if (choice == 1) {
			cout << temp->word << endl;
		}
		else if (choice == 2) {
			cout << temp->word << ", Frequency: " << temp->frequency << endl;
		}
		else if (choice == 3) {
			cout << string(100, '-') << endl;
			cout << "Review: \n" << temp->review << "\n \n" << "Rating: " << temp->rating << endl;
			cout << string(100, '-') << endl;
		}
		temp = temp->next;
		count++;
	}
}


int LinkedList::countTotal() {
	Node* temp = head;
	int count = 0;

	while (temp != nullptr) {
		count++;
		temp = temp -> next;
	}
	return count;
}

string LinkedList::selectReview(int index) {
	Node* temp = head;
	int current = 0;
	if (temp != nullptr) {
		while (current < index) {
			temp = temp->next;
			current++;
		}
		return temp->review;
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

bool LinkedList::contains(const string& word) {
	Node* temp = head;
	while (temp != nullptr) {
		if (temp->word == word) {
			return true;
		}
		temp = temp->next;
	}
	return false;
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

string trim(const string& str) {
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


//reading CSV file
void LinkedList::readCSV(LinkedList& linkedList, const string& filepath) {
	ifstream file(filepath); //check if filepath is correct
	
	string line;

	if (file.is_open()) {
		getline(file, line); //skips header

		while (getline(file, line)) {
			size_t lastComma = line.find_last_of(','); //find the last comma, because in the csv file the last comma separates the rating

			string review = line.substr(0, lastComma); //takes everything before the last comma

			string ratingStr = line.substr(lastComma + 1); //take the rating, because rating length is always 1, so just + 1 to get the rating

			int rating = stoi(ratingStr); //convert rating to integer

			linkedList.addReview(review, rating); // add it into the linked list
		}
		file.close();
	}
	else {
		cerr << "Error opening file" << endl;
	}
}

void LinkedList::readWords(LinkedList& linkedList, const string& filepath) {
	ifstream file(filepath);

	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			string word = line;
			linkedList.addWord(word);
		}
		file.close();
	}
	else {
		cerr << "Error opening file" << endl;
	}
}


void LinkedList::storeFreq(LinkedList& good, LinkedList& bad, LinkedList& reviews, LinkedList& words) {
	
	Node* temp = reviews.head;
	int limit = reviews.countTotal();
	int count = 0;



	while (temp != nullptr && count < limit) {
		cout << "Current position: " << count + 1 << endl << endl;
		cout << temp->review << endl << endl;

		istringstream iss(temp->review);
		string word;

		while (iss >> word) {
			word = trim(word);
			if (good.contains(word)) {
				cout << "Good: " << word << endl;
				words.addWordAndFreq(word);

			}
			else if (bad.contains(word)) {
				cout << "Bad: " << word << endl;
				words.addWordAndFreq(word);
			}
		}
		temp = temp->next;
		count++;
	}

}



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

void LinkedList::sentimentAnalysis(LinkedList& good, LinkedList& bad, const string& review) {
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
		if (good.contains(word)) {
			goodCount++;
			goodWords += " - " + word + "\n";
		}
		else if (bad.contains(word)) {
			badCount++;
			badWords += " - " + word + "\n";
		}
	}

	int raw = goodCount - badCount;
	int max = goodCount + badCount;
	int min = -max;
	double normalized = (raw - min) / static_cast<double>(max - min);

	double sentiment= 1 + (4 * normalized);
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
	cout << "Sentiment score (1-5) is " << sentiment << ", thus the rating should be equal to " << comp << "(" << rev <<")";
}