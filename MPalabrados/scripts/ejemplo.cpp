/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <iostream>
#include <fstream>
#include <string>

#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"

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
void errorBreak(int errorcode, const string & errorinfo);

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
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char *args[]) {
    
    Bag bag;
    string word, lang, result, ifilename, ofilename, goodmoves, badmoves; 
    string external_bag;
    int random=-1;
    ifstream ifile; ofstream ofile; 
    istream *input; ostream *output;
    int Id, nwords, nletters, score, scoreT;
    
    nwords = nletters = score = scoreT = 0;
    word = result = ifilename = ofilename = "";
    goodmoves = badmoves = external_bag = "";
    
    /*
	1. El main() recibe como parámetro obligatorio "-l <ID>" y co-
	mo parámetros opcionales "-i <file>" y "-r <random>" ,
	en cualquier orden entre los tres. Si se especifica "-i" se leen
	los datos desde ese fichero, si no, se leen desde el teclado. Si
	se especifica "-r" se define el aleatorio con el número indica-
	do, si no, no se define aleatorio.
    */
    
    bool end=false;
    Language language;
    /// Check arguments
        
    string sarg;
    for(int i=1; i<nargs; ) {
        cout << i << " " << args[i] << endl;
        sarg = args[i];
        if (sarg=="-i"){
            i++; 
            if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ifilename=args[i++];
        }else if (sarg== "-l") {
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                lang=args[i++];
        } else if (sarg== "-r") {
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                Id = atoi(args[i++]);
        }
        else if (sarg== "-b") {
                i++; 
                if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                external_bag = args[i++];
        } else
            errorBreak(ERROR_ARGUMENTS, "");
    }
    
    input = &cin;
    output = &cout;
    
    // Process arguments
    if (lang=="") {
        errorBreak(ERROR_ARGUMENTS, "");
    }
    else {
        language.setLanguage(lang);
    }
    
    /* 2. Crear una instancia de la clase Language con el anterior ID y
	mostrar el conjunto de caracteres permitido para ese lenguaje.
    */
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    
    if (ifilename!="") {
        ifile.open(ifilename);
        if (!ifile) {
            errorBreak(ERROR_OPEN, ifilename);
        }
        input = &ifile;
        cout << "Reading from "<<ifilename << endl;
    }
    
    
    cout << "SEED: "<<Id<<endl;
    
    /*  3. Crear una instancia de la clase Bag, inicializar el generador de
	números aleatorios con el número aleatorio anterior, si es que
	se ha indicado, y definir su contenido en base al lenguaje que
	se ha declarado anteriormente. 
    */
    if (Id >=0)
        bag.setRandom(Id);
    if (external_bag != "")
        bag.set(normalizeWord(external_bag));
    else
        bag.define(language);
   
    cout << "BAG (" << Id << "-" << bag.size() << ") :" << toUTF(bag.to_string()) << endl;

    Player player;

    player.add(bag.extract(7 - player.size()));
    cout << endl << "PLAYER: " << toUTF(player.to_string())  << " BAG(" << bag.size() << ")" << endl;
    cout << "INPUT H|V <nrow> <ncol> <word>: ";
    /*  4. Crear una instancia de la clase Player y llenarla por comple-
        to con caracteres de la bolsa. Este objeto player deberá estar
        siempre ordenado de la A a la Z.
     */
    Move move;
    move.read(*input);      /* lectura adelantada */
    word = move.getLetters();
    cout << endl << "READ: ";
    move.print(*output);           

    while ((word.length() > 1) && (!input->eof())) {

        /* 5. Repetir la siguiente secuencia hasta que se lea un movimiento
        con la palabra "@"  */

        cout << endl << toUTF(word);
        if (player.isValid(word)) {
            if (language.query(word)) {
                nwords++;
                score = move.findScore(language);
                move.setScore(score);
                scoreT += score;
                nletters += word.length();
                goodmoves += word + " - ";
                cout << " FOUND! " << move.getScore() << " points";
            } else {
                cout << " NOT REGISTERED!";
            }
            cout << endl << endl;
            player.extract(word);
            player.add(bag.extract(7 - player.size()));

        } else
            cout << " INVALID!" << endl;
        
        cout << endl << "PLAYER: " << toUTF(player.to_string()) << " BAG(" << bag.size() << ")" << endl;
        cout << "INPUT H|V <nrow> <ncol> <word>: ";
        move.read(*input); //     /* actualizacion de move */
        word = move.getLetters();
        cout << endl << "READ: " << word;
        move.print(*output);
    } 
    if (input->eof()) {  // salida por falta de datos
            errorBreak(ERROR_DATA, ifilename);
    }
      
        
    /*6. Terminar con la llamada a HallOfFame para visualizar los re-
	sultados. */
    HallOfFame(language, Id, bag, player, nwords, scoreT, goodmoves);
    
    /*
	7. Si en cualquier momento se presenta un error en los argumen-
	tos, en la apertura de ficheros o en la lectura de datos del fiche-
	ro, se debe usar la función errorBreak(...) para notificar el error
	y parar el programa.
	*/
  
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " points "<<endl << 
            toUTF(result) << endl;    
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language>  [-r <randomnumber> -i <inputfile>]"<<endl;
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
