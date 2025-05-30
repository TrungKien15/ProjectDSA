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
vector<int> NLR(NODE* pRoot) {
	vector<int> result;
	if (pRoot == NULL) {
		return result;
	}
	result.push_back(pRoot->key);
	vector<int> left = NLR(pRoot->p_left);
	vector<int> right = NLR(pRoot->p_right);
	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());
	return result;
}
vector<int> LNR(NODE* pRoot) {
	vector<int> result;
	if (pRoot == NULL) {
		return result;
	}
	vector<int> left = LNR(pRoot->p_left);
	result.insert(result.end(), left.begin(), left.end());
	result.push_back(pRoot->key);
	vector<int> right = LNR(pRoot->p_right);
	result.insert(result.end(), right.begin(), right.end());
	return result;
}
vector<int> LRN(NODE* pRoot) {
	vector<int> result;
	if (pRoot == NULL) {
		return result;
	}
	vector<int> left = LRN(pRoot->p_left);
	vector<int> right = LRN(pRoot->p_right);
	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());
	result.push_back(pRoot->key);
	return result;
}
vector<vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> result;
	if (pRoot == NULL) {
		return result;
	}
	vector<NODE*> current;
	current.push_back(pRoot);
	while (!current.empty()) {
		vector<int> Values;
		vector<NODE*> next;
		for (NODE* node : current) {
			Values.push_back(node->key);
			if (node->p_left != NULL) {
				next.push_back(node->p_left);
			}
			if (node->p_right != NULL) {
				next.push_back(node->p_right);
			}
		}
		result.push_back(Values);
		current = next;
	}
	return result;
}

int countNode(NODE* pRoot) {
	if (pRoot == NULL) {
		return 0;
	}
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
int sumNode(NODE* pRoot) {
	if (pRoot == NULL) {
		return 0;
	}
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
int heightNode(NODE* pRoot, int value) {
	if (pRoot == NULL) {
		return -1;
	}
	if (pRoot->key == value) {
		return 0;
	}
	int left = heightNode(pRoot->p_left, value);
	int right = heightNode(pRoot->p_right, value);
	if (left != -1) {
		return left + 1;
	}
	if (right != -1) {
		return right + 1;
	}
	return -1;
}
int Level(NODE* pRoot, NODE* p) {
	if (pRoot == NULL) {
		return -1;
	}
	if (pRoot == p) {
		return 0;
	}
	int leftLevel = Level(pRoot->p_left, p);
	int rightLevel = Level(pRoot->p_right, p);
	if (leftLevel != -1) {
		return leftLevel + 1;
	}
	if (rightLevel != -1) {
		return rightLevel + 1;
	}
	return -1;
}
int countLeaf(NODE* pRoot) {
	if (pRoot == NULL) {
		return 0;
	}
	if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
		return 1;
	}
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}