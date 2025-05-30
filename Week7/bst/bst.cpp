#include<iostream>
#include<vector>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};



NODE* createNode(int data) {
	NODE* newNode = new NODE();
	newNode->key = data;
	newNode->p_left = NULL;
	newNode->p_right = NULL;
	return newNode;
}

NODE* Search(NODE* pRoot, int x) {
	if (pRoot == NULL) {
		return NULL;
	}
	if (pRoot->key == x) {
		return pRoot;
	}
	NODE* leftResult = Search(pRoot->p_left, x);
	if (leftResult != NULL) {
		return leftResult;
	}
	return Search(pRoot->p_right, x);
}
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	if (x < pRoot->key) {
		Insert(pRoot->p_left, x);
	}
	else if (x >pRoot->key)		 {
		Insert(pRoot->p_right, x);
	}	
}
void Remove(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		return;
	}
	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_left == NULL) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_right;
			delete temp;
		}
		else if (pRoot->p_right == NULL) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_left;
			delete temp;
		}
		else {
			NODE* minNode = pRoot->p_right;
			while (minNode->p_left != NULL) {
				minNode = minNode->p_left;
			}
			pRoot->key = minNode->key;
			Remove(pRoot->p_right, minNode->key);
		}
	}
}
NODE* createTree(int a[], int n) {
	NODE* pRoot = NULL;
	for (int i = 0; i < n; i++) {
		Insert(pRoot, a[i]);
	}
	return pRoot;
}
void removeTree(NODE*& pRoot) {
	if (pRoot == NULL) {
		return;
	}
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = NULL;
}
int Height(NODE* pRoot) {
	if (pRoot == NULL) {
		return 0;
	}
	int leftHeight = Height(pRoot->p_left);
	int rightHeight = Height(pRoot->p_right);
	return max(leftHeight, rightHeight) + 1; 
}
int countLess(NODE* pRoot, int x) {
	if (pRoot == NULL) {
		return 0;
	}
	int count = 0;
	if (pRoot->key < x) {
		count = 1;
	}
	return count + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}
int countGreater(NODE* pRoot, int x) {
	if (pRoot == NULL) {
		return 0;
	}
	int count = 0;
	if (pRoot->key > x) {
		count = 1;
	}
	return count + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}
bool isBST(NODE* pRoot) {
	if (pRoot == NULL) {
		return true;
	}
	if (pRoot->p_left != NULL && pRoot->p_left->key >= pRoot->key) {
		return false;
	}
	if (pRoot->p_right != NULL && pRoot->p_right->key <= pRoot->key) {
		return false;
	}
	return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}
bool isFullBST(NODE* pRoot) {
	if (pRoot == NULL) {
		return true;
	}
	if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
		return true;
	}
	if (pRoot->p_left != NULL && pRoot->p_right != NULL) {
		return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
	}
	return false;
}