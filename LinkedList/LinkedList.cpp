#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "LinkedList.hpp"

//default constructor 
Node::Node(string rev, int rat) {
	review = rev;
	rating = rat;
	next = nullptr; //first register as end before setting the next
}

Node::Node(string w) {
	word = w;
	next = nullptr;
}

//set head to null
LinkedList::LinkedList() {
	head = nullptr;
}

//assigning pointer location to the node
//concept explanation
void LinkedList::addNode(string rev, int rat) {
	Node* newNode = new Node(rev, rat); //create node
	if (head == nullptr) { //to add the first node
		head = newNode;
	}
	else { //else go to the end of the list to add new node
		Node* temp = head; //set header as temp
		while (temp -> next != nullptr) {
			temp = temp -> next;//go to next pointer if next pointer is not null
		}
		temp -> next = newNode; //new node on the last
	}
}

void LinkedList::addNode(string word) {
	Node* newNode = new Node(word);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* temp = head;
		while (temp -> next != nullptr) {
			temp = temp -> next;
		}
		temp -> next = newNode;
	}
}

//printing the reviews and rating based on the amount
void LinkedList::printList(int amount) {
	Node* temp = head;
	int count = 0;
	while (temp != nullptr && count < amount) {
		cout << string(100, '-') << endl;
		cout << "Review: \n" << temp->review << endl << endl << "Rating: " << temp->rating << endl;
		cout << string(100, '-') << endl;
		temp = temp -> next;
		count++;
	}
}

void LinkedList::printWords(int amount) {
	Node* temp = head;
	int count = 0;
	while (temp != nullptr && count < amount) {
		cout << temp -> word << endl;
		temp = temp -> next;
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


string trim(const string& str) {
	size_t first = str.find_first_not_of(' '); //find first word with no space
	size_t last = str.find_last_not_of(' '); //find last word with no space
	return str.substr(first, (last - first + 1)); //create substring
}

//reading CSV file
void readCSV(LinkedList& linkedList, const string& filepath) {
	ifstream file(filepath); //check if filepath is correct
	
	string line;

	if (file.is_open()) {
		getline(file, line); //skips header

		while (getline(file, line)) {
			size_t lastComma = line.find_last_of(','); //find the last comma, because in the csv file the last comma separates the rating

			string review = line.substr(0, lastComma); //takes everything before the last comma

			string ratingStr = line.substr(lastComma + 1); //take the rating, because rating length is always 1, so just + 1 to get the rating

			int rating = stoi(ratingStr); //convert rating to integer

			linkedList.addNode(review, rating); // add it into the linked list
		}
		file.close();
	}
	else {
		cerr << "Error opening file" << endl;
	}
}

void readWords(LinkedList& linkedList, const string& filepath) {
	ifstream file(filepath);

	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			string word = line;
			linkedList.addNode(word);
		}
		file.close();
	}
	else {
		cerr << "Error opening file" << endl;
	}
}


void sentimentAnalysis(LinkedList& reviews, LinkedList& good, LinkedList& bad, const string& review) {
	cout << review << endl;
	cout << fixed << setprecision(2);
	int goodCount = 0;
	int badCount = 0;

	istringstream iss(review);

	string word;

	while (iss >> word) {
		word = trim(word);
		if (good.contains(word)) {
			goodCount++;
		}
		else if (bad.contains(word)) {
			badCount++;
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
	cout << max << endl << min << endl << raw << endl << sentiment << endl;
	cout << "Positive Words = " << goodCount << endl;
	cout << "Negative Words = " << badCount << endl;
	cout << "Sentiment score (1-5) is " << sentiment << ", thus the rating should be equal to " << comp << "(" << rev <<")";
}