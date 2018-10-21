#include "pa2.h"

#include <vector>  // vector
#include <queue>  // queue
#include <stack>  // stack
#include <utility>  // swap


using namespace std;


// T(n) = 2T(n/2) + 1
// O(n*log(n))
Node* Prog2::createBalancedBst(const vector<int>& A)
{
	return createBalancedBst(A, 0, A.size() - 1);
}


vector<int> Prog2::zigzagLevelTraversal(Node* root)
{
	stack<Node*> current;
	if (root) {
		current.push(root);
	}
	stack<Node*> next;
	vector<int> v;
	bool rightToLeft = true;
	while (!current.empty()) {
		root = current.top();
		current.pop();
		v.push_back(root->data_);

		if (rightToLeft) {
			if (root->left_) {
				next.push(root->left_);
			}
			if (root->right_) {
				next.push(root->right_);
			}
		} else {
			if (root->right_) {
				next.push(root->right_);
			}
			if (root->left_) {
				next.push(root->left_);
			}
		}

		if (current.empty()) {
			rightToLeft = !rightToLeft;
			swap(current, next);
		}
	}

	return v;
}


vector<int> Prog2::levelTraversal(Node* root)
{
	queue<Node*> q;
	if (root) {
		q.push(root);
	}
	vector<int> v;
	while (!q.empty()) {
		root = q.front();
		q.pop();
		v.push_back(root->data_);
		if (root->left_) {
			q.push(root->left_);
		}
		if (root->right_) {
			q.push(root->right_);
		}
	}
	return v;
}


// T(n) = 2T(n/2) + 1
// O(n*log(n))
void Prog2::mirror(Node* root)
{
	if (root) {
		swap(root->left_, root->right_);  // basic operation
		mirror(root->left_);
		mirror(root->right_);
	}
}


Node* Prog2::erase(Node* root, int val)
{
	if (!root) {
		return 0;
	} else {
		if (val < root->data_) {
			root->left_ = erase(root->left_, val);
		} else if (val > root->data_) {
			root->right_ = erase(root->right_, val);
		} else {
			if (!root->left_) {
				Node* tmp = root->right_;
				delete root;
				return tmp;
			} else if (!root->right_) {
				Node* tmp = root->left_;
				delete root;
				return tmp;
			} else {
				Node* tmp = minimum(root->right_);
				root->data_ = tmp->data_;
				root->right_ = erase(root->right_, tmp->data_);
			}
		}
	}
	return root;
}


// T(n) = 2T(n/2) + 1
// O(n*log(n))
vector<int> Prog2::convertNonIncreasingOrder(Node* root)
{
	vector<int> A;
	if (root) {
		convertNonIncreasingOrder(A, root);
	}
	return A;
}


Node* Prog2::predecessor(Node* root, Node* p)
{
	if (!root || !p) {
		return 0;
	} else if (p->left_) {
		return maximum(p->left_);
	} else {
		Node* predecessor = 0;
		while (root && root != p) {
			if (p->data_ > root->data_) {
				predecessor = root;
				root = root->right_;
			} else {
				root = root->left_;
			}
		}
		return predecessor;
	}
}


int Prog2::distance(Node* root, Node* p, Node* q)
{
	if (!root || !p || !q) {
		return 0;
	} else if (p == root) {
		return distance(p, q);
	} else if (q == root) {
		return distance(q, p);
	} else if ((p->data_ < root->data_) != (q->data_ < root->data_)) {  // logical xor, returns true when they're in separate trees
		return distance(root, p) + distance(root, q);
	} else {
		if ((p->data_ < root->data_) && (q->data_ < root->data_)) {
			return distance(root->left_, p, q);
		} else {
			return distance(root->right_, p, q);
		}
	}
}


int Prog2::distance(Node* root, Node* p)
{
	int dist = 0;
	while (root && root != p) {
		if (p->data_ <= root->data_) {
			root = root->left_;
		} else {
			root = root->right_;
		}
		++dist;
	}
	return dist;
}


void Prog2::convertNonIncreasingOrder(vector<int>& A, Node* root)
{
	if (root->right_) {
		convertNonIncreasingOrder(A, root->right_);
	}
	A.push_back(root->data_);  // basic operation
	if (root->left_) {
		convertNonIncreasingOrder(A, root->left_);
	}
}


Node* Prog2::createBalancedBst(const vector<int>& A, int left, int right)
{
	int mid = left + (right - left) / 2;
	Node* node = new Node;
	node->data_ = A[mid];  // basic operation
	node->left_ = (mid - left > 0) ? createBalancedBst(A, left, mid - 1) : 0;
	node->right_ = (right - mid > 0) ? createBalancedBst(A, mid + 1, right) : 0;
	return node;
}


Node* Prog2::minimum(Node* root)
{
	while (root->left_) {
		root = root->left_;
	}
	return root;
}


Node* Prog2::maximum(Node* root)
{
	while (root->right_) {
		root = root->right_;
	}
	return root;
}