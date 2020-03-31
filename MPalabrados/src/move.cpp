/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <string>
#include "move.h"

using namespace std;

void Move::setLetters(const string &l){
    letters = normalizeWord(l);
}

void Move::read(std::istream &is) {

  //@warning reading
  //@ set the others fields of move

    letters = normalizeWord(letters);
    
}


Move::Move()const{
    
}

void Move::set(int &r, int &c, char &h, const std::string  &l)const{
    row = r;
    column = c;
    h=='H' ? ishorizontal=true : ishorizontal=false;
    letters = l;
    
}

void Move::setRow(int &r) const{
    row = r;
}

void Move::setCol(int &c) const{
    column = c;
}

void Move::setHorizontal(char &h)const{
    h=='H' ? ishorizontal=true : ishorizontal=false;
}

void Move::setLetters(const std::string &l)const{
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

void Move::setScore(int &s)const{
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

string Move::getLetters() const{
    return letters;
}

void print(const std::ostream &os) const{
    cout << os << endl;
}

void read(const std::istream &is) const{
    getline(is, cin);
}