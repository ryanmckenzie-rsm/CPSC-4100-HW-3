/*
* *File: pa2.h
* */


#ifndef _PA2_H
#define _PA2_H


#include <iostream>
#include <vector>


using namespace std;


struct Node
{
	int data_;
	Node* left_;
	Node* right_;
};


class Prog2
{
public:
	static Node* createBalancedBst(const vector<int>& A);
	static vector<int> zigzagLevelTraversal(Node* root);
	static vector<int> levelTraversal(Node* root);
	static void mirror(Node* root);
	static Node* erase(Node* root, int val);
	static vector<int> convertNonIncreasingOrder(Node* root);
	static Node* predecessor(Node* root, Node* p);
	static int distance(Node* root, Node* p, Node* q);

private:
	static Node* createBalancedBst(const vector<int>& A, int left, int right);
	static void convertNonIncreasingOrder(vector<int>& A, Node* root);
	static Node* minimum(Node* root);
	static Node* maximum(Node* root);
	static int distance(Node* root, Node* p);
};


#endif