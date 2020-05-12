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
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected);


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char *args[]) {

    Bag bag; 
    Player player;
    Move move;
    Movelist movements, /// Original list of movements
            legalmovements, /// Movements with legal words upon the dictionary
            acceptedmovements, /// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    
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
        if (sarg=="-p"){
            i++; 
            if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ifilename=args[i++];
        } else if (sarg=="-i"){
            i++; 
            if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ifilename=args[i++];
        } else if (sarg=="-o"){
            i++; 
            if (i>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ofilename=args[i++];
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
    
    // Process arguments
    if (ifilename=="")
        errorBreak(ERROR_ARGUMENTS, "");
    if (lang=="") {
        errorBreak(ERROR_ARGUMENTS, "");
    }
    else {
        language.setLanguage(lang);
    }
    cout << "LANGUAGE: "<<lang << endl;
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    cout << "SEED: "<<Id<<endl;
   
    if (Id >=0)
        bag.setRandom(Id);
    if (external_bag != "")   // -b
        bag.set(normalizeWord(external_bag));
    else
        bag.define(language);
    cout << "BAG !! ("<<bag.size()<<") : "<<toUTF(bag.to_string())<< endl;
    //return 0;
    ifile.open(ifilename);
    if (!ifile) {
        errorBreak(ERROR_OPEN, ifilename);
    }
    input = &ifile;
    cout << "Reading from "<<ifilename << endl;
    
    if (!movements.read(*input)) {     // read full list of movements;
        errorBreak(ERROR_DATA,ifilename);
    }    
    if (ofilename=="") {
        output = &cout;
    } else {
        ofile.open(ofilename);
        if (!ofile) {
            errorBreak(ERROR_OPEN, ofilename);
        }
        output = &ofile;
        cout << "Writing to "<<ofilename << endl;
    }
  
    //cout << "BAG (" << Id << "-" << bag.size() << ") :" << toUTF(bag.to_string()) << endl;   
    
    //legalmovements = movements;
    legalmovements.assign(movements);
    
    legalmovements.zip(language);
    player.add(bag.extract(7-player.size()));
    
    for (int i=0; i<legalmovements.size(); i++)  {
        cout << "PLAYER: "<<toUTF(player.to_string())<<endl;
        move=legalmovements.get(i);
        (*output) << "MOVEMENT: "; 
        move.print(*output);
        word = move.getLetters();

        if (player.isValid(word)) {
            if (language.query(word)) {
                nwords++;
                score = move.findScore(language);
                move.setScore(score);
                scoreT += score;
                nletters += word.length();
                goodmoves += word + " - ";
                cout << " FOUND! " << move.getScore() << " points";
                acceptedmovements.add(move);
            } else {
                cout << " NOT REGISTERED!";
                rejectedmovements.add(move);
            }
            cout << endl << endl;
            player.extract(word);
            player.add(bag.extract(7 - player.size()));

        } else {
            cout << " INVALID!" << endl;
            rejectedmovements.add(move);
        }
    }
        
    if (input->eof()) {  // salida por falta de datos
            errorBreak(ERROR_DATA, ifilename);
    }
    if (ifilename!="")
        ifile.close();
    if (ofilename!="")
        ofile.close();
    HallOfFame(language, Id, bag, player, 
            movements, legalmovements, acceptedmovements, rejectedmovements);
  
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
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
            cerr<<"Error in call. Please use:\n -l <language> -p <playfile> [-r <randomnumber>]"<<endl;
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

