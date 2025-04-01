#include<iostream>
using namespace std;
int minLength(int a[], int n, int target) {
	int left = 0;
	int right = 0;
	int minLength = 0;
	while (right < n) {
		int sum = 0;
		for (int i = left; i <= right; i++) {
			sum += a[i];
		}
		if (sum == target) {
			if (minLength == 0) {
				minLength = right - left +1;
			}
			else if (minLength > right - left+1) {
				minLength = right - left +1;
			}
			left++;
			right++;
		}
		else if (sum < target) {
			right++;
		}
		else left++;
	}
	return minLength; 
}

int main() {
	int a[6] = { 2,3,1,2,4,3 };
	int n = 6;
	cout << minLength(a, n, 6);
}