#include <math.h>
#include <stdio.h>
struct rng{
	int lower=0;
	int upper = 0;
	int delta = 0;
	bool used = 0;

};
rng list[1000];
//fill the range with the largest part ,keep filling the empty parts
int fill(rng arr[],int *usedRanges,int *count, int min, int max, int space , int n);
int main() {
	rng list[1000];
	int n, x, count = 0, usedRanges = 0;
	int i,j;
	long int* out;
	bool zero=0, ceilling=0;
	//get input
	scanf_s("%d %d", &n, &x);

	for (i = 0; i < n; i++) {
		scanf_s("%d %d", &list[i].lower, &list[i].upper);
		list[i].delta = list[i].lower - list[i].upper;
		//delta[i] = upper[i] - lower[i];
		zero = list[i].lower == 0 ? 1 : zero;
		ceilling = list[i].upper== x ? 1 : ceilling;
	}
	//checking the presence of 0 and the ceilling of the main range
	if (!(zero && ceilling)) {
		printf_s("0\n");
		return 0;
	}
	while ((n - usedRanges) > x) {
		fill(list, &usedRanges, &count, 0, x, x, n);
		count += pow(2, n - usedRanges);
	}
	printf_s("%d ", count);
	//free the storage for dynamic arrays

	return 0;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

 
// n is size of heap
void heap(rng arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// left child is larger than root
	if (left < n && arr[left].upper > arr[largest].upper || (arr[left].upper == arr[largest].upper && arr[left].delta > arr[largest].delta))
		largest = left;
	// right child is larger than largest 
	if (right < n && (arr[right].upper > arr[largest].upper ||(arr[right].upper == arr[largest].upper&& arr[right].delta > arr[largest].delta)))
		largest = right;
	if (largest != i) {
		swap(&arr[i].upper, &arr[largest].upper);
		heap(arr, n, largest);
	}

}

void heapSort(rng arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heap(arr, n, i);
	for (int i = n - 1; i >= 0; i--) {
		swap(&arr[0].upper, &arr[i].upper);
		heap(arr, i, 0);

	}

}
int fill(rng arr[], int* usedRanges, int* count, int min, int max, int space , int n) {
	int i, j;
	int upperVoid, lowerVoid = 0;
	rng filler;
	for ( i = n; arr[i].upper >min; i--) {
		if (arr[i].upper <= max && arr[i].used == 0&&arr[i].lower>=min) {
			filler = arr[i];
			arr[i].used = 1;
			i = -1;
		}
	}
	//cant find a fitting range
	if (i < 0)
		return -1;
	else {
		if (space<=filler.delta)
			return filler.delta;
		else {
			if (filler.upper < max)
				upperVoid = fill(arr, usedRanges, count, filler.lower + 1, max,max-filler.upper, n);
			if (filler.lower > min)
				lowerVoid = fill(arr, usedRanges, count, min, filler.upper - 1,filler.lower-min, n);
			if (lowerVoid < 0|| upperVoid < 0)
				return -1;
			if (lowerVoid + upperVoid >= filler.delta) {
				//a-b--c--d-e
				//bd
				//ac
				//ce
				arr[i].used = 0;
				return lowerVoid + upperVoid;
			}
			else {
				*usedRanges ++;
				return filler.delta;
			}
		}
	}
}