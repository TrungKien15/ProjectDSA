#include<iostream>
using namespace std;
bool countDays(int a[], int n, int day,int weight) {
	int s = 0;
	int t = 1; // bien dem so ngay
	for (int i = 0; i < n; i++) {
		s += a[i];
		if (s > weight) {
			t++;
			i--;
			s = 0;
		}
	}
	if (t <= day) {
		return true;
	}
	else return false;
}

int minCapacity(int weight[], int n, int day) {
	int low = weight[n - 1];
	int high = 0; 
	for (int i = 0; i < n; i++) {
		high += weight[i];
	}
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (countDays(weight, n, day, mid)) {
			high = mid;
		}
		else low = mid + 1;
	}
	return low;
}

int main() {
	int weight[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = 10;
	int day = 5;
	cout << minCapacity(weight, n, day);
}