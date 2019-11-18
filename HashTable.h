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
  void erase(KeyType);            // remove key and associated data from table

  void rehash(int); // sets a new size for the hash table, rehashes the hash table 
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
  table = new Table();
  table->reserve(11);
  table->resize(11);
  this->num = 0;
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(int S){
  table = new Table();
  table->reserve(S);
  table->resize(S);
  this->num = 0;
}

//hash function
template <class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::hash_function(KeyType k){
  size_t hashVal = hash<KeyType>()(k);
  int intHash = hashVal % table->size();
  return intHash;
}

//INSERT VALUE
//add check for duplicate key.
template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType k, ValueType v){
  int index = hash_function(k);
  int counter = 0;
  while(true){
    if (table->at(index).isEmpty()==true)
    {
      table->at(index).assign(k,v);
      return;
    }else{
      index++;
      counter++;
      if (index > (table->size() - 1))
      {
        index = 0;
      }
      if (counter > (table->size())/2)
      {
        cout << "TABLE SIZE: "<<table->size() << endl;
        cout << "TABLE SIZE / 2: " << table->size()/2 << endl;

        rehash(table->size() * 2);
        cout << "REHASHED TABLE"<< endl;
      }
    }
  }
}

//GET VALUE
//add counter so that can return not found if counter > table size
template <class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValue(KeyType k){
  int index = hash_function(k);
  while(true){
    if (index > (table->size()-1))
    {
      index = 0; 
    }
    //cout << "INDEX = " << index << " KEY AT INDEX = " << table->at(index).getKey() << " LOOKING FOR = " << k <<  endl; 
    KeyType key = table->at(index).getKey();
    if (key != k)
    {
      index++;
    }
    else if (key == k && table->at(index).isEmpty()==true)
    {
      index++;
    }
    else
    {
      ValueType val = table->at(index).getValue();
      return val;
    }
  }
}


//ERASE FUNCTION.
//add counter so that return not found if key cannot be found.
template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::erase(KeyType k){
  //get index of key k.
  int index = hash_function(k);
  int counter = 0;
  while(true){

    //checks to see if every item in the table has been checked.
    if (counter > table->size())
    {
      cout<<"KEY NOT FOUND"<<endl;
      return;
    }

    if (index > (table->size() - 1))
    {
      index = 0;
    }

    KeyType key = table->at(index).getKey();
    // if key at index is not the the same as k then add 1 to index
    if (key != k)
    {
      index++;
      counter++;
    }
    else if (key == k && table->at(index).isEmpty() == true)
    {
      index++;
      counter++;
    }
    else
    {
      //set the table to empty so that it can be inserted into
      table->at(index).setEmpty();
      return;
    }
  } 
}


template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::rehash(int newSize){
  if (newSize < table->size())
   {
    cout<<"ERROR: new table size should be bigger than orginal hashtable"<<endl;
   }else{
    //create a temp table. copy all the values into the temp table.
    //erase all values in old table.
    //resize old table.
    //rehash all values in temp table into new size table.
    //delete the temp table.

    //create tempory table
    Table *temp;
    temp = new Table();
    int s = table->size();
    temp->reserve(s);
    temp->resize(s);


    //makes a copy of the table. called temp
    for (int i = 0; i < s; ++i)
    {
      if (table->at(i).isEmpty() != true)
      {
        KeyType tempKey = table->at(i).getKey();
        ValueType tempVal = table->at(i).getValue();
        int index = hash_function(tempKey);
        bool inserted = true;
        while(inserted){
          if (temp->at(index).isEmpty()==true)
          {
            temp->at(index).assign(tempKey,tempVal);
            inserted = false;
          }else{
            index++;
            if (index > (table->size() - 1))
            {
              index = 0;
            }
          }
        }      
        //now delete entry from table.
        table->at(i).setEmpty();
      }
    }

    table->reserve(newSize);    
    table->resize(newSize);

    //copy values from old table into new sized table;
    for (int i = 0; i < s; ++i)
    {
      if (temp->at(i).isEmpty() != true)
      {
        KeyType keyToInsert = temp->at(i).getKey();
        ValueType valToInsert = temp->at(i).getValue();
        insert(keyToInsert,valToInsert);
      }
    }


    //testing purp
    // for (int i = 0; i < table->size(); ++i)
    // {
    //   cout << i << " = KEY: " <<table->at(i).getKey() << " IS EMPTY: " << table->at(i).isEmpty() << endl;
    //   cout << i << " = VAL: " <<table->at(i).getValue() << " IS EMPTY: " << table->at(i).isEmpty() << endl;

    // }
    delete temp;
   } 
 }

#endif

//TODO
/**
Rehash function
add functionality to insert that if it searches for a free space more than half the size of the hashtable then it rehashes the table.
deconstructor
try and catch stsatements
make use of num in hashtable
**/
