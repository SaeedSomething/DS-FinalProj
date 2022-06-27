#include <math.h>
#include <stdio.h>
long int min = -1;
long int* ptr = &min;
void maxSegTree(long int input[], long int segmentTree[][2], long int lazy[], long int low, long int high, long int pos);
long int* maxRngQuery(long int segmentTree[][2], long int qLow, long int qHigh, long int low, long int high, long int pos);

//update
void updateSegTree() {}
//fill the range with the largest part ,keep filling the empty parts
void fill(long int low, long int high, long int* segTree, bool* used );
int main() {
	long int n, x, count = 0, usedRanges = 0;
	int i,j;
	long int* out;
	bool zero=0, ceilling=0;
	//get input
	scanf_s("%d %d", &n, &x);
	long int* lower = new long int[n];
	long int* upper = new long int[n];
	long int* delta = new long int[n];
	bool* rngUsed = new bool[n];
	auto segments = new long int[2 * n - 1][2];
	long int* lazy = new long int[2 * n - 1];
	for (i = 0; i < n; i++) {
		scanf_s("%d %d", &lower[i], &upper[i]);
		delta[i] = upper[i] - lower[i];
		zero = lower[i] == 0 ? 1 : zero;
		ceilling = upper[i] == x ? 1 : ceilling;
	}
	//checking the presence of 0 and the ceilling of the main range
	if (!(zero && ceilling)) {
		printf_s("0\n");
		return 0;
	}
	//build the tree
	maxSegTree(delta, segments,lazy, 0, x, 0);
	for (i = 0; i < 2 * n - 1; i++) {
		printf_s("%d %d \n", segments[i][0], segments[i][1]);
	}
	//until there is a chance to cover the whole thing
	//(n - usedRanges) * segments[0][0] > x
	while (1) {
		scanf_s("%d %d", &i, &j);
		out=maxRngQuery(segments, i, j, 0, x, 0);
	}
	//free the storage for dynamic arrays
	delete[] lower;
	delete[] upper;
	delete[] delta;
	delete[] segments;
	delete[] rngUsed;
	return 0;
}
//build
void maxSegTree(long int input[], long int segmentTree[][2], long int lazy[], long int low, long int high, long int pos) {
	if (low == high) {
		segmentTree[pos][0] = input[low];//value of the variable
		segmentTree[pos][1] = low;//place of the variable in delta[]&rngUsed[]
		lazy[pos] = 0;
		return;
	}
	int mid = (low + high) / 2;
	maxSegTree(input, segmentTree, lazy, low, mid, 2 * pos + 1);
	maxSegTree(input, segmentTree, lazy, mid + 1, high, 2 * pos + 2);
	//segmentTree[pos] = segmentTree[2 * pos + 1][0] > segmentTree[2 * pos + 2][0] ? segmentTree[2 * pos + 1] : segmentTree[2 * pos + 2];
	if (segmentTree[2 * pos + 1][0] > segmentTree[2 * pos + 2][0]) {
		segmentTree[pos][0] = segmentTree[2 * pos + 1][0];
		segmentTree[pos][1] = segmentTree[2 * pos + 1][1];
	}
	else {
		segmentTree[pos][0] = segmentTree[2 * pos + 2][0];
		segmentTree[pos][1] = segmentTree[2 * pos + 2][1];
	}
}
//query
long int* maxRngQuery(long int segmentTree[][2], long int qLow, long int qHigh, long int low, long int high, long int pos) {
	if (qLow <= low && high <= qHigh) {
		return segmentTree[pos];
	}
	if (qLow > high || qHigh < low) {
		//long int* ptr ;
		// *ptr = -1;
		return ptr;
	}
	long int mid = (low + high) / 2;
	long int* m = maxRngQuery(segmentTree, qLow, qHigh, low, mid, 2 * pos + 1);
	long int* n = maxRngQuery(segmentTree, qLow, qHigh, mid + 1, high, 2 * pos + 2);
	long int* out = m;
	//out = &m > &n ? m: n;
	if (m[0] > n[0]) {
		out[0] = m[0];
		out[1] = n[1];
	}
	else {
		out[0] = n[0];
		out[1] = n[1];
	}
	return out;
}