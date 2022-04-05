#include <bits/stdc++.h>
#define ll long long int

using namespace std;

class ArrayVector {
public:
ArrayVector(); // constructor
int size() const; // number of elements
bool empty() const; // is vector empty?
int& operator[](int i); // element at index
int at(int i); // element at index
void erase(int i); // remove element at index
void insert(int i, const int& e); // insert element at index
void reserve(int N); // reserve at least N spots

private:
int capacity; // current array size
int n; // number of elements in vector
int* A; // array storing the elements
};

ArrayVector::ArrayVector() // constructor
: capacity(0), n(0), A(NULL) { }

int ArrayVector::size() const // number of elements
{ return n; }

bool ArrayVector::empty() const // is vector empty?
{ return size() == 0; }

int& ArrayVector::operator[](int i) // element at index
{ return A[i]; }
// element at index (safe)
int ArrayVector::at(int i) {
	if (i < 0 || i >= n){
		cout<<"Error : Terminating";
		return INT_MIN;
	}
	return A[i];
}

void ArrayVector::reserve(int N) { // reserve at least N spots
if (capacity >= N) return; // already big enough
int* B = new int[N]; // allocate bigger array
for (int j = 0; j < n; j++) // copy contents to new array
B[j] = A[j];
if (A != NULL) delete [] A; // discard old array
A = B; // make B the new array
capacity = N; // set new capacity
}

void ArrayVector::insert(int i, const int& e) {
if (n >= capacity) // overflow?
reserve(max(1, 2 * capacity)); // double array size
for (int j = n - 1; j >= i; j--) // shift elements up
A[j+1] = A[j];
A[i] = e; // put in empty slot
n++; // one more element
}

void ArrayVector::erase(int i) { // remove element at index
for (int j = i+1; j < n; j++) // shift elements down
A[j - 1] = A[j];
n--; // one fewer element
}




typedef int Elem; // list base element type
class NodeList { //node base type List
private:
struct Node { //nested struct inside class
	int elem;
	Node* next;
	Node* prev;
};

public:
class Iterator { //nested class
Node* v; //pointer to node
Iterator(Node* x); //create from node
public:
//dereference operator that access data stored
int& operator*();
//comparison operator to check if two iterators pointing/not pointing to same object (not just value)
bool operator==(const Iterator& p) const;

bool operator!=(const Iterator& x) const; //to same object (not just value)
Iterator& operator++(); //move to next position and return referance to it
Iterator operator++(int);
Iterator& operator--(); //move to previous position and return referance to it
//only Node list can access private memers and create new operator
friend class NodeList;
};

private:
Node* header; //head of the list
Node* trailer; //tail of the list

int n; //node counter
public:
NodeList(); //constructor
NodeList(NodeList& L);
~NodeList(); //destructor
int size() const;
bool empty() const;
Iterator begin() const; //beggining position
Iterator end() const; //position after last node
void operator=(NodeList& L);
void insertFront(int value); //invoke insert(begin(), value)
void insertBack(int value); //invoke insert(end(), value)
void insert(const Iterator& p, int value); //insert Element before position p
void eraseFront(); //invoke erase(begin())
//invoke erase(--end()), have to decrement to position backwards one node
void eraseBack();
void erase(const Iterator& p); //remove element at position p
int getFront();
int getBack();
};

int NodeList::getFront(){
	if(empty()) return INT_MIN;
	return header->next->elem;
}
int NodeList::getBack(){
	if(empty()) return INT_MIN;
	return trailer->prev->elem;
}

NodeList::NodeList() { // constructor
	n = 0; // initially empty
	header = new Node; // create sentinels
	trailer = new Node;
	header->next = trailer; // have them point to each other
	trailer->prev = header;
}

NodeList::~NodeList() {
	while (!empty())
		eraseFront();
	delete header;
	delete trailer;
}

int NodeList::size() const // list size
{ return n; }

bool NodeList::empty() const // is the list empty?
{ return (n == 0); }

NodeList::Iterator NodeList::begin() const // begin position is first item
{ return Iterator(header->next); }

NodeList::Iterator NodeList::end() const // end position is just beyond last
{ return Iterator(trailer); }

NodeList::Iterator::Iterator(Node* u) // constructor from Node*
{ v = u; }

Elem& NodeList::Iterator::operator*() // reference to the element
{ return v->elem; }

bool NodeList::Iterator::operator==(const Iterator& p) const // compare positions
{ return v == p.v; }

bool NodeList::Iterator::operator!=(const Iterator& p) const
{ return v != p.v; }

NodeList::Iterator& NodeList::Iterator::operator++() // move to next position
{ v = v->next; return *this; }

NodeList::Iterator& NodeList::Iterator::operator--() // move to previous position
{ v = v->prev; return *this; }

void NodeList::insert(const Iterator& p, int value) { //insert element before p
	Node* position = p.v; //pointer to p's node
	Node* predecessor = position->prev; //u is a pointer to p's previous node
	Node* newNode = new Node; //new node to insert
	newNode->elem = value;
	//newNode's next is pointing to position, and position's previous to newNode
	newNode->next = position; position->prev = newNode;
	//newNode's previous is pointing to previous, and previous next to newNode
	newNode->prev = predecessor; predecessor->next = newNode;
	n++; //increment n by 1
}

void NodeList::insertFront(int value) {
	return insert(begin(), value);
}

void NodeList::insertBack(int value) {
	return insert(end(), value);
}

void NodeList::erase(const Iterator& p) {
	Node* oldNode = p.v;
	Node* predecessor = oldNode->prev; //set position's predecessor
	Node* successor = oldNode->next; //set position's next node
	predecessor->next = successor; successor->prev = predecessor; //change links
	delete oldNode;
	n--; //decrement n by 1
}

void NodeList::eraseFront() {
	return erase(begin());
}
void NodeList::eraseBack() {
	return erase(--end());
}

vector<int> BubbleSort(vector<int>& v){
	for(int j=0;j<v.size();j++){
		for(int i=0;i<v.size()-1;i++)
			if(v[i]>v[i+1]) swap(v[i],v[i+1]);
	}
	return v;
}

void solve()
{
	vector<int>v={5,3,7,2,9},v1;
	v1=BubbleSort(v);
	for(auto& val:v1)
		cout<<val<<" ";
	cout<<endl;
}

int main()
{
	solve();

	return 0;
}