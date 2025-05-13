#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Queue {
	NODE* head;
	NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue& q, int key);
int dequeue(Queue& q);
int size(Queue q);
bool isEmpty(Queue q);

Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = q->tail = nullptr;
	return q;
}

int dequeue(Queue& q) {
	if (q.head == nullptr) {
		return -1;
	}
	NODE* temp = q.head;
	int value = temp->key;
	q.head = q.head->p_next;

	if (q.head == nullptr) {
		q.tail = nullptr;
	}
	delete temp;
	return value;
}	

void enqueue(Queue& q, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = nullptr;

	if (q.tail == nullptr) {
		q.head = q.tail = newNode;
	}
	else {
		q.tail->p_next = newNode;
		q.tail = newNode;
	}
}

int size(Queue q) {
	int count = 0;
	NODE* temp = q.head;
	while (temp != nullptr) {
		count++;
		temp = temp->p_next;
	}
	return count;
}

bool isEmpty(Queue q) {
	return q.head == nullptr;
}

void queueToText(Queue& q, ofstream& ofs) {
	if (isEmpty(q)) {
		ofs << "EMPTY" << endl;
	}
	else {
		NODE* temp = q.head;
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
	Queue* s = initializeQueue();
	string function;
	while (ifs >> function) {
		if (function == "init") {
			if (s != nullptr) {
				delete s;
			}
			s = initializeQueue();
			ofs << "EMPTY" << endl;
		}
		else if (function == "enqueue") {
			int key;
			ifs >> key;
			ifs.ignore();
			enqueue(*s, key);
			queueToText(*s, ofs);
		}
		else if (function == "dequeue") {
			dequeue(*s);
			queueToText(*s, ofs);
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