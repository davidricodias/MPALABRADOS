/**
 * @file tiles.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include "tiles.h"

using namespace std;

Tiles::Tiles() {
    cell=nullptr;
    columns=0;
    rows=0;
}

Tiles::Tiles(int r, int c) {
    cell=nullptr;
    allocate(r,c);
}

Tiles::Tiles(const Tiles& orig) {
    cell = nullptr;
    copy(orig);
}

Tiles::~Tiles() {
    deallocate();
}

Tiles& Tiles::operator=(const Tiles& orig) {
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}

void Tiles::setSize(int r, int c) {
    allocate(r,c);
}

void Tiles::add(const Move& m) {
    if (cell != nullptr) {
        string word = m.getLetters();

        int x = m.getCol() - 1, y = m.getRow() - 1; // translate coords to pos into the matrix
        if (y >= 0 && x >= 0)
            for (int i = 0; i < word.size() && y < getHeight() && x < getWidth(); i++) {

                set(y, x, word[i]);
                if (m.isHorizontal())
                    x++;
                else
                    y++;
            }
    }
}

int Tiles::getWidth() const {
    return columns;
}

int Tiles::getHeight() const {
    return rows;
}

char Tiles::get(int r, int c) const  {
    assert (cell != nullptr && r >=0 && r<=getHeight() && 0<=c && c <= getWidth());
    return cell[r][c];
}

void Tiles::set(int r, int c, char l) {
    assert (cell != nullptr && r>= 0 && r<=getHeight() && c >= 0 && c <= getWidth());
    cell[r][c] = l;    
}
	 
void Tiles::print(std::ostream &os) const {
    os << getHeight() << " " << getWidth() << endl;
    for (int f = 0; f < getHeight(); ++f) {
        for (int c = 0; c < getWidth(); ++c) {
            os << toUTF(get(f,c))<<" ";
        }
        os << endl;
    }
    os << endl;
} 

bool Tiles::read(std::istream &is){
    int n, m;
    string car;
    is >> n >> m;
    deallocate();
    allocate(n,m);
    for (int f = 0; f < getHeight(); f++) {
        for (int c = 0; c < getWidth(); c++) {
            is >> car;
            set(f,c, toISO(car)[0]);
        }
    }
}

/// Privados

void Tiles::allocate(int r, int c) {
    assert (r > 0 && c> 0);
    columns=c;
    rows=r;
    cell = new char*[r];
    cell[0] = new char[r * c];
    for (int i = 1; i < r; ++i)
        cell[i] = cell[i - 1] + c;
    for (int row = 0; row < r; ++row) {
        for (int column = 0; column < c; ++column) {
            set(row,column,EMPTY);
        }
    }
}

void Tiles::deallocate() {
    if (cell != nullptr) {
        delete[] cell[0];
        delete[] cell;
        cell = nullptr;
    }
}

void Tiles::copy(const Tiles& otro) {
    allocate(otro.getHeight(), otro.getWidth());
    for (int f = 0; f < otro.getHeight(); ++f) {
        for (int c = 0; c < otro.getWidth(); ++c) {
            set(f,c, otro.get(f,c));
        }
    }
}
