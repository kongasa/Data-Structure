class OutOfBound {};
class IllegalSize {};

#include <iostream>
#include <cstring>
using namespace std;

template <class elemType>
class seqList {
private:
	elemType *data;
	int currentLength;
	int maxSize;

	void doubleSpace();
public:
	seqList(int initSize = 10);
	seqList(const seqList &other);
	~seqList() { delete[]data; }
	void clear() { currentLength = 0; }
	int length()const { return currentLength; }
	void insert(int i, const elemType &x);
	void remove(int i);
	int search(const elemType &x)const;
	elemType visit(int i) const;
	void traverse() const;
	seqList &operator=(const seqList &other);
	seqList operator+(const seqList &other) const;
};

template <class elemType>
void seqList<elemType>::doubleSpace() {
	elemType *tmp = data;

	maxSize *= 2;
	data = new elemType[maxSize];

	for (int i = 0; i < currentLength; ++i) data[i] = tmp[i];
	delete[] tmp;
}


template <class elemType>
seqList<elemType>::seqList(int initSize) {
	if (initSize <= 0) throw IllegalSize();

	data = new elemType[initSize];
	maxSize = initSize;
	currentLength = 0;
}

template <class elemType>
seqList<elemType>::seqList(const seqList<elemType> &other) {
	currentLength = other.currentLength;
	maxSize = other.maxSize;
	data = new elemType[maxSize];
	for (int i = 0; i < currentLength; ++i)
		data[i] = other.data[i];
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
	if (i < 0 || i > currentLength) throw OutOfBound();
	if (currentLength == maxSize) doubleSpace();
	for (int j = currentLength; j > i; j--) data[j] = data[j - 1];
	data[i] = x;
	++currentLength;
}

template <class elemType>
void seqList<elemType>::remove(int i) {
	if (i < 0 || i > currentLength - 1) throw OutOfBound();
	for (int j = i; j < currentLength - 1; j++) data[j] = data[j + 1];
	--currentLength;
}

template<class elemType>
int seqList<elemType>::search(const elemType &x) const {
	int i;
	for (i = 0; i < currentLength && data[i] != x; ++i);
	if (i == currentLength) return -1;
	else return i;
}

template <class elemType>
elemType seqList<elemType>::visit(int i) const {
	if (i < 0 || i > currentLength - 1) throw OutOfBound();
	return data[i];
}

template<class elemType>
void seqList<elemType>::traverse()const {
	cout << endl;
	for (int i = 0; i < currentLength; i++) cout << data[i] << ' ';
}

template<class elemType>
seqList<elemType> &seqList<elemType>::operator=(const seqList<elemType> &other) {
	if (this == &other) return *this;

	currentLength = other.currentLength;
	if (maxSize < other.maxSize) {
		delete[] data;
		maxSize = other.maxSize;
		data = new elemType[maxSize];
	}
	for (int i = 0; i < currentLength; i++)
		data[i] = other.data[i];
	return *this;
}

template<class elemType>
seqList<elemType> seqList<elemType>::operator+(const seqList<elemType> &other)const {
	seqList<elemType> newSeqList(currentLength + other.currentLength);
	int i;
	for (i = 0; i < currentLength; i++)
		newSeqList.data[i] = data[i];
	for (i = 0; i < other.currentLength; i++)
		newSeqList.data[i + currentLength] = other.data[i];
	newSeqList.currentLength = currentLength + other.currentLength;
	return newSeqList;
}

int main() {
	try {
		char str[7];
		cin.getline(str, 7);
		int n, m;
		
		if (strcmp(str, "int") == 0) {
			int t, i = 0;
			cin >> n >> m;
			seqList<int> A(n), B(m), C(m + n);
			for (; i < n; i++) { cin >> t; A.insert(i, t); }
			for (i = 0; i < m; i++) { cin >> t; B.insert(i, t); }
			C = A + B;
			C.traverse();
		}
		if (strcmp(str, "char") == 0) {
			int  i = 0;
			char t;
			cin >> n >> m;
			seqList<char> A(n), B(m), C(m + n);
			for (; i < n; i++) { cin >> t; A.insert(i, t); }
			for (i = 0; i < m; i++) { cin >> t; B.insert(i, t); }
			C = A + B;
			C.traverse();
		}
		if (strcmp(str, "double") == 0) {
			int  i = 0;
			double t;
			cin >> n >> m;
			seqList<double> A(n), B(m), C(m + n);
			for (; i < n; i++) { cin >> t; A.insert(i, t); }
			for (i = 0; i < m; i++) { cin >> t; B.insert(i, t); }
			C = A + B;
			C.traverse();
		}
		return 0;
	}
	catch (OutOfBound) { cout << "out of bound!" << endl; return -1; }
	catch (IllegalSize) { cout << "illegal size!" << endl; return -1; }
}