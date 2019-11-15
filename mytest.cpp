#include <iostream>
#include <string>

#include "HashNode.h"

using namespace std;

typedef HashNode<string,int> HNSI;

int main() {
  
  HNSI N;
  N.assign("Hello", 1);

  cout << "Key = " << N.getKey() << endl;
  cout << "Value = " << N.getValue() << endl;

  return 1;
}