/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

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
            if(aux[j] == comp)
                encontrado_comp = true ;
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
                    //removeCString
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

    if(frombag.length()<=pos_emptys){
        strcat(letters, &frombag[0]);
    }
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
    char aux= cstr[0];
   
    int first, temp;
    int numLength = strlen(cstr);
    for (int i= numLength - 1; i > 0; i--){
        first = 0; 
        for (int j=1; j<=i; j++){
            if (cstr[j] < cstr[first]){
                first = j;
            }
        }
        temp = cstr[first]; 
        cstr[first] = cstr[i];
        cstr[i] = temp;
     }
    
    // Colocación de la ñ
    // Busco la letra anterior a la ñ y mas proxima a ella
    int prox_position; // Posición del más próximo
    char prox= cstr[0]; // Letra más proxima
    
    //¿Cuantas ñ's hay?
    int count=0;
    int n_enies=0; // Numero de eñes
    for(int i=0;cstr[i]!='ñ';i++){
        count++;
    }
    n_enies=TAM-count;
    
    if(cstr[0]>'n'){ // Compruebo si la primera letra es posterior a la ñ
        // Colocar en primer lugar
    }else{
        for(int i=1; prox<'n' | i<count;i++){
            if(cstr[i]>=prox){
                prox=cstr[i];
                prox_position = i;
            }
        }
        
        // Ordenamos
        for(int i=TAM;i>prox_position+1;i--){
            cstr[i+n_enies]=cstr[i];
        }
        
        // Rellenamos de eñes
        for(int i=prox_position;i<n_enies;i++){
            cstr[prox_position+1] = 'ñ';
        }
    }
    
                
}
