#include "ReviewLL.hpp"
#include "Sorting.hpp"
#include "Analysis.hpp"
#include "Interface.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

#define POSITIVE_TXT "positive-words.txt"
#define NEGATIVE_TXT "negative-words.txt"
#define ALLREVIEWS_CSV "tripadvisor_hotel_reviews.csv"
#define BIGREVIEWS_CSV "10000_reviews.csv"
#define MEDIUMREVIEWS_CSV "1000_reviews.csv"
#define SMALLREVIEWS_CSV "100_reviews.csv"

using namespace std;
int main() {
	//declare reviews, positive words, and negative words
	ReviewList reviewsList;
	WordList positiveWordList, negativeWordList;
	
	positiveWordList.readWord(POSITIVE_TXT, insertMethod::fromFront);
	negativeWordList.readWord(NEGATIVE_TXT, insertMethod::fromFront);
	system("cls");
	//
	Interface::selectSample(reviewsList, positiveWordList, negativeWordList);
	Interface::menu(reviewsList, positiveWordList, negativeWordList);

	return 0;
}