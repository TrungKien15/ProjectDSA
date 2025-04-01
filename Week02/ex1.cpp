#include<iostream>
using namespace std;
int linearSearch(int a[],int n,int k) {
	for (int i = 0; i < n; i++) {
		if (a[i] == k) {
			return i;
		}
	}
	return -1;
}
int main() {
	int n = 5;
	int a[5] = { 1,3,5,7,9 };
	int k = 5;
	cout << linearSearch(a, n, k);
}