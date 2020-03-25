/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include "language.h"
#include "bag.h"
#include "player.h"
///@warning complete missing #includes


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

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    
    //No se modifican las declaraciones
    int id;             /// To be used in bag.setRandom())
    Bag bag;            /// Bag of letters
    Player player;      /// Player set of letters
    Language language;  /// Language to be loaded from disk
    string result;      /// String that contains all the words found
    int nletters = 0 ;  /// Number of letters found
    int nwords = 0 ;    /// Number of words found
    
    //Lectura según UTF-8
    string lang ;
    cout << endl << "TYPE LANGUAGE: ";
    cin >> lang ;
    //Mejora de condiciones: búsqueda de idiomas disponibles.
    while( lang.length() == 0 || lang != "ES" || lang != "EN" ) {
        cout << endl << "Entrada inválida" ;
        cout << endl << "TYPE LANGUAGE: " << endl;
        cin >> lang ;
    }

    //Inicializa Language esgún ISO
    language.setLanguage( toISO(lang) ) ;
    
    //Muestra el conjunto de caracteres permitidos
    cout << "ALLOWED LETTERS: "
         << toUTF( language.getLetterSet() ) ;
    
    //Pide número entero. Un simple try, por si acaso
    bool is_ovflw ;
    do {
        try {
            is_ovflw = false ;
            cout << endl << "TYPE SEED (<0 RANDOM): " ;
            cin >> id ;
        } catch ( overflow_error ) {
            is_ovflw = true ;
        }
    } while( is_ovflw ) ;
    
    //Inicializa la semilla si se cumple la cond.
    if( id >= 0 ) {
        bag.setRandom( id ) ;
    }
    
    //Define el lenguaje de la bolsa
    bag.define( language );
    
    //Muestra bag. En la práctica no lo pide, pero en la ejecución de prueba sí
    //se muestra.
    cout << "BAG(" << id << "-" << bag.size() << "): "
         << toUTF( bag.to_string() ) ;
    
    string word ;
    
    do {
        //Llena la bolsa de Player
        player.add( bag.extract(MAXPLAYER) ) ;
    
        //Muestra la bolsa del Player
        cout << endl << "PLAYER: " << player.to_string() << " BAG("
             << bag.size() << ")" ;
        cout << endl << "INPUT A WORD: " ;
        cin >> word ;

        //Si es una palabra contenida en la bolsa del Player
        if( player.isValid( toISO(word) ) ) {
            
            //Si la palabra está en el diccionario
            if( language.query( toISO(word) ) ) {
                cout << endl << endl << word << " FOUND!" << endl ;
                nwords++ ;                  //Añade las palabras
                nletters += word.length() ; //Añade las letras
            } else {
                cout << endl << endl << word << " NOT REGISTERED!" << endl ;
            }
        } else {
            cout << endl << endl << word << " INVALID!" << endl ;
        }
        
    } while( word.length() < 2 ) ;
    
            
    HallOfFame(language,id,bag,player, nwords, nletters, result);
    
    
    return 0;
}

string bestAdvice(const string & s, const Language &l)  {
    
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " letters "<<endl << 
            toUTF(result) << endl;    
}


