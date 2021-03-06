#include<iostream>
using namespace std;

template <class T>
class stack{
private:
	int sz;
	T* head;
	int space;

public:
	stack(): sz(0), head(NULL), space(0) {}
	
	stack(int curr_size): sz(curr_size), head(new T[curr_size]), space(curr_size) {}

	stack& operator=(const stack &v);

	T& operator[](int n);

	const T& operator[](int n) const;

	T top();

	void pop();

	/*passed the parameter as a const reference 
	since if T is user defined type, it is wasteful to do 
	a copy. */
	void push(const T &x);

	int size();

	void reserve(int allocate_size);

	const T* begin() const;

	const T* end() const;

	~stack() {delete[] head;}
};


template <class T>
stack<T>& stack<T>::operator=(const stack &v)
{
	if((this->head) == v.head)
		return (*this);


	if((this->space) >= v.sz)
	{
		for(int i = 0; i < v.sz; i +=1)
			(this->head)[i] = v[i];

		this->sz = v.sz;

		return (*this);
	}

	T* new_head = new T[v.sz];

	for(int i = 0; i < v.sz; i +=1)
		(new_head)[i] = v[i];

	delete[] (this->head);
	this->head = new_head;
	this->sz = v.sz;
	this->space = v.space;

	return (*this);
}

template <class T>
T& stack<T>::operator[](int n){

	try{
		if(n >= sz or n < 0){
			throw -1;
		}
	}
	catch(int thr){
		cout << "index OutOfBounds exception " << endl;
		exit(-1);
	}

	return (this->head)[n];
}

template <class T>
const T& stack<T>::operator[](int n) const{

	try{
		if(n >= sz or n < 0){
			throw -1;
		}
	}
	catch(int thr){
		cout << "index OutOfBounds exception" << endl;
		exit(-1);
	}

	return (this->head)[n];
}

template <class T>
T stack<T>::top(){

	return (this->head)[(this->sz)-1];
}

template <class T>
void stack<T>::pop(){

	try{
		if(sz == 0){
			throw -1;
		}
	}

	catch(int x){
		cout << "too many pops" << endl;
	}

	sz = sz - 1;
}

template<class T>
int stack<T>::size(){
	return sz;
}


template<class T>
void stack<T>::reserve(int allocate_size){

	if(allocate_size <= space)
		return;

	T* new_head = new T[allocate_size]; 
	delete[] head;
	head = new_head;
	space = allocate_size;
}

template<class T>
void stack<T>::push(const T &x){

	if(sz == 0)
		reserve(10);

	else if(sz == space)
		reserve(2*sz);

	(this->head)[sz] = x;
	sz+=1;
}


/*the ptrs returned from T* can be used to change the value of the
container, but we do not want to do this using an iterator, so we use
a const pointer, so it does not change the value to which it is pointing
https://www.youtube.com/watch?v=IMhdMo5wcC0
*/

/*https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration*/
/*We do not want the member function begin and end also to not change the object `this` data
hence we make it const by using const like .....begin() const { .. */
template <class T>
const T* stack<T>::begin() const{

	return (this->head);
}

template <class T>
const T* stack<T>::end const(){
	return (this->head) + sz;
}



int main()
{
	stack<int> stk;
	stk.push(12);
	stk.push(32);stk.push(132);stk.push(332);stk.push(321);
	stk.push(98);stk.push(198);stk.push(984);
	stk.pop();

	cout << stk.top() << endl;

	for(auto it = stk.begin(); it != stk.end(); ++it)
	{
		cout << (*it) << " " ;
	}

	cout << endl;
	return 0;
}