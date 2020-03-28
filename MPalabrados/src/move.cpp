/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <string>

using namespace std;

void Move::setLetters(const string &l){
    letters = normalizeWord(l);
}

void Move::read(std::istream &is) {

  //@warning reading
  //@ set the others fields of move

    letters = normalizeWord(letters);
    
}
