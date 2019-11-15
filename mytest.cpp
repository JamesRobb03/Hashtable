#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashNode<string,int> HNSI;
typedef HashTable<string,int> HTSI;

int main() {
  
  HNSI N;
  N.assign("Hello", 1);

  cout << "Key = " << N.getKey() << endl;
  cout << "Value = " << N.getValue() << endl;

  HTSI T1(132);
  T1.insert("AAAA",4);
  T1.insert("AAA",3);
  T1.insert("A",1);
  int val = T1.getValue("AAAA");
  cout << "VALUE: "<<val << endl;

  return 1;
}