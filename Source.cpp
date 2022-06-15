#include <math.h>
#include <stdio.h>

void maxSegTree(int input[], int segmentTree[], int low, int high, int pos) {
	if (low == high) {
		segmentTree[pos] = input[low];
		return;
	}
	int mid = (low + high) / 2;
	maxSegTree(input, segmentTree, low, mid, 2 * pos + 1);
	maxSegTree(input, segmentTree, mid + 1, high, 2 * pos + 2);
	segmentTree[pos] = segmentTree[2 * pos + 1] > segmentTree[2 * pos + 2]?segmentTree[2 * pos + 1] : segmentTree[2 * pos + 2];

}
int main() {
	int i,n,x;
	scanf_s("%d %d", &n, &x);
	int* lower = new int[n];
	int* upper = new int[n];
	int* delta = new int[n];
	int* segments = new int[2*n-1];
	int* rngUsed = new int[2 * n - 1];
	for (i = 0; i < n; i++) {
		scanf_s("%d %d", &lower[i], &upper[i]);
		delta[i] = upper[i] - lower[i];
	}
	maxSegTree(delta, segments, 0, x, 0);
	delete[] lower;
	delete[] upper;
	delete[] delta;
	delete[] segments;
	delete[] rngUsed;

	return 0;
}