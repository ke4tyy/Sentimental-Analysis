#pragma once

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>

using namespace std;

//Explanation: Struct, grouping variables as members of a structure
struct Node {
	string review, word;
	int rating, frequency;
	Node* next; //pointer location

	//declaring constructor
	Node(string review, int rating);
 };

//Linked List class, 
class LinkedList {
private:
	Node* head;
	Node* tail;
	void addNode(Node* newNode);

public:
	LinkedList();
	void addReview(string review, int rating);
	void addWord(string word);
	void addWordAndFreq(string word);

	void print(int amount, int choice);
	int countTotal();
	bool contains(const string& word);
	string selectReview(int index);
	int selectRating(int index);


	void storeFreq(LinkedList& good, LinkedList& bad, LinkedList& reviews, LinkedList& words);


	void selectionSortWordsAscending();
	void radixSortWordsAscending();
	void quickSortWordsAscending();

	Node* recursionList(Node* currentNode, Node* previousNode = nullptr);
	void reverseList();
	void sentimentAnalysis(LinkedList& good, LinkedList& bad, const string& review);
	//reading CSV function
	void readCSV(LinkedList& llist, const string& file);
	void readWords(LinkedList& llist, const string& file);
	~LinkedList();
};



#endif