/**
 * @file main.cpp
 * @author @warning Fill in your full name
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <iostream>
#include "bag.h"
#include "language.h"
///@warning Fill missing #include
#include <string>

using namespace std;


/**
 * @brief Shows final data in a form detectable by autovalidation scripts
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param nwords Number of words found
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b,
        int nwords, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    const int BAG_LEGTH = 5;
    Bag bag;
    string word, lang, result="";
    int random, count;
    
    cout << "TYPE LANGUAGE(es/en): ";
    cin >> lang;               ///  Read language
    Language language(lang);
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl; /// Show allowed letters
    cout << "TYPE SEED (<0 RANDOM): ";
    // Do while
    cin >> random; /// @warning Read random and define bag
    if (random >= 0)
        bag.setRandom(random);
    
    /// @warning  define bag 
    bag.define(lang);
    
    /// @warning Extract a 5-letter word from the bag
    /// check whether it is in the dictionary or not
    /// if it is, count a new word, and aggregate the 
    /// word to result ... result = result + word +" - ";
    do{
        word = toISO(bag.extract(random)); 
        if(language.query(word)){
            result.append(word + "*");
        }  
    }while(bag.size() >= BAG_LEGTH);
    
    
    /// @warning Finish when the bag is empty and show results
    /// thru HallOfFame(...))
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

