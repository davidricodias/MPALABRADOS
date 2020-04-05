/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <string>
#include <iostream>
#include "move.h"


Move::Move(){
    
}

void Move::set(int &r, int &c, char &h, const std::string  &l){
    row = r;
    column = c;
    h=='H' ? ishorizontal=true : ishorizontal=false;
    letters = l;
}

void Move::setRow(int &r) {
    row = r;
}

void Move::setCol(int &c) {
    column = c;
}

void Move::setHorizontal(char &h){
    h=='H' ? ishorizontal=true : ishorizontal=false;
}

void Move::setLetters(const std::string &l){
    letters = l;
}

int Move::findScore(const Language &l)const{
    // Recorre el string y le pasa cada letra que contiene a 
    // language.getScore que irá sumando en "sum" el valor retornado
    
    int sum=0;
    int length_str = letters.length();
    for(int i = 0;i<length_str;i++){
        sum +=l.getScore(letters[i]);
    }
    
    return sum;

}

void Move::setScore(int &s){
    score = s;
}

int Move::getScore() const{
    return score;
}

int Move::getRow() const{
    return row;
}

int Move::getCol() const{
    return column;
}

bool Move::isHorizontal() const{
    return ishorizontal;
}

std::string Move::getLetters() const{
    return letters;
}

void Move::print( std::ostream &os) const{
    os << letters << " ";
}

void Move::read( std::istream &is) {
    is >> letters ;
}