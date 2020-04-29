/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */


#include <iostream>
#include <string>
#include <fstream>

#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"

using namespace std;

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo="");

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, const string id, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected);


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char **args) {
    
    const string arg_ID = "-l";
    const string arg_playerfile = "-p";
    const string arg_random= "-r";
    const string arg_bag= "-b";

    Bag bag;
    Player player;
    Language language;
    Move move;
    Movelist movements,        /// Original list of movements
            legalmovements,    /// Movements with legal words upon the dictionary
            acceptedmovements, /// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    /// ...
    ///@warning: Complete the code
    /// ...
    
    
    //1.
    string id, external_data, external_bag;
    int random=0;
    id = external_data = external_bag = "";
    
    for(int i=1; i<nargs; i++){
        string arg = args[i] ;
        
        if( arg == arg_ID){
            if((i)>=nargs){errorBreak(ERROR_ARGUMENTS,"");}
            id = args[i+1];
            
        }else if( arg==arg_playerfile ) {
            if((i)>=nargs){errorBreak(ERROR_ARGUMENTS,"");}
            external_data = args[i+1];
            
        } else if( arg==arg_random) {
            if((i)>=nargs){errorBreak(ERROR_ARGUMENTS,"");}
           random = stoi(args[i+1]);

        } else if( arg==arg_bag) {
            if((i)>=nargs){errorBreak(ERROR_ARGUMENTS,"");}
           external_bag = args[i+1];
           bag.set(external_bag);
        }
     }
    
    
    if( id=="" || external_data==""){
        errorBreak(ERROR_ARGUMENTS, "Lectura de parametros inválida");
    }

    //2.
    language.setLanguage(id);
    cout << "Caracteres permitidos:" << endl;
    cout << toUTF(language.getLetterSet()) << endl;
    
    
    //3.
    if(external_bag != ""){
        bag.set(normalizeWord(external_bag));
    }else if(random>-1){
        bag.define(id);
        bag.setRandom(random);
    } else{
        errorBreak(ERROR_ARGUMENTS, "Lectura de parametros inválida");
    }
    
    
    //4.
    player.add(bag.extract(7 - player.size()));
    
    //5.
    ifstream ifile;
    if(external_data!=""){
        ifile.open(external_data);   
        if(ifile){
            movements.read(ifile);
            cout << external_data << " leido." << endl;
        }else{
            errorBreak(ERROR_OPEN, external_data);
        }
    }

    //6.
    cout << endl << endl << " TRAZA OK " << endl << endl ;    
    
    
    legalmovements.assign(movements);
    legalmovements.zip(language.getLanguage());
    cout << "legales"<<legalmovements.size() << endl;
    //8.
    int l_moves = legalmovements.size();
    for(int i=0; i<l_moves; i++){
        if(language.query(legalmovements.get(i).getLetters())){
            // Añadir a la lista
            acceptedmovements.add(legalmovements.get(i));
            // Marcarla
            // ¿?
            // Calcular puntuación
            // Mostrar en pantalla
            cout << "Score: " << acceptedmovements.getScore() << endl; // ¿Puntuación total o del movimiento?
        }else{
            rejectedmovements.add(legalmovements.get(i));
        }
    }
    

    HallOfFame(language, id, bag, player, 
            movements, legalmovements, acceptedmovements, rejectedmovements);
    
    return 0;
}

void HallOfFame(const Language &l, const string id, const Bag &b, const Player &p, 
        const Movelist &original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << id << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string());
    cout << endl << endl << "ORIGINAL ("<<original.size()<<"): "<<endl; original.print(cout);
    cout << endl << endl << "LEGAL ("<<legal.size()<<"): "<<endl; legal.print(cout);
    cout << endl << endl << "ACCEPTED ("<<accepted.size()<<") SCORE "<<accepted.getScore()<< ": "<<endl; accepted.print(cout);
    cout << endl << endl << "REJECTED ("<<rejected.size()<<"): "<<endl; rejected.print(cout);
    cout << endl;
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language> -p <playfile> [-r <randomnumber>] -b <bag>"<<endl;
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
}
