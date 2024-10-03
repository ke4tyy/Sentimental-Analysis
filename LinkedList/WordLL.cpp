#include "WordLL.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

WordNode::WordNode(string word) {
	this->word = word;
	next = nullptr;
}

WordNode::WordNode() {
	word = "";
	frequency = 0;
	next = nullptr;
}


//word list
WordList::WordList() {
	head = nullptr;
}

void WordList::addWordFromFront(string word) {
	WordNode* newNode = new WordNode(word);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}

}

void WordList::addWordFromEnd(string word) {
	WordNode* newNode = new WordNode(word);
	//auto start = high_resolution_clock::now();
	if (head == nullptr) {
		head = newNode;
	}
	else {
		WordNode* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	//auto end = high_resolution_clock::now();
	//auto elapsed = duration_cast<nanoseconds>(end - start).count();
	//cout << endl << "Time elapsed : " << elapsed << " nanoseconds. " << endl;
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
	auto start = high_resolution_clock::now();
	ifstream file(path);
	if (file.is_open()) {
		string word;
		while (getline(file, word)) {
			this->addWordFromFront(word);
		}
	}
	else {
		cerr << "Error opening the file." << endl;
	}
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << endl << "Time elapsed : " << elapsed << " microseconds. " << endl;
}

void WordList::selectionSort() {
	auto start = high_resolution_clock::now();
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
			swap(first->word, startNode->word); //swap the word 
			swap(first->frequency, startNode->frequency); //swap frequency
		}
		first = first->next;
	}
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Selection Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}

void WordList::radixSort() {
	auto start = high_resolution_clock::now();

	if (head == nullptr || head->next == nullptr) return; //error handling

	//find max frequency
	WordNode* current = head;
	int maxFrequency = current->frequency;
	while (current != nullptr) {
		if (current->frequency > maxFrequency)
			maxFrequency = current->frequency;
		current = current->next;
	}
	int place = 1;

	//contine sorting as place gets larger
	while (maxFrequency / place > 0) {
		//digits 0 to 9
		WordNode* outputList[10] = { nullptr };
		WordNode* tails[10] = { nullptr };

		//change current to head to loop from front of list
		current = head;

		while (current != nullptr) {
			int digit = (current->frequency / place) % 10;

			// Add node
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

		//set last node next to null
		newTail->next = nullptr;

		//update head
		head = newHead;

		//increase placing
		place *= 10;
	}
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Radix Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}

void WordList::bubbleSort() {
	auto start = high_resolution_clock::now();
	if (head == nullptr) return;
	WordNode* current;
	WordNode* previous = nullptr;
	bool swapped; //check if sweapped or no

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

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Bubble Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
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

WordNode* WordList::merge(WordNode* left, WordNode* right) {
	WordNode dummy;
	WordNode* tail = &dummy; //helps merge

	//compare and merge
	while (left && right) {
		if (left->frequency < right->frequency) {
			tail->next = left;
			left = left->next;
		}
		else {
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}

	if (left) tail->next = left;
	if (right) tail->next = right;

	return dummy.next;
}

WordNode* WordList::mergeSort(WordNode* node) {
	if (!node || !node->next) return node; //return if sorted

	//split list to half
	WordNode* mid = findMiddle(node);

	//sort recursively
	WordNode* left = mergeSort(node);  // First half
	WordNode* right = mergeSort(mid);  // Second half

	//merge the sorted lists
	return merge(left, right);
}

void WordList::mergeSort() {
	auto start = high_resolution_clock::now();
	head = mergeSort(head);
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Merge Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}

void WordList::selectionSortAlphabetically() {
	auto start = high_resolution_clock::now();
	WordNode* first = head;

	while (first != nullptr) {
		WordNode* startNode = first;
		WordNode* currentNode = first->next;

		while (currentNode != nullptr) {
			if (currentNode->word < startNode->word) {
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

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Selection Sorting done! \nTime elapsed : " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}

void WordList::radixSortAlphabetically() {
	auto start = high_resolution_clock::now();

	if (head == nullptr || head->next == nullptr) return;

	//find max length
	WordNode* current = head;
	int maxLength = current->word.length();
	while (current != nullptr) {
		if (current->word.length() > maxLength)
			maxLength = current->word.length();
		current = current->next;
	}


	for (int pos = maxLength - 1; pos >= 0; pos--) {
		//a to z
		WordNode* outputList[26] = { nullptr };
		WordNode* tails[26] = { nullptr };


		current = head;

		while (current != nullptr) {

			int charIndex = pos < current->word.length() ? (current->word[pos] - 'a') : -1;

			if (charIndex < 0 || charIndex >= 26) {
				charIndex = 0;
			}

			//add node 
			if (outputList[charIndex] == nullptr) {
				outputList[charIndex] = current;
				tails[charIndex] = current;
			}
			else {
				tails[charIndex]->next = current;
				tails[charIndex] = current;
			}
			current = current->next;
		}

		WordNode* newHead = nullptr;
		WordNode* newTail = nullptr;

		for (int i = 0; i < 26; i++) {
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

		//set last node next to null
		newTail->next = nullptr;

		//update head
		head = newHead;

	}

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Radix Sorting done! \nTime elapsed: " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}

void WordList::bubbleSortAlphabetically() {
	auto start = high_resolution_clock::now();

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
			if (current->word > current->next->word) {
				swap(current->word, current->next->word);
				swap(current->frequency, current->next->frequency);
				swapped = true;
			}
			current = current->next;
		}
		previous = current;
	} while (swapped);

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Bubble Sorting done! \nTime elapsed: " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}

WordNode* WordList::mergeAlphabetically(WordNode* left, WordNode* right) {
	WordNode dummy;
	WordNode* tail = &dummy;

	while (left && right) {
		if (left->word < right->word) {
			tail->next = left;
			left = left->next;
		}
		else {
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}

	if (left) tail->next = left;
	if (right) tail->next = right;

	return dummy.next;
}

WordNode* WordList::mergeSortAlphabetically(WordNode* node) {
	if (!node || !node->next) return node;

	WordNode* mid = findMiddle(node);
	WordNode* left = mergeSortAlphabetically(node);    // First half
	WordNode* right = mergeSortAlphabetically(mid);    // Second half

	return mergeAlphabetically(left, right);
}

void WordList::mergeSortAlphabetically() {
	auto start = high_resolution_clock::now();
	head = mergeSortAlphabetically(head);
	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Merge Sorting done! \nTime elapsed : " << elapsed << " microseconds." << endl << string(70, '-') << endl;
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

