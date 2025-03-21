#include <iostream>
using namespace std;
bool isSorted(int arr[], int n) {
		if (n == 1 || n == 0)
		return true;
		if (arr[0] > arr[1])
		return false;
		return isSorted(arr + 1, n - 1);
}
int main() {
	int arr[] = { 1, 2, 3, 4, 5 }; // Example sorted array
	int n = sizeof(arr) / sizeof(arr[0]);
		if (isSorted(arr, n))
		cout << "The array is sorted.\n";
	else
		cout << "The array is NOT sorted.\n";
		return 0;
}