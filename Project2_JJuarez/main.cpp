//
//  main.cpp
//  Project2_JJuarez
//
//  Created by Julio  on 11/19/18.
//  Copyright © 2018 Julio . All rights reserved.
//
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include "bst.cpp"

using namespace std;

struct lettersOnly: ctype<char> //structure for letter only word format, ignoring symbols and punctuation.
{
    lettersOnly(): ctype<char>(get_table()) {}
    
    static ctype_base::mask const* get_table()
    {
        static vector<ctype_base::mask>
        rc(ctype<char>::table_size,ctype_base::space);
        
        fill(&rc['A'], &rc['z'+1], ctype_base::alpha);
        return &rc[0];
    }
};

void statistics(int);                 // prints statistics, number or words and unique words, average or letters and words, check sentence length
ifstream inputfile(string&);          //opens file, checks file exists
void addWordstoMap(map <string,int>&,ifstream&); //goes through file adding words to map as keys & occurrences as values
void countSentences (ifstream&);                 //counts sentences in file by using "." as delimiter
void insertToTrees(map <string,int>&,ifstream&,ifstream&,BST&, BST&,int); //inserts words to trees accordingly, T has every word, moreThanTree gets unique words longer than 3 letters and with a occurences higher than 5%

int NumberWords;
int moreThanThree;
int totalLetters;
int totalSentences;
int main()
{
    BST T;
    BST MoreThanThree;
    NumberWords = 0;
    totalLetters = 0;
    moreThanThree = 0;
    totalSentences = 0;
    string path;
    string wordSearch;
    int fivePercent = 0;
    
    map <string, int> wordCount;                 //creating a map with words in which words will be added as keys and occurrences as values.

    ifstream input;
    ifstream inputS;
    cout << "Enter file name: "<< endl;
    cin >> path;
    input = inputfile(path);                    // opens a file with the struct to ignore punctuation & symbols.
    inputS.open(path);                         // inputS will remain with punctuation to check sentences.
    addWordstoMap(wordCount, input);             //for loop adding words as keys & occurences as values
    fivePercent = wordCount.size()*.05;          //get 5% of unique words
    countSentences(inputS);                     // count sentences in inputS (unmodified)
    
    insertToTrees(wordCount, input, inputS, T, MoreThanThree, fivePercent);//insert words accordingly to two trees, T has unique words with out any punctuation, MoreThanThree gets words with the most occurrences longer than 3 characters. 
    
    cout << "Enter the word you're looking for: " <<endl;
    cin >> wordSearch;                         //word search ignoring upper case letters.
    transform(wordSearch.begin(), wordSearch.end(), wordSearch.begin(), ::tolower); //ignores search input uppercase
    T.search(wordSearch);
    
    
    statistics ((int)wordCount.size());        //function to print results
    

    chrono::seconds dura(3);                   //pause to look at search before printing Syntax
    this_thread::sleep_for( dura );
    
    
    cout << "Words used too often warning,  list of words: " << endl << endl;
    MoreThanThree.display();
    
    this_thread::sleep_for( dura );           //Pause to look at words before index
    
    cout << endl << "INDEX: " << endl;
    T.displayIndex();
    
    
    return 0; 
}
void insertToTrees(map <string,int>& wordCount,ifstream& input,ifstream& inputS,BST& T, BST& MoreThanThree,int fivePercent)
{
    
    for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
    {
        T.insert(it->first,it->second);         //iterate thorugh map, adding unique words to tree
        if(it->first.size()>3)
        {
            moreThanThree++;                    // if item being iterated through is longer than 3 characters add to counter
        }
        if((it->first.size()>3)&&it->second>fivePercent)
        {
            MoreThanThree.insert(it->first,it->second);   // Add items longer than 3 characters and longer than 5% of unique words to a new tree
        }
    }
}

void addWordstoMap(map <string,int>& wordCount,ifstream& input)
{
    string word;
    while(input>>word)                                // while input has words in it
{
    NumberWords++;                                    // count number of words
    transform(word.begin(), word.end(), word.begin(), ::tolower); // turn words to lower case.
    ++wordCount[word];                               // Add words as keys and occurrences as values in a map.
    totalLetters += word.size();                     // count letters as it iterates through the file
}
    
}

void countSentences (ifstream& inputS)
{
    string line;
    const char EOL = '.';
    while (getline (inputS, line, EOL))               // count sentences in inputS (unmodified)
    {
        totalSentences++;
    }
}

ifstream inputfile(string& path)
{
        ifstream masterfile;
        masterfile.imbue(locale(locale(), new lettersOnly()));
        masterfile.open(path);
        while (!masterfile)
        {
            cout << "warning: cannot open file" << endl;
            cout << "Enter file name: " << endl;
            cin>>path;
            masterfile.open(path);
        }
        return masterfile;

}


void statistics (int wordCount)
{
    int averageWordL = totalLetters/NumberWords; //calculate average word length
    int averageWpS = NumberWords/totalSentences; //calculate average words per sentence
    cout << "Total number of words: " << NumberWords << endl;;
    cout<< "Total number of unique words: "  << wordCount<< endl;
    cout << "Total number of unique words longer than 3 letters: " << moreThanThree << endl;
    cout << "Average word length: " << averageWordL << endl;
    cout << "Average words per sentence: " << averageWpS << endl;
    cout << endl << "             Syntax Warnings:     " << endl;
    if (averageWpS>10)
        {
            cout << "Sentence warning, average sentence is longer than 10 words "<<"("<<averageWpS<<")"<<endl;
        }
}
