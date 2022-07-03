#include <math.h>
#include <stdio.h>
struct rng{
	long int lower=0;
	long int upper = 0;
	long int delta = 0;
	bool used = 0;

};
rng list[1000];
//fill the range with the largest part ,keep filling the empty parts
long int fill(rng* arr[], long int adrress[], long int* usedRanges, long int* count, long int min, long int max, long int space, long int n);
void heapSort(rng arr[], long int n);
void heap(rng arr[], long int n, long int i);
void swap(rng* a, rng* b);
void maxSegTree(rng input[], rng* segmentTree[], long int low, long int high, long int pos);
rng* maxRngQuery(rng* segmentTree[], long int qLow, long int qHigh, long int low, long int high, long int pos);

int main() {
	long int n, x, count = 0, usedRanges = 0;
	long int i,j,check=1;
	long int* out;
	bool zero=0, ceilling=0;
	//get input
	scanf_s("%d %d", &n, &x);
	long int* adrs = new long int[n + 1];
	rng* list = new rng[n];
	rng** segTree = new rng*[2*n-1];
	for (i = 0; i < n; i++) {
		scanf_s("%d %d", &list[i].lower, &list[i].upper);
		list[i].delta = list[i].upper - list[i].lower;
		for (j = list[i].upper; j <= x; j++)
			adrs[j+1]++;
		zero = list[i].lower == 0 ? 1 : zero;
		ceilling = list[i].upper== x ? 1 : ceilling;
	}
	//checking the presence of 0 and the ceilling of the main range
	if (!(zero && ceilling)) {
		printf_s("0\n");
		return 0;
	}
	heapSort(list, n);
	maxSegTree(list, segTree, 0, n-1, 0);
	while (n > usedRanges&&check>0) {
		check=fill(segTree,adrs, &usedRanges, &count, 0, x, x, n);
		if(check>0)
			count += pow(2, n - usedRanges);
	}
	printf_s("%d \n", count);
	printf_s("%d ", count/(7 + pow(10, 9)) ) ;
	//free the storage for dynamic arrays
	delete[] list;
	delete[] segTree;
	delete[] adrs;
	return 0;
}

void swap(rng* a, rng* b) {
	rng temp = *a;
	*a = *b;
	*b = temp;
}

 
// n is size of heap
void heap(rng arr[], long int n, long int i) {
	long int largest = i;
	long int left = 2 * i + 1;
	long int right = 2 * i + 2;

	// left child is larger than root
	if (left < n && arr[left].upper > arr[largest].upper )
		largest = left;
	// right child is larger than largest 
	if (right < n && (arr[right].upper > arr[largest].upper))
		largest = right;
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heap(arr, n, largest);
	}

}

void heapSort(rng arr[], long int n) {
	for (long int i = n / 2 - 1; i >= 0; i--)
		heap(arr, n, i);
	for (long int i = n - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heap(arr, i, 0);

	}

}
long int fill(rng* arr[], long int adrress[], long int* usedRanges, long int* count, long int min, long int max, long int space , long int n) {
	long int i, j;
	long int upperVoid=0, lowerVoid = 0;
	rng* filler;
	filler = maxRngQuery(arr, adrress[min], adrress[max+1]-1,0, n-1, 0);
	//cant find a fitting range
	if (filler->delta <0)
		return -1;
	else {
		if (space <= filler->delta) {
			filler->used = 1;
			(*usedRanges)++;
			return filler->delta;
		}
		else {
			filler->used = 1;
			if (filler->upper < max)
				upperVoid = fill(arr, adrress, usedRanges, count, filler->lower + 1, max,max-filler->upper, n);
			if (filler->lower > min)
				lowerVoid = fill(arr,adrress, usedRanges, count, min, filler->upper - 1,filler->lower-min, n);
			if (lowerVoid < 0|| upperVoid < 0)
				return -1;
			if (lowerVoid + upperVoid >= filler->delta) {
				//a-b--c--d-e
				//bd
				//ac
				//ce
				filler->used= 0;
				return lowerVoid + upperVoid;
			}
			else {
				(*usedRanges) ++;
				return filler->delta+lowerVoid+upperVoid;
			}
		}
	}
}
void maxSegTree( rng input[],  rng* segmentTree[], long int low, long int high, long int pos) {
	if (low == high) {
		segmentTree[pos] = &input[low];
		return;
	}
	long int mid = (low + high) / 2;
	maxSegTree(input, segmentTree, low, mid, 2 * pos + 1);
	maxSegTree(input, segmentTree, mid + 1, high, 2 * pos + 2);
	segmentTree[pos] = segmentTree[2 * pos + 1]->delta > segmentTree[2 * pos + 2]->delta ? segmentTree[2 * pos + 1] : segmentTree[2 * pos + 2];

}
//query
 rng* maxRngQuery( rng* segmentTree[], long int qLow, long int qHigh, long int low, long int high, long int pos) {
	 rng out;
	if (qLow <= low && high <= qHigh&&segmentTree[pos]->used==0) {
		return segmentTree[pos];
	}
	if (qLow > high || qHigh < low|| low==high) {
		out.lower = out.upper = out.delta = -1 * _CRT_INT_MAX;
		return &out;
	}
	long int mid = (low + high) / 2;
	 rng* m = maxRngQuery(segmentTree, qLow, qHigh, low, mid, 2 * pos + 1);
	 rng* n = maxRngQuery(segmentTree, qLow, qHigh, mid + 1, high, 2 * pos + 2);

	//out = m->delta > n->delta ? m : n;
	return m->delta > n->delta ? m : n;
}
