#include<iostream>
using namespace std;
int findMin(int a[], int n) {
	int low = 0;
	int high = n - 1;
	while (low < high) {
		int mid = low + (high - low) / 2 ;
		if (a[mid] > a[high]) {
			low = mid + 1;
		}
		else high = mid;
	}
	return a[low];
}
int main() {
	int n = 5;
	int a[5] = { 3,4,5,1,2 };
	cout<< findMin(a, n);
}