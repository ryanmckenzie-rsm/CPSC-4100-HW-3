#include "pa2.h"
#include <fstream>
#include <map>
#include <cmath>
#include <cstdlib>
#include <set>
#include <cassert>

Node* search(Node* root, int val) {
	if (!root)
		return NULL;
	if (root->data_ == val)
		return root;
	if (val < root->data_)
		return search(root->left_, val);
	return search(root->right_, val); 
}

bool recurs(Node* p, int& h) {
	if (!p) {
		h = -1;
		return true;
	}
	int hl, hr;
	bool ok = (recurs(p->left_, hl) && recurs(p->right_, hr));
	if (ok) {
		ok &= (abs(hl-hr) <= 1);
		h = 1 + max(hl, hr);
	}
	return ok;
}

bool isBalanced(Node* root) {
    if (!root)
        return true;
    int h1, h2;
    return (recurs(root->left_, h1) && recurs(root->right_, h2) && abs(h1-h2) < 2);
}

bool isBstHelper(Node* root, Node*& prev) {
	if (!root)
		return true;
	bool ok = isBstHelper(root->left_, prev);
	ok &= (!prev || root->data_ >= prev->data_);
	prev = root;
	return ok && isBstHelper(root->right_, prev);
}

bool isBST(Node* root) {
	Node* prev = NULL;
	return isBstHelper(root, prev);
}

void killTree(Node* root) {
	if (root) {
		killTree(root->left_);
		killTree(root->right_);
		delete root;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " [data.in] [validate_file] <function_mask_string>" << endl;
		return -1;  
	}
	ifstream fin(argv[1]);
	ifstream fvin(argv[2]);
	string mask(8, '1');
    if (argc == 4)
		mask = string(argv[3]);
    string func[] = {"createBalancedBst", "levelTraversal", "zigzagLevelTraversal", "distance", 
              "predecessor", "convertNonIncreasingOrder", "mirror", "erase"}; 
	map<int, int> passed;
	int N;
	fin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		fin >> n;
		cout << "Case #" << (i+1) << "......\n";
		vector<int> A(n), VB(n);
		for (int j = 0; j < n; j++) {
			fin >> A[j];
			fvin >> VB[j];
		}

		int id = 0;
		Node* root = Prog2::createBalancedBst(A); //this function must be called for any testing
		if (mask[id] == '1' && isBalanced(root))
			passed[id]++;
		id++;
			 		

		vector<int> B;
		if (mask[id] == '1')
			B = Prog2::levelTraversal(root);
		
        //validate
        if (mask[id] == '1' && B == VB) {
			passed[id]++;
		}
		id++;
		
		for (int j = 0; j < n; j++)
			fvin >> VB[j];
		if (mask[id] == '1')
			B = Prog2::zigzagLevelTraversal(root);
		
        //validate
        if (mask[id] == '1' && B == VB)
			passed[id]++;
		id++;

		set<int> S(A.begin(), A.end());
		int m;
		fvin >> m;
		bool ok = true;
		for (int k = 0; k < m; k++) {
			int x, y, z;
			fvin >> x >> y >> z;
			Node* px = search(root, x);
			Node* py = search(root, y);
			if (mask[id] == '1')
				ok &= (Prog2::distance(root, px, py) == z);
		}
		if (mask[id] == '1' && ok)
			passed[id]++;
		id++;


		ok = true;
		if (mask[id] == '1')
		for (int k = 0; k < m; k++) {
			int x = A[rand() % (int)A.size()];
            Node* p = search(root, x);
            assert(p);
			Node* q = Prog2::predecessor(root, p);
			set<int>::iterator it = S.lower_bound(x);
			ok &= ((it == S.begin() && !q)||(*(--it) == q->data_));
        }
        if (mask[id] == '1' && ok)
            passed[id]++;
        id++;
		if (mask[id] == '1') {
	    	B = Prog2::convertNonIncreasingOrder(root);
			ok = true;
			for (int t = 0; t < (int)B.size() - 1; t++)
				ok &= (B[t] >= B[t+1]);
        }
		if (mask[id] == '1' && ok)
            passed[id]++;
        id++;
		if (mask[id] == '1')
			for (int t = 0; t < 2; t++)
				Prog2::mirror(root);
		if (mask[id] == '1' && isBST(root) && isBalanced(root))
			passed[id]++;
		id++;
		if (mask[id] == '1') {
			m = min(5, (int)A.size());
        	for (int t = 0; t < m; t++) {
				int j = t + rand() % (A.size() - t);
				swap(A[j], A[t]);
			}
			ok = true;
			for (int t = 0; t < m; t++)	{
				root = Prog2::erase(root, A[t]);
				ok &= !search(root, A[t]);
			}
		}
		if (mask[id] == '1' && ok)
            passed[id]++;
		killTree(root);
	}
	
	fin.close();
	fvin.close();
	cout << "/////////////////////// Summary of Execution ////////////////////////////////\n";
	for (int i = 0; i < sizeof(func)/sizeof(string); i++) {
		cout << func[i] << ":   " << passed[i] << "/" << N << " passed" << endl;
	}
	cout << endl;
	return 0;
}
