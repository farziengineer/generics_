#include<iostream>
using namespace std;

template <class T>
class vector{

private:
	int sz;
	T *head;
	int space;

public:
	vector(): sz(0), head(NULL), space(0) {}
	
	vector(int curr_size): sz(curr_size), head(new T[curr_size]), space(curr_size) {}

	vector(const vector &x);

	vector& operator=(const vector &v);

	vector& operator=(vector &&v);

	vector operator*(vector &x); 

	T& operator[](int n);

	const T& operator[](int n) const;

	int size(); 

	int capacity();

	void reserve(int allocate_size);

	void push_back(const T &element); 

	void pop_back();

	const T* begin() const; 

	const T* end() const;
	// unblocks/frees up memory blocked/acquired by this->head
	~vector(){ delete[] this->head; }
};

template<class T>
vector<T>::vector(const vector &x){

	this->head = new T[x.space];
	this->sz = x.sz;
	this->space = x.space;

	for(int i = 0; i < x.sz; i +=1){
		(this->head)[i] = x[i];
	}
}


template <class T>
vector<T>& vector<T>::operator=(const vector &v)
{
	if((this->head) == (v.head))
		return (*this);

	if((this->space) >= v.sz)
	{
		for(int i = 0; i < v.sz; i +=1)
			(this->head)[i] = v[i];

		this->sz = v.sz;

		return (*this);
	}

	T *n_head = new T[v.sz];

	for(int i = 0; i < v.sz; i +=1)
		n_head[i] = v[i];

	delete [] (this->head);

	this->sz = v.sz;
	this->space = v.sz;
	this->head = n_head;

	return (*this);
}


template <class T>
vector<T>& vector<T>::operator=(vector &&v){

	cout << "move constructor called" << endl;

	if(this->head == (v.head))
		return (*this);

	if(this->space >= v.sz){
		delete [] (this->head);
		this->head = v.head;
		this->sz = v.sz;
		v.head = NULL;
		return (*this);
	}

	delete[] (this->head);
	this->sz = v.sz;
	this->space = v.sz;
	this->head = v.head;
	v.head = NULL;

	return (*this);
}

template<class T>
vector<T> vector<T>::operator*(vector &x)
{
	// if(x.size() != (this->size()))
	// 	return ;
	vector temp ;
	for(int i = 0; i < x.size(); i +=1)
	{
		temp.push_back((this->head)[i] * (x[i]));
	}

	return temp;
}

template<class T>
T& vector<T>::operator[](int n)
{
	try{
		if(n >= sz or n < 0)
		{
			throw -1;
		}
		
	}
	catch(int n){
		cout << endl <<  "vector index OutOfBounds exception" << endl;
		exit(-1);
	}

	return (this->head)[n];

}

template<class T>
const T& vector<T>::operator[](int n) const{

	try{
		if(n >= sz or n < 0)
		{
			throw -1;
		}
		
	}
	catch(int n){
		cout << endl <<  "vector index OutOfBounds exception" << endl;
		exit(-1);
	}

	return (this->head)[n];

}

template<class T>
int vector<T>::size()
{
	return sz;
}

template<class T>
int vector<T>::capacity()
{
	return space;
}

template<class T>
void vector<T>::reserve(int allocate_size)
{
	if(allocate_size <= (this->space))
		return;


	T *n_head = new T[allocate_size];
	for(int i = 0; i < (this->sz); i +=1)
		n_head[i] = (this->head)[i];
	
	delete [] (this->head);
	this->head = n_head;
	this->space = allocate_size;
}



template <class T>
void vector<T>::push_back(const T &element)
{
	if(sz == 0)
		reserve(10);
	else if(sz == space)
		reserve(2*sz);

	head[sz] = element;
	sz +=1;

}

template<class T>
void vector<T>::pop_back(){

	try{
		if(sz == 0)
			throw -1;
	}
	catch(int e){
		cout << "size underflow." << endl;
	}

	sz = sz - 1;
}

template <class T>
const T* vector<T>::begin() const{

	return (this->head);
}

template <class T>
const T* vector<T>::end() const{

	return (this->head + this->sz);
}

int main()
{
	vector<int> vec;
	vec.push_back(12);
	vec.push_back(34);
	vec.push_back(3);
	vec.push_back(5);

	for(int i = 0; i < vec.size(); i +=1)
		cout << vec[i] << " ";

	cout << endl;

	vector<double> dec, lec;
	dec.push_back(2.3);
	dec.push_back(234.34);
	dec.push_back(4556.23);
	dec.push_back(34.554);

	for(int i = 0; i < dec.size(); i +=1)
		cout << dec[i] << " ";

	cout << endl;

	dec.push_back(2.09);	
	lec = dec;

	for(int i = 0; i < lec.size(); i +=1)
		cout << lec[i] << " " ;

	cout << endl;

	vector<double> rec;
	rec = lec*lec;

/*	The follwing line throws error since, res[0] will evaluate to a number
	because of operator [] overloading, will have to figure out how 
	to implement this	 
	rec[0] = 23;*/


	/*Found a fix to the above problem, instead of returning T from 
	the overloaded [] operator we can return T& i.e. return a reference
	instead of the value itself, this is done so that the return value is 
	not a Rvalue. */

	rec[0] = 121;

	for(int i = 0; i < rec.size(); i +=1)
		cout << rec[i] << " ";
	cout << endl;

	cout <<"rec size before pop_back " << rec.size() << endl;
	rec.pop_back();
	cout <<"rec size after pop_back " << rec.size() << endl;


	// testing iterators
	for(auto it = rec.begin(); it != rec.end(); ++it){

		cout << (*it) << " "; 
	}

	cout << endl;
	// throws out of bounds exception
	rec[234];


	return 0;
}