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
	Node(string review, int rating);
	Node(string word);
 };


//Linked List class, 
class LinkedList {
private:
	Node* head;

public:
	LinkedList();
	void addNode(string review, int rating);
	void printList(int amount);

	void addNode(string word);
	void printWords(int amount);

	int countTotal();
	bool contains(const string& word);
	string selectReview(int index);
	int selectRating(int index);

	~LinkedList();
};

void sentimentAnalysis(LinkedList& reviews, LinkedList& good, LinkedList& bad, const string& review);
//reading CSV function
void readCSV(LinkedList& llist, const string& file);
void readWords(LinkedList& llist, const string& file);

#endif