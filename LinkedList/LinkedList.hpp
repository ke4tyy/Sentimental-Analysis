#pragma once

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>

using namespace std;

//Explanation: Struct, grouping variables as members of a structure
struct Node {
	string review, word;
	int rating;
	Node* next; //pointer location

	//declaring constructor
	Node(string review, int rating = -1);
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

	void print(int amount, bool wordOrNot);

	int countTotal();
	bool contains(const string& word);
	string selectReview(int index);
	int selectRating(int index);

	void sentimentAnalysis(LinkedList& good, LinkedList& bad, const string& review);
	//reading CSV function
	void readCSV(LinkedList& llist, const string& file);
	void readWords(LinkedList& llist, const string& file);
	~LinkedList();
};



#endif