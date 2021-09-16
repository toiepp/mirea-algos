#include "HashSet.h"

template<typename T>
HashSet<T>::HashSet()
	: arr(new T[16])
	, capacity(16)
	, load(0.75) {
	for (int i = 0; i < capacity; ++i) {
		arr[i] = nullptr;
	}
}

template<typename T>
HashSet<T>::HashSet(int capacity)
	: arr(new T[capacity])
	, capacity(capacity)
	, load(0.75) { }

template<typename T>
HashSet<T>::HashSet(int capacity, double load)
	: HashSet(capacity) {
	this->capacity = capacity;
	this->load = load;
}

template<typename T>
void HashSet<T>::put(T &account) {
	unsigned pos = account.hash_code();
}

template<typename T>
bool HashSet<T>::remove(T &account) {
	return false;
}

template<typename T>
T HashSet<T>::find(T &account) {
}

template<typename T>
void HashSet<T>::print() {

}

template<typename T>
void HashSet<T>::rehash() {

}