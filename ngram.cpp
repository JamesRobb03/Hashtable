#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> HTSI;


//Sorts floats so largest percentages are first in the list. when sorting the floats also move the strings so that they match positions.
//make it so that if the percentages equal and the strings are the same to set string to "" and float to 0.
//then when printing only print vectors which are not equal to 0
void sort(vector<float> *a, vector<string> *b){
    for (int i = 0; i < int(a->size() -1); ++i)
    {
        for (int j = i+1; j < int(a->size() - 1); ++j)
        {
          float temp =0;
          string tempS="";
          if (a->at(i) < a->at(j))
            {
                temp = a->at(i);
                a->at(i) = a->at(j);
                a->at(j) = temp;

                tempS = b->at(i);
                b->at(i) = b->at(j);
                b->at(j) = tempS;


            }  
        }
    }

}

float round(float var) 
{ 
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 

bool beenUsed(string s, vector<string> *a){
    for (int i = 0; i < 9; ++i)
    {
        if (s == a->at(i))
        {
            return true;
        }
    }

    return false;
}

void finalPrint(vector<float> *a, vector<string> *b, int ngramAmount){
    vector<string> *duplicates;
    duplicates = new vector<string>;
    duplicates->reserve(10);
    duplicates->resize(10);

    int elements = 0;
    int i = 0;
    while(elements<10)
    {
        if (i>ngramAmount-1)
        {
            return;
        }

        if (beenUsed(b->at(i), duplicates) == false)
        {
            cout<<a->at(i)<<":"<<b->at(i)<<endl;
            duplicates->at(elements) = b->at(i);
            elements++;
        }
        i++;

    }
}


int main(int argc, char const *argv[])
{
    HTSI hashtable;
    ifstream file;
    string s="";
    char letter;
    int numchars = 3;

    if (argc != 2)
    {
        cerr << argv[0] << " requires an argument (filename)" << endl;
        return 1;
    }

    file.open(argv[1]);
    if (!file)
    {
        cerr<<"Could not read file" <<endl;
        return 1;
    }

    int ngramCount = 0;
    //while loop which goes through text file and adds ngrams to hashtable.;
    while(file.get(letter))
    {
        if (letter == '\n')
        {
            continue;
        }

        s += letter;
        int size = s.length();
        if (size == numchars)
        {
            ngramCount++;
            //cout << s << endl;
            hashtable.insert(s, 1);
            int count = hashtable.getDuplicates(s);
            if (count>0)
            {
                int val = hashtable.getValue(s);
                hashtable.erase(s);
                val = val +1;
                hashtable.insert(s, val);
            }
            s = s.substr(1);
        }
    }
    file.close();

    vector<string> *ngrams;
    ngrams = new vector<string>;
    ngrams->reserve(ngramCount);
    ngrams->resize(ngramCount);

    file.open(argv[1]);
    //This is a loop which creates an array of all the ngrams;
    s="";
    int index=0;
    while(file.get(letter))
    {
        if (letter == '\n')
        {
            continue;
        }
        s+= letter;
        int size = s.length();
        if (size == numchars)
        {
            ngrams->at(index) = s;
            //cout<<ngrams->at(index)<<endl;
            index++;
            s = s.substr(1);

        }
    }
    file.close();

    vector<float> *perc;
    perc = new vector<float>;
    perc->reserve(ngramCount);
    perc->resize(ngramCount);

    //loop through list of ngrams. get value assosciated to ngram and then works out the percentage for that ngram.
    for (int i = 0; i < int(ngramCount-1); ++i)
    {
        string key = ngrams->at(i);
        int val = hashtable.getValue(key);
        float percentage = float(val)/float(ngramCount)*100;
        percentage = round(percentage);
        perc->at(i) = percentage;
    }

    sort(perc, ngrams);

    // for (int i = 0; i < ngramCount; ++i)
    // {
    //     cout<<ngrams->at(i)<<":"<<perc->at(i)<<endl;
    // }

    finalPrint(perc, ngrams, ngramCount);
    return 0;
}





//need a sort function.
//need an array of strings.

//Add substring to hashtable as key with value of 0
//after this check count of key just added. 
//store count and erase node.
//add substring back into the hashtable with value of count.


//THIS IS CODE 6 FROM WEEK 11
// int main(int argc, char* argv[]) {
//     ifstream file;
//     string s = "";
//     int numchars = 0;
//     char letter;
//     stringstream stream;

//     if (argc != 3){
//         cerr << argv[0] << " requires two arguments" << endl;
//         return 1;
//     }

//     file.open(argv[1]);
//     if (!file) {
//         cerr << "Could not read file" << endl; 
//         return 1; 
//     }

//     stream << argv[2];
//     stream >> numchars;

//     while(file.get(letter)) {
//         if(letter == '\n'){
//             continue;
//         }
//         s += letter;
//         int size = s.length();
//         if (size == numchars){
//             cout << s << endl;
//             s = s.substr(1);
//         }
//     }
// }
