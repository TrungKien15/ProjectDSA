#include<iostream>
using namespace std;
void sortArray(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
			}
		}
	}
}
void findZeroSum(int nums[], int n) {
	sortArray(nums, n);
	int t = 0;
	cout << "[";
	for (int i = 0; i < n - 2; i++) {
		if (nums[i] == nums[i - 1]) {
			continue;
		}
		int l = i + 1;
		int r = n - 1;
		while (l < r) {
			if (nums[i] + nums[l] + nums[r] == 0) {
				if (t == 0) {
					cout << "[" << nums[i] << "," << nums[l] << "," << nums[r] << "]";
					t++;
				}
				else {
					cout << ", [" << nums[i] << "," << nums[l] << "," << nums[r] << "]";
				}
				while (l<r && nums[l] == nums[l + 1]) {
					l++;
				}
				while (l <r && nums[r] == nums[r - 1]) {
					r--;
				}

				l++;
				r--;
			}
			else if (nums[i] + nums[l] + nums[r] < 0) {
				l++;
			}
			else r--;
		}
	}
	cout << "]";
	return ;
}
int main() {
	int nums[6] = { -1,0,1,2,-1,-4 };
	int n = 6;
	findZeroSum(nums, n);
}