#include "Interface.hpp"
#include "WordLL.hpp"
#include "ReviewLL.hpp"
#include "Sorting.hpp"
#include "Analysis.hpp"

#include <iostream>
#include <iomanip>
#include <limits>

int option = -1;

bool Interface::checkIsInt() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cout << "Invalid input. Please enter a number. \n\n";
		option = -1;
		return false;
	}
	return true;
}

void Interface::selectSample(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList) {
	do {
		cout << "Please select sample size: " << endl << string(70, '-') << endl;
		cout << "1. TripAdvisor Hotel Reviews (20,491 reviews)" << endl;
		cout << "2. TripAdvisor Hotel Reviews (10,000 reviews)" << endl;
		cout << "3. TripAdvisor Hotel Reviews (1,000 reviews)" << endl;
		cout << "4. TripAdvisor Hotel Reviews (100 reviews)" << endl;
		cout << "0. Exit" << endl;

		cout << "Select option: ";
		cin >> option;
		system("cls");
		if (checkIsInt()) {
			switch (option) {
			case 0:
				exit(0);
			case 1:
				cout << "Loading 20,492 reviews.... (it would take around 10 minutes)" << endl;
				reviewsList.readCSV("tripadvisor_hotel_reviews.csv", positiveWordList, negativeWordList);
				break;
			case 2:
				cout << "Loading 10,000 reviews.... (it would take around 5 minutes)" << endl;
				reviewsList.readCSV("10000_reviews.csv", positiveWordList, negativeWordList);
				break;
			case 3:
				cout << "Loading 1,000 reviews.... (it would take around 20 seconds)" << endl;
				reviewsList.readCSV("1000_reviews.csv", positiveWordList, negativeWordList);
				break;
			case 4:
				cout << "Loading 100 reviews.... (it would take around 3 seconds)" << endl;
				reviewsList.readCSV("100_reviews.csv", positiveWordList, negativeWordList);
				break;
			default:
				cout << "Invalid option, please select again" << endl;
				break;
			}
		}

	} while (option < 0 || option > 4);
}

void Interface::menu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList) {
	do {
		option = -1;
		cout << "Please select an option: " << endl
			<< string(70, '-') << endl << "All Functions" << endl << string(70, '-') << endl
			<< "1. Analysis Functions" << endl
			<< "2. Review Functions" << endl
			<< "3. Word Functions" << endl
			<< "0. Exit" << endl;

		cout << string(70, '-') << endl << "Your option: ";
		cin >> option;

		system("cls");
		if (checkIsInt()) {
			switch (option) {
			case 0:
				exit(0);
			case 1:
				analysisMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 2:
				reviewMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 3:
				wordMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			default:
				system("cls");
				cout << "Invalid option, please select again" << endl;
				break;
			}
		}

	} while (option < 0 || option > 3);
}

void Interface::analysisMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList) {
	system("cls");
	do {
		option = -1;
		cout << "Please select an option: " << endl
			<< string(70, '-') << endl << "Analysis Functions Menu" << endl << string(70, '-') << endl
			<< "1. Sentiment Analysis" << endl
			<< "2. Comparison Analysis" << endl
			<< "3. Summary" << endl
			<< "4. Sentiment Summary" << endl
			<< "5. Back to menu" << endl
			<< "0. Exit" << endl;

		cout << string(70, '-') << endl << "Your option: ";
		cin >> option;

		int index;
		if (checkIsInt()) {
			switch (option) {
			case 0:
				exit(0);
			case 1:
				system("cls");
				cout << "Input an index: ";
				cin >> index;
				if (!checkIsInt()) {
					break;
				}
				Analysis::sentimentAnalysis(reviewsList.selectReview(index));
				system("pause");
				analysisMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 2:
				system("cls");
				cout << "Input an index: ";
				cin >> index;
				if (!checkIsInt()) {
					break;
				}
				Analysis::comparison(reviewsList.selectReview(index));
				system("pause");
				analysisMenu(reviewsList, positiveWordList, negativeWordList);
				break;

			case 3:
				//Sorted by default
				Sorting::radixSort(positiveWordList);
				Sorting::radixSort(negativeWordList);
				Analysis::summary(reviewsList, positiveWordList, negativeWordList);
				system("pause");
				analysisMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 4:
				system("cls");
				Analysis::sentimentSummary(reviewsList);
				system("pause");
				analysisMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 5:
				system("cls");
				menu(reviewsList, positiveWordList, negativeWordList);
				break;
			default:
				system("cls");
				cout << "Invalid option, please select again" << endl;
				break;
			}
		}

	} while (option < 0 || option > 5);
}

void Interface::reviewMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList) {
	system("cls");
	do {
		option = -1;
		cout << "Please select an option: " << endl
			<< string(70, '-') << endl << "Review Functions Menu" << endl << string(70, '-') << endl
			<< "1. Print Reviews" << endl
			<< "2. Search Relevant Review" << endl
			<< "3. Back to menu" << endl
			<< "0. Exit" << endl;

		cout << string(70, '-') << endl << "Your option: ";
		cin >> option;

		system("cls");
		if (checkIsInt()) {
			int amount;
			string word;
			switch (option) {
			case 0:
				exit(0);
			case 1:
				system("cls");
				cout << "Input an amount (type 0 to print all reviews): ";
				cin >> amount;
				if (checkIsInt()) {
					if (amount == 0) {
						reviewsList.print(reviewsList.countTotal());
					}
					else if (reviewsList.countTotal() < amount) {
						cout << "amount is out of list's size" << endl;
					}
					else if (amount > 0) {
						reviewsList.print(amount);
					}
					else {
						cout << "invalid input" << endl;
					}
				}
				system("pause");
				reviewMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 2:
				system("cls");
				cout << "Enter keyword: ";
				cin >> word;
				word = trimming::trim(word);
				reviewsList.searchRelevant(word);
				system("pause");
				reviewMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 3:
				system("cls");
				menu(reviewsList, positiveWordList, negativeWordList);
				break;
			default:
				system("cls");
				cout << "Invalid option, please select again" << endl;
				break;
			}
		}
		} while (option < 0 || option > 3);
}

void Interface::wordMenu(ReviewList& reviewsList, WordList& positiveWordList, WordList& negativeWordList) {
	system("cls");
	do {
		option = -1;
		cout << "Please select an option: " << endl
			<< string(70, '-') << endl << "Word Functions Menu" << endl << string(70, '-') << endl
			<< "1. Print Words and Frequencies" << endl
			<< "2. Search Word" << endl
			<< "3. Back to menu" << endl
			<< "0. Exit" << endl;

		cout << string(70, '-') << endl << "Your option: ";
		cin >> option;

		if (checkIsInt()) {
			int choice = -1;
			string word;
			switch (option) {
			case 0:
				exit(0);
			case 1:
				do {
					system("cls");
					cout << "Please select an option: " << endl
						<< "1. Print good words" << endl
						<< "2. Print bad words" << endl
						<< "0. Back to menu" << endl;

					cin >> choice;
					if (checkIsInt()) {
						switch (choice) {
						case 0:
							wordMenu(reviewsList, positiveWordList, negativeWordList);
							break;
						case 1:
							Sorting::radixSort(positiveWordList);
							positiveWordList.printWordsAndFrequency();
							break;
						case 2:
							Sorting::radixSort(negativeWordList);
							negativeWordList.printWordsAndFrequency();
							break;
						}
					}
				} while (choice < 0 || choice > 2);
				system("pause");
				wordMenu(reviewsList, positiveWordList, negativeWordList);
				break;
			case 2:
				word = "";
				system("cls");
				do {
					system("cls");
					cout << "Please select an option: " << endl
						<< "1. Search good words" << endl
						<< "2. Search bad words" << endl
						<< "0. Back to word menu" << endl
						<< "Your option: ";
					cin >> choice;
					if (checkIsInt()) {
						switch (choice) {
						case 0:
							wordMenu(reviewsList, positiveWordList, negativeWordList);
							break;
						case 1:
							cout << "Enter keyword: ";
							cin >> word;
							Sorting::radixSortAlphabetically(positiveWordList);
							word = trimming::trim(word);
							positiveWordList.linearSearch(word);
							system("pause");
							wordMenu(reviewsList, positiveWordList, negativeWordList);
							break;
						case 2:
							cout << "Enter keyword: ";
							cin >> word;
							Sorting::radixSortAlphabetically(negativeWordList);
							word = trimming::trim(word);
							negativeWordList.linearSearch(word);
							system("pause");
							wordMenu(reviewsList, positiveWordList, negativeWordList);
							break;
						}
					}
				} while (choice < 0 || choice > 2);
				break;
			case 3:
				system("cls");
				menu(reviewsList, positiveWordList, negativeWordList);
				break;
			default:
				system("cls");
				cout << "Invalid option, please select again" << endl;
				break;
			}
		}
	} while (option < 0 || option > 3);
}
