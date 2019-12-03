#include <iostream>

using namespace std;
template<typename T>
class ArrayList {
    public:
    // Types
        // value_type
        typedef T value_type;
        // iterator
        class iterator {
          public:
            iterator(T *l){
              loc = l;
            }
            iterator(){
              loc = nullptr;
            }
            iterator(const iterator &i) {
              loc = i.loc;
            };
            T &operator*(){
              return *loc;
            };
            bool operator==(const iterator &i) const {
              //cout << "equality check " << (loc == i.loc ? "true" :"false") << endl;
              return loc == i.loc;
            };
            bool operator!=(const iterator &i) const {
              //cout << "inequality check " << (loc != i.loc ? "true" :"false") << endl;
              return loc != i.loc;
            };
            iterator &operator=(const iterator &i) {
              loc = i.loc;
              return *this;
            };
            iterator operator++(int){
              iterator ret = iterator(loc);
              loc++;
              return ret;
            };
            iterator operator--(int) {
              iterator ret = iterator(loc);
              loc--;
              return ret;
            };
            iterator &operator++(){
              loc++;
              return *this;
            };
            iterator &operator--(){
              loc--;
              return *this;
            };
          private:
            T* loc;
        };

        // const_iterator
        class const_iterator {
          public:
            const_iterator(const T *l){
              loc = l;
            }
            const_iterator(){
              loc = nullptr;
            }
            const_iterator(const const_iterator &i) {
              loc = i.loc;
            };
            const T &operator*(){
              return *loc;
            };
            bool operator==(const const_iterator &i) const {
              //cout << "equality check " << (loc == i.loc ? "true" :"false") << endl;
              return loc == i.loc;
            };
            bool operator!=(const const_iterator &i) const {
              //cout << "inequality check " << (loc != i.loc ? "true" :"false") << endl;
              return loc != i.loc;
            };
            const_iterator &operator=(const const_iterator &i) {
              loc = i.loc;
              return *this;
            };
            const_iterator operator++(int){
              const_iterator ret = const_iterator(loc);
              loc++;
              return ret;
            };
            const_iterator operator--(int) {
              const_iterator ret = const_iterator(loc);
              loc--;
              return ret;
            };
            const_iterator &operator++(){
              loc++;
              return *this;
            };
            const_iterator &operator--(){
              loc--;
              return *this;
            };
          private:
            const T* loc;
        };

        // General Methods
        ArrayList();
        ArrayList(const ArrayList &that);
        ArrayList<T> &operator=(const ArrayList<T> &al);

        ~ArrayList();
        void push_back(const T &t);           // add to the end.
        T& pop_back();                      // remove last element.
        int size() const;
        void clear();
        void insert(const T &t,int index);    // insert this element before the given index.
        const T &operator[](int index) const; // get the element at index.
        T &operator[](int index);             // get the element at index.
        void remove(int index);               // remove the item at the given index.

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
      private:
        T* array;
        int arrayCap;
        int numElems;
        void checkAndGrow();
};

template<typename T>
ArrayList<T>::ArrayList():array{new T[10]},arrayCap{10},numElems{0} {
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList &that){
  arrayCap = that.arrayCap;
  numElems = that.numElems;
  array = new T[that.arrayCap];
  for(int i=0; i<numElems; i++) {

    array[i] = that.array[i];
  }
}

template<typename T>
ArrayList<T>::~ArrayList() {
  if(array)
    delete[] array;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T> &al){
  if(array)
    delete[] array;
  arrayCap = al.arrayCap;
  numElems = al.numElems;
  array = new T[al.arrayCap];
  for(int i=0; i<numElems; i++) {
    array[i] = al.array[i];
  }
  return *this;
}

template<typename T>
void ArrayList<T>::push_back(const T &t){
  checkAndGrow();
  array[numElems] = t;
  numElems++;
}

template<typename T>
T& ArrayList<T>::pop_back(){
  if(numElems < 1)
    throw "No elements in list";
  return array[--numElems];
}

template<typename T>
int ArrayList<T>::size() const{
  return numElems;
}

template<typename T>
void ArrayList<T>::clear(){
  numElems = 0;
}

template<typename T>
void ArrayList<T>::insert(const T &t,int index){
  checkAndGrow();
  for(int i=numElems; i>index; --i) {
    array[i] = array[i+1];
  }
  array[index] = t;
  ++numElems;
}

template<typename T>
const T &ArrayList<T>::operator[](int index) const{
  if(index >= numElems)
    throw "Index out of bounds";
  return array[index];

}

template<typename T>
T &ArrayList<T>::operator[](int index){
  if(index >= numElems)
    throw "Index out of bounds";
  return array[index];
}

template<typename T>
void ArrayList<T>::remove(int index){
  if(index >= numElems)
    throw "Index out of bounds";
  for(int i=index; i < numElems-1; i++) {

    array[i] = array[i+1];
  }
  numElems--;
}

template<typename T>
void ArrayList<T>::checkAndGrow() {
  if( numElems >= arrayCap ){
      T* bigger = new T[arrayCap*2];
      for(int i=0; i<numElems; i++)
      {
          bigger[i] = array[i];
      };
      delete[] array;
      array = bigger;
      arrayCap = arrayCap*2;
  }
}

template<typename T>
typename ArrayList<T>::iterator ArrayList<T>::begin(){
  return ArrayList<T>::iterator(&array[0]);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::begin() const {
  return ArrayList<T>::const_iterator(&array[0]);

}

template<typename T>
typename ArrayList<T>::iterator ArrayList<T>::end() {
  return ArrayList<T>::iterator(&array[numElems]);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::end() const {
  return ArrayList<T>::const_iterator(&array[numElems]);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::cbegin() const {
  return ArrayList<T>::const_iterator(&array[0]);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::cend() const {
  return ArrayList<T>::const_iterator(&array[numElems]);
}
