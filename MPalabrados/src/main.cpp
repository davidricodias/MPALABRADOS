/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"
#include "tiles.h"

using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
#define PASSWORD "MPALABRADOS-V1"
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
 * @param t Final tiles
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, int random, const Bag &b, 
        const Player &p, const Tiles &t,
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected);


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
///*
//
// * 1) El main() recibe múltiples parámetros de entrada, distinguiendo
//entre dos modos de funcionamiento.

    Bag bag; 
    Player player;
    Move move;
    Movelist movements, /// Original list of movements
            legalmovements, /// Movements with legal words upon the dictionary
            acceptedmovements, /// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    
    string word, lang, result, matchfilename, playfilename, savefilename, goodmoves, badmoves; 
    string external_bag;
    int random=-1;
    ifstream matchfile, playfile; ofstream savefile; 
    istream *input; ostream *output;
    int Id, nwords, nletters, score, scoreT, height, width;

    // Clear
    nwords = nletters = score = scoreT = width = height = 0;
    word = result = matchfilename = playfilename = savefilename = "" ;
    goodmoves = badmoves = external_bag = "";
    
    Language language;
    
    /// Check arguments
    
    
    string sarg;
    for(int i=1; i < nargs; ) {
        // cout << i << " " << args[i] << endl; ... Debugging
        sarg = args[i];
        if (sarg=="-p"){                // playfile
            i++ ; 
            if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                playfilename=args[i++];
        } else if (sarg == "-save"){    // save
            i++ ; 
            if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                savefilename=args[i++];
        } else if (sarg == "-l") {      // lang
                i++ ; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                lang=args[i++];
        } else if (sarg == "-r") {      // random
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                Id = atoi(args[i++]);
        } else if (sarg == "-b") {      // bag
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                external_bag = args[i++];
        } else if (sarg == "-w") {      // width
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                width = atoi(args[i++]);
        } else if (sarg == "-h") {      // height
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                height = atoi(args[i++]);
        } else if (sarg == "-open") {   // open match
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                matchfilename = args[i++];
        } else
            errorBreak(ERROR_ARGUMENTS, "");
    }
    
    // Check playing mode
    bool start_new_game = lang != "" && width != 0 && height != 0 && playfilename != "" ;
    bool continue_game = matchfilename != "" && playfilename != "" ;
    
    // Note that, if user enters correct arguments to continue game, but also enters
    // bad arguments to start a new game, it won't cause an error
    if( start_new_game == continue_game )
        errorBreak( ERROR_ARGUMENTS );
    

    //a) Empezar una partida nueva. Para ello los parámetros de
    //llamada serán
    //-l <lang> -w <int> -h <int> -p <pfile> [-r <int> -b <bag> -save <matchfile>]
    //especificando el diccionario, el ancho y alto del tablero de
    //juego, el fichero de movimientos registrados y, opcional-
    //mente, el número aleatorio la bolsa suministrada y la posibilidad de salvar la la
    //jugada en un fichero con extensión .match con la opción
    //-save . En caso de que no se indique esta última opción,
    //entonces deberá mostrar el estado final de la partida con el
    //mismo formato (ver Sección ??).

    // First mode
    if( start_new_game ) {
    
        cout << endl << "Starting new game..." << endl;
    
        

    // b) Continuar una partida existente. Para ello los parámetros
    //de llamada serán
    //-open <matchfile> -p <playfile> [-save <matchfile>]
    //indicando la apertura de un fichero .match desde el que
    //se restaura el estado anterior de la partida, y un fichero
    //de movimientos. Opcionalmente, se podrá grabar la partida
    //final si se indica el parámetro -save comentado antes.        
    // Second mode    
    } else {
        // Open matchfile
        matchfile.open( matchfilename ) ;
        
        cout << endl << "Trying to open game file" << endl;
        if( matchfile ) {
            
            cout << endl << "Checking match file" ;       
        
            //Check passwonrd
            matchfile >> word ;
            if( word != PASSWORD )
                errorBreak(ERROR_OPEN, matchfilename) ;
            cout << endl << "Match file has password!" << endl;
            
            // Save language
            matchfile >> lang ;
            
            // Save height and width
            matchfile >> height >> width ;
            
        } else {
            errorBreak(ERROR_OPEN, matchfilename) ;
        }
    }
    

// * 2. Crear una instancia de la clase Language con el ID indicado.

    language.setLanguage(lang);
    
// 3. Crear una instancia de la clase Bag, si es una partida nueva,
//  inicializar la bolsa, en otro caso, cargarla directamente desde el
//fichero .match



    if( matchfilename != "" )
        bag.set(normalizeWord(external_bag)) ;
    else
        bag.define(language) ;
    
// * 4. Crear una instancia de la clase Player y inicializarla por com-
//pleto con caracteres de la bolsa o bien leerla del fichero .match.
//
// * 5. Crear una instancia de la clase Tiles y dimensionarla según
//los parámetros leı́dos, bien desde la lı́nea de comandos, bien
//desde el fichero .match.
//
// * 6. Crear una instancia de la clase bf Movelist llamada original
//y leer todos los movimientos desde el fichero indicado en el
//parámetro -p usando operador sobrecargado >>
//
// * 7. Crear una instancia de Movelist llamada legal que contenga
//sólo los movimientos de original que están en el diccionario
//del lenguaje elegido. Usar, para ello, el método zip(...)
//
// * 8. Crear dos instancias adicionales de Movelist y llamarlas accepted
//y rejected
//
// * 9. Recorrer toda la lista de movimientos leı́da y, por cada uno de
//ellos.
//
//     * a) Si el movimiento está en el diccionario, añadir la palabra a
//la lista accepted , calcular su puntuación, según el idioma
//y acumularla. A continuación, se deberá colocar cada mo-
//vimiento en su posición correspondiente en la instancia de
//Tiles creada anteriormente, ignorando aquellos caracteres
//que caigan fuera de las dimensiones permitidas y sobrees-
//cribiendo los caracteres que se crucen.
//
//     * b) En otro caso añadirla a la lista rejected .
//
// * 10. Terminar mostrando el estado de la partida en pantalla o guardándo-
//lo en disco según la presencia o no de -save .
//11. Si en cualquier momento se presenta un error en los argumen-
//tos, en la apertura de ficheros o en la lectura de datos del fiche-
//ro, se debe usar la función errorBreak(...) para notificar el error
//y parar el programa 
// */
    
    
    
    
    if (input->eof()) 
            errorBreak(ERROR_DATA, matchfilename);
    // Close files
    if (playfilename != "")
        playfile.close();
    if (savefilename != "")
        savefile.close();
    
    return 0;
}


void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use either:"<<endl;
            cerr<< "-l <language> -w <width> -h <height> -p <playfile> [-b <bag> -r <randomnumber> -save <matchfile>]"<<endl;
            cerr<< "-open <matchfile> -p <playfile> [-save <matchfile>]"<<endl;            
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

/**@warning HallOfFame() */







//////////// OLD CODE //////////////////
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
//void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
//        const Movelist& original,const Movelist& legal,
//        const Movelist& accepted,const Movelist& rejected);

//
///**
// * @brief Main function. 
// * @return 
// */
//int main(int nargs, char *args[]) {
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////    // | OLD CODE BELOW |    
////    // Process arguments
////    
////    if (playfilename=="")
////        errorBreak(ERROR_ARGUMENTS, "");
////    
////    
////    if (lang=="") {
////        errorBreak(ERROR_ARGUMENTS, "");
////    }
////    else {
////        
////    }
////    cout << "LANGUAGE: "<<lang << endl;
////    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
////    cout << "SEED: "<<Id<<endl;
////   
////    if (Id >=0)
////        bag.setRandom(Id);
//
////    cout << "BAG !! ("<<bag.size()<<") : "<<toUTF(bag.to_string())<< endl;
////    //return 0;
////    ifile.open(ifilename);
////    if (!ifile) {
////        errorBreak(ERROR_OPEN, ifilename);
////    }
////    input = &ifile;
////    cout << "Reading from "<<ifilename << endl;
////    
////    if (!movements.read(*input)) {     // read full list of movements;
////        errorBreak(ERROR_DATA,ifilename);
////    }    
////    if (ofilename=="") {
////        output = &cout;
////    } else {
////        ofile.open(ofilename);
////        if (!ofile) {
////            errorBreak(ERROR_OPEN, ofilename);
////        }
////        output = &ofile;
////        cout << "Writing to "<<ofilename << endl;
////    }
////  
////    //cout << "BAG (" << Id << "-" << bag.size() << ") :" << toUTF(bag.to_string()) << endl;   
////    
////    //legalmovements = movements;
////    legalmovements.assign(movements);
////    
////    legalmovements.zip(language);
////    player.add(bag.extract(7-player.size()));
////    
////    for (int i=0; i<legalmovements.size(); i++)  {
////        cout << "PLAYER: "<<toUTF(player.to_string())<<endl;
////        move=legalmovements.get(i);
////        (*output) << "MOVEMENT: "; 
////        move.print(*output);
////        word = move.getLetters();
////
////        if (player.isValid(word)) {
////            if (language.query(word)) {
////                nwords++;
////                score = move.findScore(language);
////                move.setScore(score);
////                scoreT += score;
////                nletters += word.length();
////                goodmoves += word + " - ";
////                cout << " FOUND! " << move.getScore() << " points";
////                acceptedmovements.add(move);
////            } else {
////                cout << " NOT REGISTERED!";
////                rejectedmovements.add(move);
////            }
////            cout << endl << endl;
////            player.extract(word);
////            player.add(bag.extract(7 - player.size()));
////
////        } else {
////            cout << " INVALID!" << endl;
////            rejectedmovements.add(move);
////        }
////    }
////        

////    HallOfFame(language, Id, bag, player, 
////            movements, legalmovements, acceptedmovements, rejectedmovements);
//
//    return 0;
//}
//
//void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
//        const Movelist& original,const Movelist& legal,
//        const Movelist& accepted,const Movelist& rejected) {
//    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
//    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
//    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string());
//    cout << endl << endl << "ORIGINAL ("<<original.size()<<"): "<<endl; original.print(cout);
//    cout << endl << endl << "LEGAL ("<<legal.size()<<"): "<<endl; legal.print(cout);
//    cout << endl << endl << "ACCEPTED ("<<accepted.size()<<") SCORE "<<accepted.getScore()<< ": "<<endl; accepted.print(cout);
//    cout << endl << endl << "REJECTED ("<<rejected.size()<<"): "<<endl; rejected.print(cout);
//    cout << endl;
//}
//
//void errorBreak(int errorcode, const string &errorinfo) {
//    cerr << endl << "%%%OUTPUT" << endl;
//    switch(errorcode) {
//        case ERROR_ARGUMENTS:
//            cerr<<"Error in call. Please use:\n -l <language> -p <playfile> [-r <randomnumber>]"<<endl;
//            break;
//        case ERROR_OPEN:
//            cerr<<"Error opening file "<<errorinfo << endl;
//            break;
//        case ERROR_DATA:
//            cerr<<"Data error in file "<<errorinfo << endl;
//            break;
//    }
//    std::exit(1);
//}
//
