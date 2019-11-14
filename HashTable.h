#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

template <class KeyType, class ValueType>
class HashTable {
  typedef vector <HashNode<KeyType,ValueType> > Table;
  Table *table; // size of table (# of buckets) is stored in the Table data structure
  int num;   // number of entries stored in the HashTable;

public:
  HashTable();        // constructor, initializes table of size 11;
  HashTable(int);  // constructor, requires size of table as arg
  //~HashTable();       // deconstructor

  int size();      // returns size of the hash table (number of buckets)
  int hash_function(KeyType);  // the table's hash function
  ValueType getValue(KeyType);    // find and return data associated with key

  void insert(KeyType,ValueType); // insert data associated with key into table
  //void erase(KeyType);            // remove key and associated data from table

  //void rehash(int); // sets a new size for the hash table, rehashes the hash table 
  // extend if necessary
};

template <class KeyType, class ValueType>
int HashTable<KeyType,ValueType>::size() {
  return table->size();
}

/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(){
  table = new Table(11);
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(int S){
  table = new Table(S);
}

template <class KeyType>
int HashTable::hash_function(KeyType k){
  return k % table->size();
}

int HashTable::hash_function(string k){
  int sum;
  long p = 1;
  for (char c : s)
  {
    sum = (sum + (c - 'a' + 1) * p ) % table->size();
    p = p * 31
  }
}

template <class KeyType>
ValueType HashTable::getValue(KeyType k){
  int index = hash_function(k);
  return table(index)->getValue;
}

template <class KeyType, class ValueType>
void HashTable::insert(KeyType k,ValueType v){
  int index = hash_function(k);
  table(index)->assign(k, v);
}


#endif