#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "HashTable.h"
#include <iomanip>
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
//function which rounds to two decimal places
float round(float var) 
{ 
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 
//returns true if item has already been used
//used to prevent printing duplicates.
bool beenUsed(string s, vector<string> *a, int outputNum){
    for (int i = 0; i < outputNum-1; ++i)
    {
        if (s == a->at(i))
        {
            return true;
        }
    }

    return false;
}
//function which prints the list
void finalPrint(vector<float> *a, vector<string> *b, int ngramAmount, int outputNum){
    vector<string> *duplicates;
    duplicates = new vector<string>;
    duplicates->reserve(outputNum);
    duplicates->resize(outputNum);

    int elements = 0;
    int i = 0;
    while(elements<outputNum)
    {
        if (i>ngramAmount-1)
        {
            return;
        }

        if (beenUsed(b->at(i), duplicates, outputNum) == false)
        {
            std::cout << std::setprecision(2) << std::fixed;
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
    stringstream stream;
    stringstream stream2;
    int outputNum = 10;
    if (argc == 1)
    {
        file.open("inputfile.txt");
    }

    else if (argc == 2)
    {
        file.open(argv[1]);
    }
    else if (argc == 3)
    {
        file.open(argv[1]);
        stream << argv[2];
        stream >> numchars;
        if (numchars<1)
        {
            cout << "ngram length must be greater than 0"<<endl;
            return 0;
        }
    }
    else if (argc == 4){
        file.open(argv[1]);
        stream << argv[2];
        stream >> numchars;
        stream2 << argv[3];
        stream2 >> outputNum;
        if (numchars<1)
        {
            cout << "ngram length must be greater than 0"<<endl;
            return 0;
        }
        if (outputNum<1)
        {
            cout << "number of top most frequent n-grams to output must be greater than 0"<<endl;
            return 0;
        }
    }
    else{
        cout<<"To many arguments. please try again"<<endl;
        return 0;
    }

    if (!file)
    {
        cerr<<"Could not read file. Check if file exists." <<endl;
        return 0;
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

    if (argc == 1)
    {
        file.open("inputfile.txt");
    }
    else{
        file.open(argv[1]);
    }
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
    for (int i = 0; i < int(ngramCount); ++i)
    {
        string key = ngrams->at(i);
        int val = hashtable.getValue(key);
        float percentage = float(val)/float(ngramCount)*100;
        percentage = round(percentage);
        perc->at(i) = percentage;
    }

    sort(perc, ngrams);
    finalPrint(perc, ngrams, ngramCount, outputNum);

    return 0;
}