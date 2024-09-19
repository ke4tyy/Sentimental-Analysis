#pragma once

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>
using namespace std;

struct Node {
	string review, word;
	int rating, frequency;
	Node* next; //pointer location

	//declaring constructor
	Node(string review, int rating);
};

//Explanation: Struct, grouping variables as members of a structure
struct ReviewNode {
	string review;
	int rating;
	ReviewNode* next;
	ReviewNode(string review, int rating);
};

struct WordNode {
	string word;
	int frequency;
	WordNode* next;

	WordNode(string word);
};

class WordList {
private:
	WordNode* head;
	WordNode* tail;

public:
	WordList();
	WordNode* getHead();
	WordNode* getTail();
	void addWord(string word);
	void addFrequency(string word);
	bool searchWord(string word);
	void readWord(string path);
	~WordList();
};

class ReviewList {
private:
	ReviewNode* head;
	ReviewNode* tail;

public: 
	ReviewList();
	void addReview(string review, int rating);
	int countTotal();
	string selectReview(int index);

	void readCSV(string file);
	void print(int amount);
	string trim(string str);
	void updateFrequency(WordList& good, WordList& bads);
	void sentimentAnalysis(WordList good, WordList bad, const string& review);
	~ReviewList();
};


//Linked List class, 
class LinkedList {
private:
	Node* head;
	Node* tail;
	void addNode(Node* newNode);

public:
	LinkedList();
	int selectRating(int index);




	void selectionSortWordsAscending();
	void radixSortWordsAscending();
	void quickSortWordsAscending();

	Node* recursionList(Node* currentNode, Node* previousNode = nullptr);
	void reverseList();

	//reading CSV function
	~LinkedList();
};

#endif