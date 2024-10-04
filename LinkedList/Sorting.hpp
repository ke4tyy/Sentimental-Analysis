#pragma once
#ifndef SORTING_HPP
#define SORTING_HPP

#include <string>

#include "WordLL.hpp"

namespace Sorting {
	//SORTING BY FREQUENCY
	void selectionSort(WordList& list); //selection sort by frequency
	void radixSort(WordList& list); //radix sort by frequency
	void bubbleSort(WordList& list); //bubble sort by frequency

	//merge sort code
	WordNode* merge(WordNode* left, WordNode* right);  //merge
	WordNode* mergeSort(WordList& list, WordNode* node);
	void mergeSort(WordList& list);


	//SORTING BY ALPHABET
	void selectionSortAlphabetically(WordList& list); //selection sort by alphabet
	void radixSortAlphabetically(WordList& list); //radix sort by alphabet
	void bubbleSortAlphabetically(WordList& list); //bubble sort by alphabet

	//merge sort code
	WordNode* mergeAlphabetically(WordNode* left, WordNode* right);
	WordNode* mergeSortAlphabetically(WordList& list, WordNode* node);
	void mergeSortAlphabetically(WordList& list);

}

#endif