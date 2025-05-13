#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

Stack* initializeStack();
void push(Stack& s, int key);
int pop(Stack& s);
int size(Stack s);
bool isEmpty(Stack s);

Stack* initializeStack() {
	Stack* s = new Stack;
	s->top = nullptr;
	return s;
}
void push(Stack& s, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = s.top;
	s.top = newNode;

}
int pop(Stack& s) {
	if (s.top == nullptr) {
		return -1;
	}
	NODE* temp = s.top;
	int first = temp->key;
	s.top = s.top->p_next;
	delete temp;
	return first;
}

int size(Stack s) {
	int count = 0;
	NODE* temp = s.top;
	while (temp != nullptr) {
		count++;
		temp = temp->p_next;
	}
	return count;
}
bool isEmpty(Stack s) {
	return s.top == nullptr;
}
void stackToText(Stack& s, ofstream& ofs) {
	if (isEmpty(s)) {
		ofs << "EMPTY" << endl;
	}
	else {
		NODE* temp = s.top;
		while (temp != nullptr) {
			ofs << temp->key << " ";
			temp = temp->p_next;
		}
		ofs << endl;
	}
}
void perform(char path1[], char path2[]) {
	ifstream ifs(path1);
	while (ifs.is_open() == false) {
		cout << "Cannot open the input file" << endl;
		return;
	}
	ofstream ofs(path2);
	while (ofs.is_open() == false) {
		cout << "Cannot open the output file" << endl;
		return;
	}
	Stack* s = initializeStack();
	string function;
	while (ifs>>function) {
		if (function == "init") {
			if (s != nullptr) {
				delete s;
			}
			s = initializeStack();
			ofs << "EMPTY" << endl;
		}
		else if (function == "push") {
			int key;
			ifs >> key;
			ifs.ignore();
			push(*s, key);
			stackToText(*s, ofs);
		}
		else if (function == "pop") {
			pop(*s);
			stackToText(*s, ofs);
		}
	}
	if (s != nullptr) {
		delete s;
	}
}
int main() {
	char path1[] = "input.txt";
	char path2[] = "output.txt";
	perform(path1, path2);
	return 0;
}
