/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <cassert>
#include <iostream>
#include <random>
#include <fstream>

#include "language.h"
#include "bag.h"
#include "player.h"

using namespace std;

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param nwords Number of words found
 * @param score Number of letters found
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);


// main final
int main(){
    Bag bag;
    Player player;
    string word, lang, result="";
    int Id, nwords, nletters;
    
    cout << "TYPE LANGUAGE: ";
    cin >> lang;
    Language language(lang);
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    cout << "TYPE SEED (<0 RANDOM): ";
    cin >> Id;
    if (Id > 0)
        bag.setRandom(Id);
    bag.define(language);
    nwords = nletters = 0;
    
    cout << "BAG ("<<Id<<"-"<<bag.size()<<") : "<<toUTF(bag.to_string())<< endl;
    do {

        player.add(bag.extract(7-player.size()));
        cout << endl << "PLAYER: "<<toUTF(player.to_string())<<" BAG("<<bag.size()<<")"<<endl;
        cout << "INPUT A WORD: ";
        cin >> word;
        word = toISO(word);
        if (word.length()>1) {
            cout << endl << toUTF(word);
            if (player.isValid(word))  {
                if (language.query(word)) {
                    nwords++;
                    nletters += word.length();
                    result += word+" - ";
                    cout <<" FOUND!";
                } else {
                    cout << " NOT REGISTERED!";
                }
                cout << endl<<endl;
                player.extract(word);
            } else
                cout << " INVALID!" << endl;
        }
    }while (word.length()>1);
    HallOfFame(language,Id,bag,player, nwords, nletters, result);
    return 0;
} 

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout <<endl << "%%%OUTPUT" <<  endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " letters found"<<endl << 
            toUTF(result) << endl;    
}

