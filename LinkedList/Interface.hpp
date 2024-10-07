#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Interface.hpp"
#include "WordLL.hpp"
#include "ReviewLL.hpp"
#include "Sorting.hpp"
#include "Analysis.hpp"

#include <string>
namespace Interface {
	bool checkIsInt(); // checks if its integer or no

	//MAIN INTERFACE
	void selectSample(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList);

	void menu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList);

	void analysisMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList);

	void reviewMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList);

	void wordMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList);

	void comparisonMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList);

	//sub-interface
}

#endif