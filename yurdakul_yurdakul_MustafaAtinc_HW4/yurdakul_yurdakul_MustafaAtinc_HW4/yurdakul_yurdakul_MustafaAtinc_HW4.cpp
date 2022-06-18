#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Heap capacity 
#define MAX_HEAP_SIZE (1028) 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 

//// Utility functions 

// exchange a and b 
void Exch(int &a, int &b)
{
	int aux = a;
	a = b;
	b = aux;
}

// Greater and Smaller are used as comparators 
bool Greater(int a, int b)
{
	return a > b;
}

bool Smaller(int a, int b)
{
	return a < b;
}

double Average(double a, double b)
{
	return (a + b) / 2;
}

// Signum function 
// = 0 if a == b - heaps are balanced 
// = -1 if a < b - left contains less elements than right 
// = 1 if a > b - left contains more elements than right 
int Signum(int a, int b)
{
	if (a == b)
		return 0;

	return a < b ? -1 : 1;
}

// Heap implementation 
// The functionality is embedded into 
// Heap abstract class to avoid code duplication 
template <class may>
class Heap
{
public:
	// Initializes heap array and comparator required 
	// in heapification 
	Heap<may>(int *b, bool(*c)(int, int)) : A(b), comp(c)
	{
		heapSize = -1;
	}

	// Frees up dynamic memory 
	virtual ~Heap()
	{
		if (A)
		{
			delete[] A;
		}
	}

	// We need only these four interfaces of Heap ADT 
	virtual bool Insert(may e) = 0;
	virtual may GetTop() = 0;
	virtual may ExtractTop() = 0;
	virtual may GetCount() = 0;

	void printHeap() {
		for (int i = 0; i <= heapSize; i++)
		{
			cout << A[i] << endl;
		}
	}
protected:

	// We are also using location 0 of array 
	int left(int i)
	{
		return 2 * i + 1;
	}

	int right(int i)
	{
		return 2 * (i + 1);
	}

	int parent(int i)
	{
		if (i <= 0)
		{
			return -1;
		}

		return (i - 1) / 2;
	}


	// Heap array 
	may *A;
	// Comparator 
	bool(*comp)(int, int);
	// Heap size 
	int heapSize;

	// Returns top element of heap data structure 
	may top(void)
	{
		may maxi = 0;

		if (heapSize >= 0)
		{
			maxi = A[0];
			//for (int i = 1; i < heapSize; ++i) 
			//maxi = max(maxi, A[i]); 
		}

		return maxi;
	}
	//
	//may mini(void)
	//{
	//	may minimum= 0;

	//	if(heapSize >= 0)
	//	{
	//		minimum = A[0];
	//		//for (int i = 1; i < heapSize; ++i) 
	//		//minimum = min(minimum, A[i]); 
	//	}
	//	return minimum;
	//}

	// Returns number of elements in heap 
	int count()
	{
		return heapSize + 1;
	}

	// Heapification 
	// Note that, for the current median tracing problem 
	// we need to heapify only towards root, always 
	void heapify(int i)
	{

		int p = parent(i);

		// comp - differentiate MaxHeap and MinHeap 
		// percolates up 
		if (i > 0 && comp(A[i], A[p]))
		{
			Exch(A[i], A[p]);
			heapify(p);
		}
	}
	void maxheapify(int arr[], int n, int i)
	{
		int largest = i; // Initialize largest as root 
		int l = 2 * i + 1; // left = 2*i + 1 
		int r = 2 * i + 2; // right = 2*i + 2 

						   // If left child is larger than root 
		if (l < n && arr[l] > arr[largest])
			largest = l;

		// If right child is larger than largest so far 
		if (r < n && arr[r] > arr[largest])
			largest = r;

		// If largest is not root 
		if (largest != i) {
			Exch(arr[i], arr[largest]);

			// Recursively heapify the affected sub-tree 
			maxheapify(arr, n, largest);
		}
	}
	void minheapify(int arr[], int n, int i)
	{
		int smallest = i; // Initialize largest as root 
		int l = 2 * i + 1; // left = 2*i + 1 
		int r = 2 * i + 2; // right = 2*i + 2 

						   // If left child is larger than root 
		if (l < n && arr[l] < arr[smallest])
			smallest = l;

		// If right child is larger than largest so far 
		if (r < n && arr[r] < arr[smallest])
			smallest = r;

		// If largest is not root 
		if (smallest != i) {
			Exch(arr[i], arr[smallest]);

			// Recursively heapify the affected sub-tree 
			minheapify(arr, n, smallest);
		}
	}

	// Deletes root of heap 
	int deleteTop()
	{
		int del = 0;

		if (heapSize > -1)
		{
			del = A[0];

			Exch(A[0], A[heapSize]);
			heapSize--;
			maxheapify(A, heapSize + 1, 0);
			//heapify(0);
		}

		return del;
	}
	int deleteMin()
	{
		int del = 0;

		if (heapSize > -1)
		{
			del = A[0];
			Exch(A[0], A[heapSize]);
			heapSize--;
			minheapify(A, heapSize + 1, 0);
		}

		return del;
	}

	// Helper to insert key into Heap 
	bool insertHelper(int key)
	{
		bool ret = false;

		if (heapSize < MAX_HEAP_SIZE)
		{
			ret = true;
			heapSize++;
			A[heapSize] = key;
			heapify(heapSize);
		}

		return ret;
	}

};

// Specilization of Heap to define MaxHeap 
class MaxHeap : public Heap<int>
{
private:

public:
	MaxHeap() : Heap(new int[MAX_HEAP_SIZE], &Greater) { }

	~MaxHeap() { }

	// Wrapper to return root of Max Heap 
	int GetTop()
	{
		return top();
	}

	// Wrapper to delete and return root of Max Heap 
	int ExtractTop()
	{
		return deleteTop();
	}

	// Wrapper to return # elements of Max Heap 
	int GetCount()
	{
		return count();
	}

	// Wrapper to insert into Max Heap 
	bool Insert(int key)
	{
		return insertHelper(key);
	}
};

// Specilization of Heap to define MinHeap 
class MinHeap : public Heap<int>
{
private:

public:

	MinHeap() : Heap(new int[MAX_HEAP_SIZE], &Smaller) { }

	~MinHeap() { }

	// Wrapper to return root of Min Heap 
	int GetTop()
	{
		return top();
	}

	// Wrapper to delete and return root of Min Heap 
	int ExtractTop()
	{
		return deleteMin();
	}

	// Wrapper to return # elements of Min Heap 
	int GetCount()
	{
		return count();
	}

	// Wrapper to insert into Min Heap 
	bool Insert(int key)
	{
		return insertHelper(key);
	}
};

// Function implementing algorithm to find median so far. 
double getMedian(double e, double &m, Heap<int> &l, Heap<int> &r)
{
	// Are heaps balanced? If yes, sig will be 0 
	int sig = Signum(l.GetCount(), r.GetCount());
	switch (sig)
	{
	case 1: // There are more elements in left (max) heap 

		if (e < m) // current element fits in left (max) heap 
		{
			// Remore top element from left heap and 
			// insert into right heap 

			r.Insert(l.ExtractTop());
			// current element fits in left (max) heap 
			l.Insert(e);
		}
		else
		{

			// current element fits in right (min) heap 
			r.Insert(e);
		}

		// Both heaps are balanced 
		m = Average(l.GetTop(), r.GetTop());

		break;

	case 0: // The left and right heaps contain same number of elements 

		if (e < m) // current element fits in left (max) heap 
		{
			l.Insert(e);
			m = l.GetTop();

		}
		else
		{

			r.Insert(e);
			m = r.GetTop();

		}

		break;

	case -1: // There are more elements in right (min) heap 

		if (e < m) // current element fits in left (max) heap 
		{

			l.Insert(e);

		}
		else
		{
			// Remove top element from right heap and 
			// insert into left heap 

			int no = r.ExtractTop();
			l.Insert(no);
			// current element fits in right (min) heap 
			r.Insert(e);

		}

		// Both heaps are balanced 
		m = Average(l.GetTop(), r.GetTop());

		break;
	}

	// No need to return, m already updated 

	return m;
}

double printMedian(vector<double> numbs, Heap<int> *maxheap, Heap<int> *minheap)
{

	double m = 0; // effective median 
	for (unsigned int i = 0; i < numbs.size(); i++)
	{
		m = getMedian(numbs[i], m, *maxheap, *minheap);

	}
	//for (int i = 0; i < numbs.size(); i++) {
	//	cout << maxheap->GetTop() << endl;
	//	maxheap->ExtractTop();
	//}
	cout << m << endl;
	// C++ more flexible, ensure no leaks 
	//delete left;
	//delete right;
	return m;
}
// Driver code 
int main()
{
	Heap<int> *maxheap = new MaxHeap;
	Heap<int> *minheap = new MinHeap;

	vector<double> numbs;
	double num;
	string fname = "";
	while (fname != "cancel") {
		ifstream file;
		cout << "Give the file name:" << endl;
		cin >> fname;
		if (cin.eof()) {
			// we just read EOF, break out of the loop
			break;
		}
		file.open(fname);
		if (!file) {
			cout << " Error opening file, please try again. " << endl;
			break;
		}
		if (file.is_open()) {
			while (!file.eof())
			{
				file >> num;
				numbs.push_back(num);
			}
			file.close();
		}
		// In lieu of A, we can also use data read from a stream 
		double median = printMedian(numbs, maxheap, minheap);
		vector<double>().swap(numbs);
	}
	system("pause");
	return 0;
}
