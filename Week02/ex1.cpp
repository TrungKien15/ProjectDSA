#include<iostream>
using namespace std;

int fibonacci(int n);

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cout << fibonacci(i) << " ";
	}
}

int fibonacci(int n) {
	if (n == 1) {
		return 0;
	}
	else if (n == 2) {
		return 1;
	}
	return fibonacci(n - 2) + fibonacci(n - 1);
}