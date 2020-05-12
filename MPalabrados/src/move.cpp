/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include "language.h"
#include "move.h"

using namespace std;

Move::Move() {
        row = column = score = -1;
        letters="";
        ishorizontal = true;
}

void Move::set(int r, int c, char h, const string & l) {
    setRow(r);
    setCol(c);
    setHorizontal(h);
    setLetters(l);
    //score = -1;
}

void Move::setRow(int r){
    row = r;
}
void Move::setCol(int c){
    column=c;
}
void Move::setHorizontal(char h){
    h = toupper(h);
    ishorizontal = (h == 'H');
}
void Move::setLetters(const string &l){
    letters = normalizeWord(l);
}

void Move::setScore(int s) {
    score = s;
}

int Move::findScore(const Language &l) {
    if (l.query(getLetters()))  {
        score=0;
        for (int let=0; let<getLetters().size(); let++){
            score += l.getScore(getLetters()[let]);
        }
    } else{
        score = -1;
    }
    return score;
}

int Move::getScore() const{
    return score;
}


int Move::getRow() const {
        return row;
}
int Move::getCol() const{
        return column;
}
bool Move::isHorizontal() const{
        return ishorizontal;
}
string Move::getLetters() const{
        return letters;
}

void Move::print( std::ostream &os) const {
    os << (ishorizontal? 'H':'V')<< " "  << row << " " << column 
            << " " << toUTF(letters);    
}

void Move::read( std::istream &is) {
    char h;
    int _row, _column;
    string _letters;
    is >> h >> _row >> _column  >> _letters;
    set(_row,_column, h, _letters);
}

