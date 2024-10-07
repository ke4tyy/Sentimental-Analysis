#include "Sorting.hpp"

#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

void Sorting::selectionSort(WordList& list) {
	auto start = high_resolution_clock::now();
	WordNode* first = list.head;

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

	// Update the tail
	WordNode* newTail = list.head;
	while (newTail && newTail->next) {
		newTail = newTail->next;
	}
	list.tail = newTail;

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Selection Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}

void Sorting::radixSort(WordList& list) {
	auto start = high_resolution_clock::now();

	if (list.head == nullptr || list.head->next == nullptr) return; //error handling

	WordNode* current = list.head;
	int maxFrequency = current->frequency;
	while (current != nullptr) {
		if (current->frequency > maxFrequency)
			maxFrequency = current->frequency;
		current = current->next;
	}
	int place = 1;

	while (maxFrequency / place > 0) {
		WordNode* outputList[10] = { nullptr };
		WordNode* tails[10] = { nullptr };

		current = list.head;

		while (current != nullptr) {
			int digit = (current->frequency / place) % 10;

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

		newTail->next = nullptr;
		list.head = newHead;
		list.tail = newTail;  // Update the tail pointer

		place *= 10;
	}

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Radix Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}

void Sorting::bubbleSort(WordList& list) {
	auto start = high_resolution_clock::now();
	if (list.head == nullptr) return;

	WordNode* current;
	WordNode* previous = nullptr;
	bool swapped;

	do {
		swapped = false;
		current = list.head;

		while (current->next != previous) {
			if (current->frequency > current->next->frequency) {
				swap(current->word, current->next->word);
				swap(current->frequency, current->next->frequency);
				swapped = true;
			}
			current = current->next;
		}
		previous = current;
	} while (swapped);

	// Update the tail
	WordNode* newTail = list.head;
	while (newTail && newTail->next) {
		newTail = newTail->next;
	}
	list.tail = newTail;

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Bubble Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}

WordNode* Sorting::merge(WordNode* left, WordNode* right) {
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

WordNode* Sorting::mergeSort(WordList& list, WordNode* node) {
	if (!node || !node->next) return node;

	WordNode* mid = list.findMiddle(node);

	WordNode* left = mergeSort(list, node);
	WordNode* right = mergeSort(list, mid);

	return merge(left, right);
}

void Sorting::mergeSort(WordList& list) {
	auto start = high_resolution_clock::now();

	list.head = mergeSort(list, list.head);

	// Update the tail after merge sort
	WordNode* newTail = list.head;
	while (newTail && newTail->next) {
		newTail = newTail->next;
	}
	list.tail = newTail;

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Merge Sorting done! \n Time elapsed : " << elapsed << " microseconds. " << endl << string(70, '-') << endl;
}



//ALPHABETICALLY
void Sorting::selectionSortAlphabetically(WordList& list) {
	auto start = high_resolution_clock::now();
	WordNode* first = list.head;

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

	// Update the tail
	WordNode* newTail = list.head;
	while (newTail && newTail->next) {
		newTail = newTail->next;
	}
	list.tail = newTail;

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Selection Sorting done! \nTime elapsed : " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}

void Sorting::radixSortAlphabetically(WordList& list) {
	auto start = high_resolution_clock::now();

	if (list.head == nullptr || list.head->next == nullptr) return;

	// Find the maximum word length
	WordNode* current = list.head;
	int maxLength = current->word.length();
	while (current != nullptr) {
		if (current->word.length() > maxLength)
			maxLength = current->word.length();
		current = current->next;
	}

	for (int pos = maxLength - 1; pos >= 0; pos--) {
		WordNode* outputList[26] = { nullptr };
		WordNode* tails[26] = { nullptr };

		current = list.head;

		while (current != nullptr) {
			int charIndex = pos < current->word.length() ? (current->word[pos] - 'a') : -1;

			if (charIndex < 0 || charIndex >= 26) {
				charIndex = 0;
			}

			// Add node
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

		// Set last node's next to null
		newTail->next = nullptr;

		// Update the head and tail
		list.head = newHead;
		list.tail = newTail;
	}

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Radix Sorting done! \nTime elapsed: " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}

void Sorting::bubbleSortAlphabetically(WordList& list) {
	auto start = high_resolution_clock::now();

	if (list.head == nullptr) return;

	WordNode* current;
	WordNode* previous = nullptr;
	bool swapped;

	do {
		swapped = false;
		current = list.head;

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

	// Update the tail
	WordNode* newTail = list.head;
	while (newTail && newTail->next) {
		newTail = newTail->next;
	}
	list.tail = newTail;

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Bubble Sorting done! \nTime elapsed: " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}

WordNode* Sorting::mergeAlphabetically(WordNode* left, WordNode* right) {
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

WordNode* Sorting::mergeSortAlphabetically(WordList& list, WordNode* node) {
	if (!node || !node->next) return node;

	WordNode* mid = list.findMiddle(node);
	WordNode* left = mergeSortAlphabetically(list, node);   // Sort first half
	WordNode* right = mergeSortAlphabetically(list, mid);   // Sort second half

	return mergeAlphabetically(left, right);
}

void Sorting::mergeSortAlphabetically(WordList& list) {
	auto start = high_resolution_clock::now();

	list.head = mergeSortAlphabetically(list, list.head);

	// Update the tail after merge sort
	WordNode* newTail = list.head;
	while (newTail && newTail->next) {
		newTail = newTail->next;
	}
	list.tail = newTail;

	auto end = high_resolution_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start).count();
	cout << string(70, '-') << endl << "Alphabetical Merge Sorting done! \nTime elapsed : " << elapsed << " microseconds." << endl << string(70, '-') << endl;
}
