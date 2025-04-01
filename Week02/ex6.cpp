#include<iostream>	
using namespace std;
void sumTarget(int a[], int n, int target) {
	int left = 0;
	int right = n-1;
	while (left < right) {
		int sum = a[left] + a[right];
		if (sum == target) {
			cout << "YES";
			return;
		}
		else if (sum > target) {
			right--;
		}
		else {
			left++;
		}
	}
	cout << "NO";
	return;
}
int main() {
	int n = 5;
	int a[5] = { 1,2,3,4,6};
	int target = 5;
	sumTarget(a, n, target);
}