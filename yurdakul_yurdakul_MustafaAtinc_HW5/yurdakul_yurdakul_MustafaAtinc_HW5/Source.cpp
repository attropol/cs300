#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;


class Person {
private:
	string name;
	string lname;
	string phonenumber;
	string city;
public:
	Person() {}
	Person(string newname) {
		name = newname;
	}
	Person(string newname, string newlname) {
		name = newname;
		lname = newlname;
	}
	Person(string newname, string newlname, string newphonenumber, string newcity)
	{
		name = newname;
		lname = newlname;
		phonenumber = newphonenumber;
		city = newcity;
	}
	string getName() {
		return name;
	}
	string getLname() {
		return lname;
	}
	string getPhonenumber() {
		return phonenumber;
	}
	string getCity() {
		return city;
	}
	void setName(string newname) {
		name = newname;
	}
	void setLname(string newlname) {
		lname = newlname;
	}
	void setPhonenumber(string newphonenumber) {
		phonenumber = newphonenumber;
	}
	void setCity(string newcity) {
		city = newcity;
	}
};
//BST BEGINS
using namespace std;

// BST node 
struct Node {
	string name;
	string lname;
	string numb;
	string city;
	struct Node *left, *right;
};

// Utitlity function to create a new node 
Node* newNode(Person p)
{
	Node* temp = new Node;

	temp->name = p.getName();
	temp->lname = p.getLname();
	temp->city = p.getCity();
	temp->numb = p.getPhonenumber();

	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

// A utility function to insert a new 
// Node with given key in BST 
Node* insert(Node* root, Person p)
{
	// Create a new Node containing 
	// the new element 
	Node* newnode = newNode(p);

	// Pointer to start traversing from root and 
	// traverses downward path to search 
	// where the new node to be inserted 
	Node* x = root;

	// Pointer y maintains the trailing 
	// pointer of x 
	Node* y = NULL;

	while (x != NULL) {
		y = x;
		if (p.getName() < x->name)
			x = x->left;
		else
			x = x->right;
	}

	// If the root is NULL i.e the tree is empty 
	// The new node is the root node 
	if (y == NULL)
		y = newnode;

	// If the new key is less then the leaf node key 
	// Assign the new node to be its left child 
	else if (p.getName() < y->name)
		y->left = newnode;

	// else assign the new node its right child 
	else
		y->right = newnode;

	// Returns the pointer where the 
	// new node is inserted 
	return y;
}

// A utility function to do inorder 
// traversal of BST 
void Inorder(Node* root)
{
	if (root == NULL)
		return;
	else {
		Inorder(root->left);
		//cout << root->name <<" "<<root->lname <<endl;
		Inorder(root->right);
	}
}
Node* search(Node* root, Person p)
{
	// Base Cases: root is null or key is present at root 
	if (root == NULL || root->name == p.getName())
		return root;

	// Key is greater than root's key 
	if (root->name < p.getName())
		return search(root->right, p.getName());

	// Key is smaller than root's key 
	return search(root->left, p.getName());
}

//BTS ENDS

//AVL BEGINS

struct avl {
	string name;
	string lname;
	string numb;
	string city;
	struct avl *l;
	struct avl *r;
}*r;
class avl_tree {
public:
	int height(avl *);
	int difference(avl *);
	avl *rr_rotat(avl *);
	avl *ll_rotat(avl *);
	avl *lr_rotat(avl*);
	avl *rl_rotat(avl *);
	avl * balance(avl *);
	avl * insert(avl*, Person);
	avl * search(avl*, Person);
	void inorder(avl *);
	avl_tree() {
		r = NULL;
	}
};
int avl_tree::height(avl *t) {
	int h = 0;
	if (t != NULL) {
		int l_height = height(t->l);
		int r_height = height(t->r);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}
int avl_tree::difference(avl *t) {
	int l_height = height(t->l);
	int r_height = height(t->r);
	int b_factor = l_height - r_height;
	return b_factor;
}
avl *avl_tree::rr_rotat(avl *parent) {
	avl *t;
	t = parent->r;
	parent->r = t->l;
	t->l = parent;
	return t;
}
avl *avl_tree::ll_rotat(avl *parent) {
	avl *t;
	t = parent->l;
	parent->l = t->r;
	t->r = parent;
	return t;
}
avl *avl_tree::lr_rotat(avl *parent) {
	avl *t;
	t = parent->l;
	parent->l = rr_rotat(t);
	return ll_rotat(parent);
}
avl *avl_tree::rl_rotat(avl *parent) {
	avl *t;
	t = parent->r;
	parent->r = ll_rotat(t);
	return rr_rotat(parent);
}
avl *avl_tree::balance(avl *t) {
	int bal_factor = difference(t);
	if (bal_factor > 1) {
		if (difference(t->l) > 0)
			t = ll_rotat(t);
		else
			t = lr_rotat(t);
	}
	else if (bal_factor < -1) {
		if (difference(t->r) > 0)
			t = rl_rotat(t);
		else
			t = rr_rotat(t);
	}
	return t;
}
avl *avl_tree::insert(avl *r, Person p) {
	if (r == NULL) {
		r = new avl;
		r->name = p.getName();
		r->lname = p.getLname();
		r->city = p.getCity();
		r->numb = p.getPhonenumber();

		r->l = NULL;
		r->r = NULL;
		return r;
	}
	else if (p.getName()< r->name) {
		r->l = insert(r->l, p);
		r = balance(r);
	}
	else if (p.getName() >= r->name) {
		r->r = insert(r->r, p);
		r = balance(r);
	} return r;
}
void avl_tree::inorder(avl *t) {
	if (t == NULL)
		return;
	inorder(t->l);
	//cout << t->name << " "<< t->lname<<endl;
	inorder(t->r);
}
avl *avl_tree::search(avl*t, Person p)
{
	// Base Cases: root is null or key is present at root 
	if (t == NULL || t->name == p.getName())
		return t;

	// Key is greater than root's key 
	if (t->name < p.getName())
		return search(t->r, p.getName());

	// Key is smaller than root's key 
	return search(t->l, p.getName());
}
//AVL ENDS
//BINARY SEARCH BEGINS
int binarySearch(vector<Person> numbs, int l, int r, Person p)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle 
		// itself 
		if (numbs[mid].getName() == p.getName())
			return mid;

		// If element is smaller than mid, then 
		// it can only be present in left subarray 
		if (numbs[mid].getName() > p.getName())
			return binarySearch(numbs, l, mid - 1, p);

		// Else the element can only be present 
		// in right subarray 
		return binarySearch(numbs, mid + 1, r, p);
	}

	// We reach here when element is not 
	// present in array 
	return -1;
}
//BINARY SEARCH ENDS
// A utility function to swap two elements 
//void swap(vector<Person>* a, vector<Person>* b)
//{
//	vector<Person> t;
//	t= *a;
//	*a = *b;
//	*b = t;
//}
//HEAP SORT BEGINNING
void heapify(vector<Person>&arr, int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

					   // If left child is larger than root 
	if (l < n && arr[l].getName() > arr[largest].getName())
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r].getName() > arr[largest].getName())
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}

// main function to do heap sort 
void heapSort(vector<Person>&arr, int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i>0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}
}
//HEAP SORT END

//MERGE SORT2 BEGIN
void merge(vector<Person>& numbs, int p, int q, int r)
{
	int size1 = q - p + 1;
	int size2 = r - q;
	vector<Person> L(size1);
	vector<Person> R(size2);

	for (int i = 0; i < size1; i++)
	{
		L[i] = numbs[p + i];
	}
	for (int j = 0; j < size2; j++)
	{
		R[j] = numbs[q + j + 1];
	}

	int i = 0, j = 0;
	int k;
	for (k = p; k <= r && i < size1 && j < size2; k++)
	{
		if (L[i].getName() <= R[j].getName())
		{
			numbs[k] = L[i];
			i++;
		}
		else
		{
			numbs[k] = R[j];
			j++;
		}
	}
	for (i = i; i < size1; ++i)
	{
		numbs[k] = L[i];
		k++;
	}

	for (j = j; j < size2; j++)
	{
		numbs[k] = R[j];
		k++;
	}
}
void merge_sort(vector<Person>& numbs, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort(numbs, p, q);
		merge_sort(numbs, q + 1, r);
		merge(numbs, p, q, r);
	}
}
//MERGE SORT2 END

//QUICK SORT BEGINNING


int partition(vector<Person>&numbs, int low, int high)
{
	int pivotIndex = low + (high - low) / 2;
	Person pivotValue = numbs[pivotIndex];
	int i = low, j = high;
	while (i <= j) {
		while (numbs[i].getName() < pivotValue.getName()) {
			i++;
		}
		while (numbs[j].getName() > pivotValue.getName()) {
			j--;
		}
		if (i <= j) {
			Person temp = numbs[i];
			numbs[i] = numbs[j];
			numbs[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}

/* The main function that implements QuickSort
low  --> Starting index,
high  --> Ending index */
void quickSort(vector<Person>&numbs, int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(numbs, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(numbs, low, pi - 1);
		quickSort(numbs, pi, high);
	}
}
//QUICK SORT END

//INSERTION SORT BEGINNING
void insertionSort(vector<Person>&numbs, int n)
{
	int i, j;
	Person key;
	for (i = 1; i < n; i++)
	{
		key = numbs[i];
		j = i - 1;

		while (j >= 0 && numbs[j].getName() > key.getName())
		{
			numbs[j + 1] = numbs[j];
			j = j - 1;
		}
		numbs[j + 1] = key;
	}
}
//INSERTION SORT END

//PRINT FUNCTION TO SEE IF IT WORKS FINE
/* Function to print an array */
void printArray(vector<Person>numbs, int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << numbs[i].getName() << " " << numbs[i].getLname() << endl;
}

void insert1(vector<Person> numbs, int left, int right, Node* root) {
	if (left < right) {
		int mid = (left + right) / 2;
		insert(root, numbs[mid]);
		insert1(numbs, left, mid, root);
		insert1(numbs, mid + 1, right, root);
	}
}

int main()
{
	vector<Person> numbs;
	vector<Person> numbs1;
	vector<Person> numbs2;
	vector<Person> numbs3;
	string word;
	string lname2;
	ifstream file;
	string fname;
	cout << "Please enter the contact file name:" << endl;
	cin >> fname;
	file.open(fname);
	if (!file) {
		cout << " Error opening file, please try again. " << endl;
		return 0;
	}
	//variables used to load data into the tree
	string name;
	string lname;
	string phonenumber;
	string city;
	Person p;
	while (file >> name >> lname >> phonenumber >> city)
	{
		p.setName(name);
		p.setLname(lname);
		p.setPhonenumber(phonenumber);
		p.setCity(city);
		numbs.push_back(p);
		numbs1.push_back(p);
		numbs2.push_back(p);
		numbs3.push_back(p);
	}
	file.close();
	Person q;
	cout << "Please enter the word to be queried :" << endl;
	cin >> word;
	size_t pos = word.find(" ");
	if (pos != std::string::npos) {
		lname2 = word.substr(pos);
		word = word.substr(0, pos);
	}

	//split word/lname
	q.setName(word);
	q.setLname(lname2);
	cout << q.getName() << q.getLname() << endl;
	numbs.push_back(q);
	numbs1.push_back(q);
	numbs2.push_back(q);
	numbs3.push_back(q);
	cout << endl;
	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;
	auto start1 = chrono::steady_clock::now();
	insertionSort(numbs, numbs.size());
	auto end1 = chrono::steady_clock::now();
	int insertiontime = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
	cout << "Insertion Sort Time: "
		<< insertiontime
		<< " ns" << endl;
	auto start2 = chrono::steady_clock::now();
	quickSort(numbs1, 0, numbs1.size() - 1);
	auto end2 = chrono::steady_clock::now();
	int quicktime = chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
	cout << "Quick Sort Time: "
		<< quicktime
		<< " ns" << endl;
	auto start3 = chrono::steady_clock::now();
	merge_sort(numbs2, 0, numbs2.size() - 1);
	auto end3 = chrono::steady_clock::now();
	int mergetime = chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count();
	cout << "Merge Sort Time: "
		<< mergetime
		<< " ns" << endl;
	auto start4 = chrono::steady_clock::now();
	heapSort(numbs3, numbs3.size());
	auto end4 = chrono::steady_clock::now();
	int heaptime = chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count();
	cout << "Heap Sort Time: "
		<< heaptime
		<< " ns" << endl;
	cout << endl;
	cout << "Searching for " << q.getName() << endl;
	cout << "======================================" << endl;
	Node* root = NULL;
	root = insert(root, numbs[numbs.size() / 2]);
	insert1(numbs, 0, numbs.size() / 2, root);
	insert1(numbs, numbs.size() / 2 + 1, numbs.size(), root);
	cout << "INSERT BÝTTÝ" << endl;
	auto start5 = chrono::steady_clock::now();
	search(root, q);
	auto end5 = chrono::steady_clock::now();
	int bsttime = chrono::duration_cast<chrono::nanoseconds>(end5 - start5).count();
	cout << "The search in BST took "
		<< bsttime
		<< " ns" << endl;

	avl_tree avl;
	for (int i = 0; i < numbs.size(); i++)
	{
		r = avl.insert(r, numbs[i]);
	}
	avl.inorder(r);
	auto start6 = chrono::steady_clock::now();
	avl.search(r, q);
	auto end6 = chrono::steady_clock::now();
	int avltime = chrono::duration_cast<chrono::nanoseconds>(end6 - start6).count();
	cout << "The search in AVL took "
		<< avltime
		<< " ns" << endl;
	auto start7 = chrono::steady_clock::now();
	binarySearch(numbs, 0, numbs.size(), q);
	auto end7 = chrono::steady_clock::now();
	int binarytime = chrono::duration_cast<chrono::nanoseconds>(end7 - start7).count();
	cout << "Binary search time "
		<< binarytime
		<< " ns" << endl;
	cout << endl;
	cout << "SpeedUps in search" << endl;
	cout << "======================================" << endl;
	double bstavl = bsttime / (double)avltime;
	double bsavl = binarytime / (double)avltime;
	double bsbst = binarytime / (double)bsttime;
	cout << "(BST / AVL) SpeedUp  = " << bstavl << endl;
	cout << "(Binary Search / AVL) SpeedUp  = " << bsavl << endl;
	cout << "(Binary Search / BST) SpeedUp  = " << bsbst << endl;
	cout << endl;
	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	double insqu = insertiontime / (double)quicktime;
	double merqu = mergetime / (double)quicktime;
	double hequ = heaptime / (double)quicktime;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << insqu << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << merqu << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << hequ << endl;
	//	printArray(numbs, numbs.size() - 1);
	//	printArray(numbs1, numbs1.size() - 1);
	//	printArray(numbs2, numbs2.size() - 1);
	//	printArray(numbs3, numbs3.size() - 1);
	system("pause");
	return 0;
	//printArray(arr, n);
}