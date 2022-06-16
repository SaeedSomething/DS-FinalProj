#include <math.h>
#include <stdio.h>
//build
void maxSegTree(long int input[], long int segmentTree[],long int lazy[], long int low, long int high, long int pos) {
	if (low == high) {
		segmentTree[pos] = input[low];
		lazy[pos] = 0;
		return;
	}
	int mid = (low + high) / 2;
	maxSegTree(input, segmentTree,lazy , low, mid, 2 * pos + 1);
	maxSegTree(input, segmentTree, lazy ,mid + 1, high, 2 * pos + 2);
	segmentTree[pos] = segmentTree[2 * pos + 1] > segmentTree[2 * pos + 2] ? segmentTree[2 * pos + 1] : segmentTree[2 * pos + 2];

}
//query
long int maxRngQuery(long int segmentTree[], long int qLow, long int qHigh, long int low, long int high, long int pos) {
	if (qLow <= low && high <= qHigh) {
		return segmentTree[pos];
	}
	if (qLow > high || qHigh < low)
		return _CRT_INT_MAX * -1;
	long int mid = (low + high) / 2;
	long int m = maxRngQuery(segmentTree, qLow, qHigh, low, mid, 2 * pos + 1);
	long int n = maxRngQuery(segmentTree, qLow, qHigh, mid + 1,high, 2 * pos + 2);
	mid = m > n ? m : n;
	return mid;
}
//update
void updateSegTree() {}
//fill the range with the largest part ,keep filling the empty parts
void fill(long int low, long int high, long int* segTree, bool* used );
int main() {
	long int n, x, count = 0, usedRanges = 0;
	int i;
	//get input
	scanf_s("%d %d", &n, &x);
	long int* lower = new long int[n];
	long int* upper = new long int[n];
	long int* delta = new long int[n];
	bool* rngUsed = new bool[n];
	long int* segments = new long int[2 * n - 1];
	long int* lazy = new long int[2 * n - 1];
	for (i = 0; i < n; i++) {
		scanf_s("%d %d", &lower[i], &upper[i]);
		delta[i] = upper[i] - lower[i];
	}
	//build the tree
	maxSegTree(delta, segments,lazy, 0, x, 0);
	//until there is a chance to cover the whole thing
	while ((n - usedRanges) * segments[0] > x) {

	}
	//free the storage for dynamic arrays
	delete[] lower;
	delete[] upper;
	delete[] delta;
	delete[] segments;
	delete[] rngUsed;
	return 0;
}