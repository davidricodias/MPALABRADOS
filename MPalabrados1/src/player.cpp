/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <algorithm>
#include <string>
#include <cstring>
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
void removeCString(char *cstr, int pos);
/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr);

/**
* @brief Basic constructor and initializer. 
*/
Player::Player(){}

/**
* @brief Returns the number of letters stored.
* @return The number of letters
*/
int Player::size() const{
    return strlen(letters);
}


/**
* @brief Returns the number of letters stored. Although internally this set is stored in a CSTRING, the return value must be a STRING 
* @return The set of letters
*/
string Player::to_string() const{
    string letters_str = letters ;
    return letters_str ;
}

void Player::clear(){
    letters[0]='\0';
}

bool Player::isValid(const string s) const{
    
    bool is_valid = true ;
    
    char aux[MAXPLAYER+1] ;
    
    strcpy(aux,letters) ;
    
    char comp ;
    
    for( int i=0  ; i < s.length() && is_valid ; i++ ) {
        comp = s[i] ;
        
        bool encontrado_comp = false ;
        for( int j=0 ; aux[j] != '\0' && is_valid && !encontrado_comp; j++ ) {
            if(aux[j] == comp) {
                encontrado_comp = true ;
                removeCString(aux, j) ;
            }
        }
        if( !encontrado_comp )
            is_valid = false ;
    }

    return is_valid ;
    
}

bool Player::extract(const string s){
    if(isValid(s)){
        for(int i=0;i<s.length();i++) {
            for(int j=0;letters[j]!='\0';j++){
                if(s.at(i)==letters[j]){
                    removeCString(letters, j);
                }
            }
        }
        return true;
    }
    return false;
}



void Player::add(string frombag){
    int pos_emptys = 0;

    // Compruebo cuantas posiciones vacías hay
    pos_emptys = MAXPLAYER - strlen(letters);

    strcat(letters, &frombag[0]);
    
}

// Private
/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos){
    // Copiamos el contenido de pos+1 en pos donde pos es la posicion
    // que vamos a remplazar
    
    int TAM = strlen(cstr); // Tamanio
    
    for(int i=pos; i<TAM; i++){
        cstr[i]=cstr[i+1];
    }
    
}

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr){
    int TAM = strlen(cstr);
    sort(cstr[0], cstr[TAM]);
                
}

