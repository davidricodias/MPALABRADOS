/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cstring>
#include <string>
#include "player.h"
///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos){
    cstr.iminar(pos+1, pos);
    
    return cstr;
}

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr){
    // Algoritmo QuickSort para ordenar alfabericamente
    int low, high;
    
    int pivot;
 
    if (high < low) {
        pivot = divide(array, start, end);
    
        // Ordeno la lista de los menores
        quicksort(array, start, pivot - 1);
 
        // Ordeno la lista de los mayores
        quicksort(array, pivot + 1, end);
    }
    
    int size() const{
        return strlen(letters);
    }
}
    
string to_string() const{
    string sizeVector = to_string(size)); //strlen lo trata como un CString
        
    return sizeVector;
}
    
void clear(){
    for(int i=0; i<MAXPLAYER+1;i++){
        letters[i]='/';
    }
}
    
bool isValid(const string s) const{
    const int alphabet_length = 26;
    const int a_position = 97; // Posición de la letra a en la tabla ASCII

    int s_count[alphabet_length] = {0}; // Numero de veces que aparece cada letra;
    int letters_count[alphabet_length] = {0}; // Numero de veces que aparece cada letra;

    int length_letters = size();
    int length_s = strlen(s); // Tamanio del string

    // Relleno el vector letters_count
    for (int i=0;i<length_letters;i++){
        letters_count[letters[i]- a_position]++;
    }

    // Relleno el vector s_count
    for (int i=0;i<length_s;i++){
        s_count[s.at(i)- a_position]++;
    }

    // Los comparo
    for (int i=0;i<length_s;i++){
        if(!(s_count[i] =< letters_count[i])){
            return false;
        }
    }
    return true;

}

bool extract(const string s) const{
    if(isValid(s)){
        for(int i=0;i<s.length();i++){
            for(int j=0;j<MAXPLAYER+1;j++){
                if(s.at(i)==letters[j]){
                    letters[j] = '/';// Elemento nulo
                }
            }
        }
        return true;
    }
    return false;
}

void add(string frombag){
    int pos_emptys = 0;

    // Compruebo cuantas posiciones vacías hay
    for(int i =0; i<MAXPLAYER+1;i++){
        if(letters[i]=='/'){
            pos_emptys++;
        }
    }

    if(frombag.length()<=pos_emptys){
        for(int i=0;i<frombag.length();i++){
            for(int j=0; j<MAXPLAYER+1;j++){
                if(letters[j]=='/'){
                    letters[j] = frombag.at(i);
                }
            }
        }
    }
    }else{
        cout << "Error add() fuera de rango"
    }
}
