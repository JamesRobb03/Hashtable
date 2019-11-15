#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashNode<string,int> HNSI;
typedef HashTable<int,int> HTSI;

int main() {
  
  HNSI N;
  N.assign("Hello", 1);

  cout << "Key = " << N.getKey() << endl;
  cout << "Value = " << N.getValue() << endl;

  HTSI T1(132);
  T1.hash_function(60);
  T1.insert(1,10);
  //T1.getValue(1);

  return 1;
}