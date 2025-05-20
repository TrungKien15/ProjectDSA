#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};
void printTree(NODE* pRoot) {
	if (pRoot == NULL) {
		return;
	}
	
	printTree(pRoot->p_left);
	cout << pRoot->key << " "<<pRoot->height<<" ";
	printTree(pRoot->p_right);
}
NODE* createNode(int data) {
	NODE* newNode = new NODE();
	newNode->key = data;
	newNode->p_left = NULL;
	newNode->p_right = NULL;
	newNode->height = 0;
	return newNode;
}
void heightUpdate(NODE* &pRoot) {
	if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
		pRoot->height = 0;
		return ;
	}
	else if (pRoot->p_left == NULL) {
		heightUpdate(pRoot->p_right);
		pRoot->height = pRoot->p_right->height + 1;

	}
	else if (pRoot->p_right == NULL) {
		heightUpdate(pRoot->p_left);
		pRoot->height = pRoot->p_left->height + 1;
	}
	else {
		heightUpdate(pRoot->p_left);
		heightUpdate(pRoot->p_right);
		int height = max(pRoot->p_left->height, pRoot->p_right->height);
		pRoot->height = height + 1;
	}
}	
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	if (x < pRoot->key) {
		Insert(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Insert(pRoot->p_right, x);
	}
	else {
		return;
	}
	heightUpdate(pRoot);
	
	int balance;
	if (pRoot->p_left != NULL && pRoot->p_right != NULL) {
		balance = pRoot->p_left->height - pRoot->p_right->height;
	}
	else if (pRoot->p_left != NULL) {
		balance = pRoot->p_left->height + 1;
	}
	else if (pRoot->p_right != NULL) {
		balance = -1 * (pRoot->p_right->height + 1);
	}
	else {
		balance = 0;
	}
	if (balance > 1) {
		if (x < pRoot->p_left->key) {
			// Left Left 
			NODE* temp = pRoot->p_left;
			pRoot->p_left = temp->p_right;
			temp->p_right = pRoot;
			pRoot = temp;
		}
		else {
			// Left Right 
			NODE* temp = pRoot->p_left->p_right;
			pRoot->p_left->p_right = temp->p_left;
			temp->p_left = pRoot->p_left;
			pRoot->p_left = temp->p_right;
			temp->p_right = pRoot;
			pRoot = temp;
		}
	}
	else if (balance < -1) {
		if (x > pRoot->p_right->key) {
			// Right Right 
			NODE* temp = pRoot->p_right;
			pRoot->p_right = temp->p_left;
			temp->p_left = pRoot;
			pRoot = temp;
		}
		else {
			// Right Left	
			NODE* temp = pRoot->p_right->p_left;
			pRoot->p_right->p_left = temp->p_right;
			temp->p_right = pRoot->p_right;
			pRoot->p_right = temp->p_left;
			temp->p_left = pRoot;
			pRoot = temp;
		}
	}
	heightUpdate(pRoot);
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
		if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
			delete pRoot;
			pRoot = NULL;
		}
		else if (pRoot->p_left == NULL) {
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
			NODE* temp = pRoot->p_right;
			while (temp->p_left != NULL) {
				temp = temp->p_left;
			}
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);

		}	
	}
	if (pRoot == NULL) {
		return;
	}
	heightUpdate(pRoot);
	int balance;
	if (pRoot->p_left != NULL && pRoot->p_right != NULL) {
		balance = pRoot->p_left->height - pRoot->p_right->height;
	}
	else if (pRoot->p_left != NULL) {
		balance = pRoot->p_left->height + 1;
	}
	else if (pRoot->p_right != NULL) {
		balance = -1 * (pRoot->p_right->height + 1);
	}
	else {
		balance = 0;
	}
	if (balance > 1) {
		NODE* p = pRoot->p_left; 
		int leftHeight=-1;
		if (p->p_left != NULL) {
			leftHeight = p->p_left->height;
		}
		int rightHeight=-1;
		if (p->p_right != NULL) {
			rightHeight = p->height;
		}
		if (leftHeight>=rightHeight) {
			
			// Left Left Case
			NODE* temp = pRoot->p_left;
			pRoot->p_left = temp->p_right;
			temp->p_right = pRoot;
			pRoot = temp;
		}
		else {
			
			// Left Right Case
			NODE* temp = pRoot->p_left->p_right;
			pRoot->p_left->p_right = temp->p_left;
			temp->p_left = pRoot->p_left;
			pRoot->p_left = temp->p_right;
			temp->p_right = pRoot;
			pRoot = temp;
		}
	}
	else if (balance < -1) {
		NODE* p = pRoot->p_right;
		int leftHeight = -1;
		if (p->p_left != NULL) {
			leftHeight = p->p_left->height;
		}
		int rightHeight = -1;
		if (p->p_right != NULL) {
			rightHeight = p->height;
		}
		if (rightHeight >= leftHeight) {
			// Right Right Case
			
			NODE* temp = pRoot->p_right;
			pRoot->p_right = temp->p_left;
			temp->p_left = pRoot;
			pRoot = temp;
		}
		else {
			// Right Left Case
			;
			NODE* temp = pRoot->p_right->p_left;
			pRoot->p_right->p_left = temp->p_right;
			temp->p_right = pRoot->p_right;
			pRoot->p_right = temp->p_left;
			temp->p_left = pRoot;
			pRoot = temp;
		}
	}
	heightUpdate(pRoot);
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
bool isAVL(NODE* pRoot) {
	if (pRoot == NULL) {
		return true;
	}
	if (pRoot->p_left == NULL && pRoot->p_right != NULL) {
		if (pRoot->p_right->height == 0) {
			return true;
		}
		return false;
	}
	else if (pRoot->p_right == NULL && pRoot->p_left != NULL) {
		if (pRoot->p_left->height == 0) {
			return true;
		}
		return false;
	}
	else if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
		return true;
	}
	else {
		return isAVL(pRoot->p_left) && isAVL(pRoot->p_right) && isBST(pRoot) ;
	}
}
