#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

struct NODE {
	string key = "";
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

Stack* initializeStack();
void push(Stack& s,string key);
string pop(Stack& s);
bool isEmpty(Stack s);

Stack* initializeStack() {
	Stack* s = new Stack;
	s->top = nullptr;
	return s;
}
void push(Stack& s, string key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = s.top;
	s.top = newNode;

}
string pop(Stack& s) {
	if (s.top == nullptr) {
		return "-1";
	}
	NODE* temp = s.top;
	string first = temp->key;
	s.top = s.top->p_next;
	delete temp;
	return first;
}

bool isEmpty(Stack s) {
	return s.top == nullptr;
}
string removeZero(string s) {
	int t = 0;
	string result = "";
	if (s[t] == '-') {
		t++;
		result = '-' + result;
	}
	while (s[t] == '0') {
		t++;
	}
	if (t == s.length()) {
		return "0";
	}
	for (int i = t; i < s.length(); i++) {
		result += s[i];
	}
	return result;
}
bool compare(string s1, string s2) {
	if (s1 == "+" || s1 == "-") {
		return true;
	}
	else if (s1 == "*" or s1 == "/") {
		if (s2 == "*" or s2 == "/") {
			return true;
		}
	}
	return false;
}
string calculation(string s1, string s2, char ope, bool& error) {
	int s;
	if ((ope == '+' || ope == '-') && (s1[0] != '-' && s2[0] != '-')) {
		int length;

		if (s1.length() >= s2.length()) {
			length = s1.length() - s2.length();
			for (int i = 0; i < length; i++) {
				s2 = "0" + s2;
			}
		}
		else {
			length = s2.length() - s1.length();
			for (int i = 0; i < length; i++) {
				s1 = "0" + s1;
			}
		}
	}
	bool negative;
	string s3 = "";
	switch (ope) {
	case '+':
		if (s1[0] == '-' && s2[0] != '-') {
			s1[0] = '0';
			s3 = calculation(s2, s1, '-', error);
			return s3;
		}
		else if (s1[0] != '-' && s2[0] == '-') {
			s2[0] = '0';
			s3 = calculation(s1, s2, '-', error);
			return s3;
		}
		else if (s1[0] == '-' && s2[0] == '-') {
			s1[0] = '0';
			s2[0] = '0';
			s3 = calculation(s1, s2, '+', error);
			s3 = '-' + s3;
			return s3;
		}
		else {
			s = 0;
			for (int i = s1.length() - 1; i >= 0; i--) {
				int d = 0;
				if (s == 0) {
					d = s1[i] + s2[i] - '0' - '0';
				}
				else {
					d = s1[i] + s2[i] - '0' - '0' + 1;
					s--;
				}
				if (d >= 10) {
					s++;
					d -= 10;
				}
				s3 = (char)(d + '0') + s3;
			}
			if (s == 1) {
				s3 = "1" + s3;
			}
			s3 = removeZero(s3);
			return s3;
			break;
		}

	case '-':
		if (s1[0] == '-' && s2[0] != '-') {
			s1[0] = '0';
			s3 = calculation(s2, s1, '+', error);
			s3 = '-' + s3;
			return s3;
		}
		else if (s1[0] != '-' && s2[0] == '-') {
			s2[0] = '0';
			s3 = calculation(s1, s2, '+', error);
			return s3;
		}
		else if (s1[0] == '-' && s2[0] == '-') {
			s1[0] = '0';
			s2[0] = '0';
			s3 = calculation(s1, s2, '-', error);
			if (s3[0] == '-') {
				s3[0] = '0';
				s3 = removeZero(s3);
			}
			else if (s3[0] != '0') {
				s3 = '-' + s3;
			}
			return s3;
		}
		else {
			s = 0;
			for (int i = s1.length() - 1; i >= 0; i--) {
				int d = 0;
				if (s == 0) {
					d = s1[i] - (s2[i] - '0') - '0';
				}
				else {
					d = s1[i] - (s2[i] - '0') - '0' - 1;
					s++;
				}
				if (d < 0 && i != 0) {
					s--;
					d += 10;
				}
				else if (d < 0 && i == 0) {
					string temp = "";
					temp = temp + char(abs(d) + '0');
					for (int i = 0; i < s3.length(); i++) {
						temp = temp + "0";
					}
					s3 = calculation(temp, s3, '-', error);
					s3 = '-' + s3;
					s3 = removeZero(s3);
					return s3;
				}
				s3 = (char)(d + '0') + s3;
			}
			if (s == -1) {
				s3 = "-" + s3;
			}
			s3 = removeZero(s3);
			return s3;
			break;
		}

	case '*':
		negative = false;
		if (s1[0] == '-' && s2[0] != '-') {
			negative = true;
			s1[0] = '0';
		}
		else if (s2[0] == '-' && s1[0] != '-') {
			s2[0] = '0';
			negative = true;
		}
		else if (s2[0] == '-' && s1[0] == '-') {
			s2[0] = '0';
			s1[0] = '0';
		}
		for (int i = s2.length() - 1; i >= 0; i--) {
			int s = 0;
			string comp = "";
			for (int k = 0; k < s2.length() - 1 - i; k++) {
				comp = comp + "0";
			}
			for (int j = s1.length() - 1; j >= 0; j--) {
				int d = 0;
				if (s == 0) {
					d = (s2[i] - '0') * (s1[j] - '0');
				}
				else {
					d = (s2[i] - '0') * (s1[j] - '0') + s;
					s = 0;
				}
				if (d >= 10) {
					s += d / 10;
					d = d % 10;
				}
				comp = (char)(d + '0') + comp;
			}
			if (s != 0) {
				comp = char(s + '0') + comp;
			}
			s3 = calculation(s3, comp, '+', error);

		}
		s3 = removeZero(s3);
		if (negative) {
			s3 = '-' + s3;
		}
		return s3;
		break;
	case '/':
		negative = false;
		if (s1[0] == '-' && s2[0] != '-') {
			negative = true;
			s1[0] = '0';
			s1 = removeZero(s1);
		}
		else if (s2[0] == '-' && s1[0] != '-') {
			s2[0] = '0';
			s2 = removeZero(s2);
			negative = true;
		}
		else if (s2[0] == '-' && s1[0] == '-') {
			s2[0] = '0';
			s1[0] = '0';
			s1 = removeZero(s1);
			s2 = removeZero(s2);
		}
		error = true;
		for (int i = s2.length() - 1; i >= 0; i--) {
			if (s2[i] != '0') {
				error = false;
				break;
			}
		}
		if (error == true) {
			cout << "Error" << endl;
			return "Error";
			break;
		}
		else {
			if (s1.length() < s2.length()) {
				return "0";
			}
			string current = "";
			int t = 0;
			while (s1.length() >= s2.length()) {
				string a = calculation(s1, s2, '-', error);
				if (a[0] == '-' && s1.length() == s2.length()) {
					break;
				}
				if (current != "") {
					if (s2.length() > 1) {
						for (int i = 0; i < s2.length()-1; i++) {
							current = current + s1[i + 1];
						}
					}
					else {
						for (int i = 0; i < s2.length(); i++) {
							current = current + s1[i + 1];
						}
					}
				}
				else if (current == "") {
					for (int i = 0; i < s2.length(); i++) {
						current = current + s1[i];
					}
				}
				string temp = calculation(current, s2, '-', error);
				
				while (temp[0] == '-' && current.length() < s1.length()) {
					s3 = s3 + '0';
					current = current + s1[current.length()];
					temp = calculation(current, s2, '-', error);
				}
				if (temp[0] == '-') {
					s3 = s3 + '0';

				}
				if (temp[0] == '-' && s1.length() == current.length()) {
					break;
				}
				
				for (int i = 1; i < 10; i++) {
					string mul = "";
					mul = mul + char(i + '0');
					string temp2 = calculation(mul, s2, '*', error);
					string minus = calculation(current, temp2, '-', error);
					if (minus[0] == '-') {
						s3 = s3 + char(i - 1 + '0');
						string l = "";
						l = l + char(i - 1 + '0');
						mul = calculation(l, s2, '*', error);
						int d = mul.length();
						for (int i = d; i < s1.length(); i++) {
							mul = mul + '0';
						}
						minus = calculation(s1, mul, '-', error);
						d = minus.length();
						t++;
						int k = s1.length() - t - d;
						
						for (int i = 0; i < k; i++) {
							minus = '0' + minus;
						}
						current = "";
						
						current = current + minus[0];
						s1 = minus;
						break;
					}
					else if (minus[0] == '0') {
						s3 = s3 + char(i + '0');
						string l = "";
						l = l + char(i + '0');
						mul = calculation(l, s2, '*', error);
						int d = mul.length();
						for (int i = d; i < s1.length(); i++) {
							mul = mul + '0';
						}
						minus = calculation(s1, mul, '-', error);
						d = minus.length();
						t++;
						int k = s1.length() - t - d;

						for (int i = 0; i < k; i++) {
							minus = '0' + minus;
						}
						current = "";
						s1 = minus;
						break;
					}

				}
			}
			
			s3 = removeZero(s3);
			if (negative) {
				s3 = '-' + s3;
			}
			return s3;
		}
	default:
		break;
	}
}

bool checkBrackets(char a[]) {
	Stack* s = initializeStack();
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == '(') {
			push(*s, "(");
		}
		else if (a[i] == ')') {
			if (isEmpty(*s)) {
				return false;
			}
			pop(*s);
		}
	}
	if (isEmpty(*s)) {
		return true;
	}
	else return false;
}
string postFixCalc(string p, bool& error) {
	Stack* s = initializeStack();
	string temp = "";
	string result = "";
	for (int i = 0; i < p.length(); i++) {
		if (p[i] != ' ') {
			temp = temp + p[i];
		}
		else {
			if (temp[temp.length() - 1] <= '9' && temp[temp.length() - 1] >= '0') {
				push(*s, temp);
				temp = "";
			}
			else {
				string s2 = pop(*s);
				string s1 = pop(*s);

				result = calculation(s1, s2, temp[0], error);

				if (error) {
					return "0";
				}
				push(*s, result);
				temp = "";
			}
		}
	}
	return result;
}
void perform(string path1, string path2) {
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
	string postFix = "";
	char s[1000];
	while (!ifs.eof())
	{
		bool error = false;
		Stack* q = initializeStack();
		int nums = 0;
		int ope = 0;
		ifs.getline(s, 1000, '\n');
		if (!checkBrackets(s)) {
			cout << "Error" << endl;
			ofs << "Error" << endl;
			continue;
		}
		string a = "";

		for (int i = 0; i < strlen(s); i++) {
			if (s[i] == '(') {
				push(*q, "(");
			}
			else if (s[i] == ' ') {
				continue;
			}
			else if (s[i] == ')') {
				while (q->top->key != "(") {
					string k = pop(*q);
					postFix = postFix + k + " ";
				}
				pop(*q);
			}
			else if ('0' <= s[i] && s[i] <= '9') {
				while ('0' <= s[i + 1] && s[i + 1] <= '9') {
					a = a + s[i];
					i++;
				}
				a = a + s[i];
				postFix = postFix + a + ' ';
				nums++;
				a = "";
			}
			else {
				if (s[i] == '-') {
					if (i > 0 && s[i - 1] == '(') {
						while ('0' <= s[i + 1] && s[i + 1] <= '9') {
							a = a + s[i];
							i++;
						}
						a = a + s[i];
						postFix = postFix + a + ' ';
						nums++;
						a = "";
					}
					else {
						a = a + s[i];
						while (q->top != nullptr && compare(a, q->top->key) && q->top->key != "(") {
							postFix = postFix + pop(*q) + ' ';

						}
						push(*q, a);
						ope++;
						a = "";
					}
				}
				else {
					a = a + s[i];
					while (q->top != nullptr && compare(a, q->top->key) && q->top->key != "(") {
						postFix = postFix + pop(*q) + ' ';

					}
					push(*q, a);
					ope++;
					a = "";
				}
			}
		}
		while (!isEmpty(*q)) {
			postFix = postFix + pop(*q) + ' ';
		}
		delete[]q;
		q = nullptr;
		if (nums - ope != 1) {
			ofs << "Error" << endl;
			cout << "Error" << endl;
			postFix = "";
			continue;
		}
		else {
			string s = postFixCalc(postFix, error);
			if (!error) {
				ofs << s << endl;
				for (char ch : s) {
					cout << ch;
				}
				cout << endl;
			}
			else {
				ofs << "Error" << endl;
				postFix = "";
				continue;
			}
		}
		postFix = "";
	}

}
int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Error!" << endl;
		return -1;
	}
	string path1 = argv[1];
	string path2 = argv[2];
	perform(path1, path2);
}