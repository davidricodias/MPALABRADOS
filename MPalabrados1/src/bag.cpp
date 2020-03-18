/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */
#include <cassert>      //Implementa la funcion assert, ¿Para debugging?. En clase no se ha mencionado así que no la uso
#include <random>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <random>

#include "bag.h"
#include "language.h"


///@warning Fill missing #include

using namespace std;

/**
 * @brief Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id);

/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 * @warning TO BE FULLY IMPLEMENTED. 
 * @warning Check parameters const/&/* and their types
 */
void removeVector(char *s, int &n, int p);


// Main methods

// Constructor
Bag::Bag() {
    nletters = 0;
    id = time(NULL);
}

void Bag::setRandom(int mid) {
    id = mid;
}

void Bag::define(const Language &l) {
    
    string local_letters = l.getLetterSet();
    
    nletters = 0;
    for (int i = 0; i < local_letters.size(); i++) {
        nletters += l.getFrequency(local_letters[i]);  
    }
        
    for (int k = 0, i = 0; i < local_letters.size(); i++) {
        for (int j = 0; j < l.getFrequency(local_letters[i]); j++) {
            set(k++, local_letters[i]);
        }
    }
    shuffleVector(letters, nletters, id);
}


int Bag::size() const {
    return nletters;
}

string Bag::to_string() const  {
    
    string s ;
    
    for( int i=0 ; i < nletters ; i++ ) {
        s[i]=get(i) ;
    }
    return s ;
}

void Bag::set(std::string s) {

    nletters = s.size();
    
    for (int i=0;i<s.size(); i++) {
        set(i,s[i]);
    }
}


string Bag::extract(int n) {
    
    string out;
    
    if (n > nletters) {
        n = nletters;
    }
    
    for (int i=0; i<n; i++) {
        out.append(1,get(0));
        removeVector(letters, nletters, 0);
    }
    
    return out;

}

/// Private

char Bag::get(int p) const {

    if( 0 <= p && p < nletters ) {
        return letters[p] ;
    } else {
        return '\000' ;
    }
}

void Bag::set(int p, char c) {
    letters[p] = c;
}


// Auxiliary functions 

void shuffleVector(char* s, int n, int id) {
    
    vector <char> aux(s, s+n);
    
    std::shuffle(aux.begin(), aux.end(), std::default_random_engine(id));

    //Copia el vector
    for (int i=0; i<n; i++)
        s[i] = aux[i];    
}

void removeVector(char* s, int & n, int p){
    
    for( int i=p ; i<n-1 ; i++ ) {
        s[i] = s[i+1] ;
    }
    
    n--;

}
