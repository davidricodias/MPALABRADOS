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
#include <cmath>
#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"
#include "tiles.h"
//#include "AnsiTerminal.h"

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
void errorBreak(int errorcode, const string & errorinfo);

/**
 * @brief Shows final data
 * @param l
 * @param b
 * @param p
 * @param tiles
 * @param score
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 * @param os
 * @param release
 */
void HallOfFame(const Language &l, const Bag &b, const Player &p, const Tiles & tiles, int score, const Movelist& original, const Movelist& legal, const Movelist& accepted, const Movelist& rejected, ostream * os, bool release);

void showOutput(const Language &l, int score, const Bag &b, const Player &p, const Tiles & tiles, ostream *os);


void loadMatch(const string & ifilematch, int &score, Language &language, int &h, int &w, Tiles & tiles, Player &player, Bag &bag){
    ifstream ifile;
    string word, lang;
    int n;
    
    ifile.open(ifilematch);
        if (!ifile)
            errorBreak(ERROR_OPEN,ifilematch);
        ifile >> word;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        if (word != PASSWORD)
            errorBreak(ERROR_DATA,ifilematch);
        ifile >> score;
        ifile >> lang;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        language.setLanguage(lang);
        tiles.read(ifile);
        h = tiles.getHeight();
        w = tiles.getWidth();
        
        ifile >> n;
        if (n>0) {
            ifile >> word;
            player.add(toISO(word));
        }
        ifile >> n;
        if (n>0) {
            ifile >> word;
            bag.set(toISO(word));
        }
        ifile.close();
 //               tiles.print(cout);
                
    }


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char *args[]) {

    Bag bag; 
    Player player;
    Move move;
    Movelist originalmovements, /// Original list of movements
            legalmovements, /// Movements with legal words upon the dictionary
            acceptedmovements, /// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    Tiles tiles;
    int width = -1, height = -1;
    
    
    string word, lang, result, fileplay, ifilematch, ofilematch, goodmoves, badmoves; 
    string external_bag;
    ifstream ifile;
    ofstream ofile;
    istream *input;
    ostream *output;
    int Id, nwords, nletters, score, scoreT;
    

    nwords = nletters = score = scoreT = 0;
    word = result = fileplay =ifilematch = ofilematch = "";
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
    for(int arg=1; arg<nargs; ) {
        sarg = args[arg];
        if (sarg=="-open"){
            arg++; 
            if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ifilematch=args[arg++];
        }else if (sarg=="-save"){
            arg++; 
            if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ofilematch=args[arg++];
        }else if (sarg== "-l") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                lang=args[arg++];
        } else if (sarg== "-r") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                Id = atoi(args[arg++]);
        } else if (sarg== "-b") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                external_bag = args[arg++];
        }else if (sarg== "-w") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                width = atoi(args[arg++]);
        } else if (sarg== "-h") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                height = atoi(args[arg++]);
        }  else
            errorBreak(ERROR_ARGUMENTS, "");
    }
  
     // Process arguments
    if  ((fileplay=="") || (lang=="" && ifilematch=="") ||( ifilematch=="" &&  (width <0 ||  height <0)))
        errorBreak(ERROR_ARGUMENTS, "");
 
    // load parameters
    if (ifilematch == "") { // game from scratch 
        language.setLanguage(lang);
        if (Id >= 0)
            bag.setRandom(Id);
        if (external_bag != "")
            bag.set(toISO(external_bag)); //codification 1byte for each
        else
            bag.define(language);
        cout << "!!!!!!!!!!!!!!BAG " << toUTF(bag.to_string()) << endl; // codification to see Ñ as nice character
        tiles.setSize(height,width);
      
    }
    else  // game from previous match
       loadMatch(ifilematch,score,language, height, width, tiles, player, bag);

    // once the main objects are inicialized
    
    cout << "LANGUAGE: "<<language.getLanguage() << endl;
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    cout << "PLAYER: " << toUTF(player.to_string()) << endl;
    cout << "BAG: " << toUTF(bag.to_string())<< endl;
    //cout << "SEED: "<<Id<<endl;
    
    ifile.open(fileplay);
    if (!ifile)
        errorBreak(ERROR_OPEN, fileplay);

    //movements.read(ifile); //ifile >> movements;
    ifile >> originalmovements;
  
    cout << originalmovements ; //movements.print(cout);

    if ((!ifile) || ifile.eof())
        errorBreak(ERROR_DATA, fileplay);
    ifile.close();

    legalmovements = originalmovements;
    legalmovements.zip(language);
    player.add(bag.extract(7-player.size()));  // fill player when necessary
    bool fin = false;
    for (int i = 0; i < legalmovements.size() && !fin; i++) {
        move = legalmovements.get(i);
        HallOfFame(language, bag, player, tiles, score, originalmovements, legalmovements, acceptedmovements, rejectedmovements, &cout, false);
        word = move.getLetters();
        if (player.isValid(word) && language.query(word)) {
            player.extract(word);
            player.add(bag.extract(7 - player.size()));
            move.setScore(move.findScore(language));
            acceptedmovements.add(move);
            tiles.add(move);
        } else
            rejectedmovements.add(move);

    }
    ostream *os = &cout;
    if (ofilematch!="")  {
        ofile.open(ofilematch);    
        if (!ofile)
            errorBreak(ERROR_OPEN,ofilematch);
        os = &ofile;
    }
    HallOfFame(language, bag, player, tiles, score, originalmovements, legalmovements, acceptedmovements, rejectedmovements, os,true);
    
    if (ifile.eof()) {  // salida por falta de datos
            errorBreak(ERROR_DATA, fileplay);
    }
    if (fileplay!="")
        ifile.close();
    if (ofilematch!="")
        ofile.close();

  
    return 0;
}
void showOutput(const Language &l, int score, const Bag &b, const Player &p, const Tiles & tiles, ostream * os){
   
        (*os) << score  << endl;
        (*os) << l.getLanguage() << endl;
        //    (*os) << tiles.getHeight()<<" "<<tiles.getWidth()<<endl;
        tiles.print((*os));
        (*os) << p.size() << " " << toUTF(p.to_string()) << endl;
        (*os) << b.size() << " " << toUTF(b.to_string()) << endl;
}

void HallOfFame(const Language &l, const Bag &b, const Player &p, const Tiles & tiles, int score, const Movelist& original, const Movelist& legal, const Movelist& accepted, const Movelist& rejected, ostream *os, bool release = false) {
    char ch;
    //cout<< "tecla  " ;cin >> ch;
    if (!release) { // debug mode
        (*os) << endl << "%%%SALIDA" << endl;
        (*os) << score + accepted.getScore() << endl;
        (*os) << "LANGUAGE: " << l.getLanguage() << endl;
        (*os) << "BAG (" << b.size() << "): " << toUTF(b.to_string()) << endl;
        (*os) << "PLAYER (" << p.size() << "): " << toUTF(p.to_string()) << endl;
        tiles.print(((*os)));
        (*os) << "TILES: " << endl;
        (*os) << endl << endl << "ORIGINAL (" << original.size() << "): " << endl;
        (*os) << original.print(cout);
        (*os) << endl << endl << "LEGAL (" << legal.size() << "): " << endl;
        (*os) << legal; //legal.print(cout);
        (*os) << endl << endl << "ACCEPTED (" << accepted.size() << ") SCORE " << accepted.getScore() << ": " << endl;
        (*os) << accepted; // accepted.print(cout);
        (*os) << endl << endl << "REJECTED (" << rejected.size() << "): " << endl;
        (*os) << rejected; //rejected.print(cout);
        (*os) << endl;
    } else { // release mode, the last print by screen & opcionally by file
        int scoreT = score + accepted.getScore();
        if (os != &cout){
            (*os) << PASSWORD << endl;
            showOutput(l, scoreT, b, p, tiles, os);
        }
        else {
            cout << endl << "%%%OUTPUT" << endl;
            showOutput(l, scoreT, b, p, tiles, os);
        }
    }
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

