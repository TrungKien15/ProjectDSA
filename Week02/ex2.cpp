#include<iostream>
using namespace std;
int sentinelLinearSearch(int a[], int n, int k) {
	int last = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	a[n - 1] = last;
	if (a[n - 1] == k || i < n - 1) {
		return i;
	}
	return -1;
}
int main() {
	int n = 5;
	int a[5] = { 1,3,5,7,9 };
	int k = 5;
	cout << sentinelLinearSearch(a, n, k);
}