#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

typedef HashNode<string,int> HNSI;
typedef HashTable<int,string> HTSI;

// bool test2() {
//   HTSI T1(117); 
//   int s;

//   T1.insert("Hello",17);
//   T1.insert("World",19);
//   T1.insert("abc",12);

//   if (T1.getValue("Hello") != 17 || T1.getValue("abc")!=12 || T1.getValue("World") != 19) {
//     cout << "Values are not stored correctly. T1" << endl;
//     return false;
//   }

//   s = T1.size();
//   T1.rehash(2*s);
//   if (T1.size() < 2*s) { 
//     cout << "rehash does not work correctly." << endl;
//     return false;
//   }

//   cout<<"Made it to here 1"<<endl;

//   if (T1.getValue("Hello") != 17 || T1.getValue("abc")!=12 || T1.getValue("World") != 19) {
//     cout << "Values are not stored correctly." << endl;
//     return false;
//   }

//   cout<<"Made it to here 2"<<endl;

//   T1.insert("AAAA",39);
//   T1.insert("AAA",42);
//   T1.insert("A",76);
//   if (T1.getValue("AAAA") != 39 || T1.getValue("A")!=76 || T1.getValue("AAA") != 42) {
//     cout << "Values are not stored correctly." << endl;
//     return false;
//   } 

//   T1.erase("AAA");
//   T1.erase("World");

//   if (T1.getValue("Hello") != 17 || T1.getValue("abc")!=12 || T1.getValue("AAAA") != 39 || T1.getValue("A")!=76) {
//     cout << "Values are not stored correctly." << endl;
//     return false;
//   }
//   return true;
// }

int main() {
    
  //test2();
  HTSI T1(5); 
  int s;
  s = T1.size()*10;
  cout << s << endl;
  for (int i = 0; i < s; ++i)
  {
    T1.insert(i,"test");
  }
  return 1;
}