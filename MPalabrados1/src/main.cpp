/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <cassert>
#include <iostream>
#include "language.h"
#include "bag.h"

using namespace std;

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param nwords Number of words found
 * @param score Number of points scored
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b,
        int nwords, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    Bag bag;
    string word, lang, result="";
    int random, count=0, max, maxId;
    max = -1;
    cout << "TYPE LANGUAGE: ";
    cin >> lang;
    Language language(lang);
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    cout << "TYPE SEED (<0 RANDOM): ";
    cin >> random; 
    if (random >= 0)
        bag.setRandom(random);
    bag.define(language);
    count = 0;
    cout << "BAG ("<<random<<"-"<<bag.size()<<") : "<<toUTF(bag.to_string())<< endl;
    do {
        word = bag.extract(5);
        cout << toUTF(word);
        if (language.query(word)) {
            count++;
            cout <<" ***";
            result += word + " - ";
        }
        cout << endl;
    }while (bag.size()>0);
    HallOfFame(language,random, bag,count,result);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b,  
        int nwords, const string &result) {
    cout << endl <<"%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << nwords << " words found "<<endl << 
            toUTF(result) << endl;    
}


