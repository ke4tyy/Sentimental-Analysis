#include "WordLL.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

WordNode::WordNode(string word, int frequency) {
	this->word = word;
	this->frequency = frequency;
	next = nullptr;
}
WordNode::WordNode() {
	word = "";
	frequency = 0;
	next = nullptr;
}

//word list
WordList::WordList() {
	head = tail = nullptr;
}

void WordList::addWord(string word, int frequency, insertMethod method) {
	WordNode* newNode = new WordNode(word, frequency);

	if (head == nullptr) {
		head = tail = newNode;
		return;
	}

	switch (method) {
	case insertMethod::fromFront:
		newNode->next = head;
		head = newNode;
		break;

	case insertMethod::fromEnd:
		{
			WordNode* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
			tail = newNode;
		}
		break;

	case insertMethod::fromEndUsingTail:
		tail->next = newNode;
		tail = newNode;
		break;
	}
}

void WordList::addFrequency(string word) {
	word = trimming::trim(word);
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
			return true;
		}
		checkNode = checkNode->next;
	}
	return false;
}

void WordList::readWord(const string& path, insertMethod method) {
	ifstream file(path);
	auto start = high_resolution_clock::now();
	if (file.is_open()) {
		string word;
		while (file >> word) {
			addWord(word, 0, method);
		}
	}
	else {
		cerr << "Error opening the file." << endl;
	}
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();

	switch (method) {
	case insertMethod::fromFront:
		cout << "Method used : Insert from Front" << endl;
		break;
	case insertMethod::fromEnd:
		cout << "Method used : Insert from End" << endl;
		break;
	case insertMethod::fromEndUsingTail:
		cout << "Method used : Insert from End using Tail" << endl;
		break;
	}
	cout << "Time elapsed : " << elapsed << " microseconds. " << endl << endl;
}

WordNode* WordList::findMiddle(WordNode* node) {
	if (!node || !node->next) return node;

	WordNode* slow = node;
	WordNode* fast = node->next;

	//one goes the end while the other will be at the middle
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	// Split the list into two halves
	WordNode* mid = slow->next;
	slow->next = nullptr;  //set next to null to break list to half
	return mid;
}

// Binary search function for linked list
void WordList::binarySearch(string searchWord) {
	auto timeStart = high_resolution_clock::now();

	if (head == nullptr) {
		cout << "The list is empty." << endl;
		return;
	}

	WordNode* start = head;
	WordNode* end = nullptr;

	while (start != end) {
		WordNode* middle = findMiddle(start);

		// Compare the middle node's word with the target word
		if (middle->word == searchWord) {
			auto timeEnd = high_resolution_clock::now();
			auto elapsed = duration_cast<microseconds>(timeEnd - timeStart).count();
			cout << string(70, '-') << endl;
			cout << "Binary Search: \nWord Found! \nSearched word : " << middle->word
				<< "\nFrequency : " << middle->frequency << "\nTime elapsed : " << elapsed
				<< " microseconds" << endl;
			cout << string(70, '-') << endl;

			return;
		}
		else if (middle->word < searchWord) {
			// Search in the right half
			start = middle->next;
		}
		else {
			// Search in the left half
			end = middle;
		}
	}

	cout << "Word not found in the list." << endl;
}

void WordList::linearSearch(string searchWord) {
	auto timeStart = high_resolution_clock::now();
	WordNode* currentNode = head;

	while (currentNode != nullptr) {
		if (currentNode->word == searchWord) {
			auto timeEnd = high_resolution_clock::now();
			auto elapsed = duration_cast<microseconds>(timeEnd - timeStart).count();
			cout << string(70, '-') << endl;
			cout << "Word Found! \n Searched word : " << currentNode->word << endl << "Frequency : " << currentNode->frequency << endl << "Time elapsed : " << elapsed << " microseconds" << endl;
			cout << string(70, '-') << endl;
			return;
		}

		currentNode = currentNode->next;
	}
	cout << "Word is not found in this list." << endl;
}

void WordList::printWordsAndFrequency() {
	WordNode* currentNode = head;

	if (head != nullptr) {
		while (currentNode != nullptr) {
			if (currentNode->frequency == 0) {
				currentNode = currentNode->next;
			}
			else {
				cout << left << setw(15) << currentNode->word << " = " << currentNode->frequency << " times" << endl;
				currentNode = currentNode->next;
			}
		}
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

//trimming function (global variable): so that both ReviewLL and WordLL can use
namespace trimming {
	string trimming::trim(string str) {
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

}