/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "tiles.h"

using namespace std;

Tiles::Tiles(){
    // To_do rellenar constructor vacio
}

Tiles::Tiles(int r, int c){
    setSize(r,c);
}

Tiles::Tiles(const Tiles & orig){
    *this = orig;
}

Tiles::~Tiles(){
    // To_do destructor
}

void Tiles::setSize(int r, int c){
    columns = c;
    rows = r;
}

Tiles&::operator=(const Tiles& orig){
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}

int Tiles::getWidth()const{
    return columns;
}

int Tiles::getHeight()const{
    return rows;
}

char Tiles::get(int r, int c)const{
    // To_do comprobación si son valores correctos
    return cell[r,c];
}

void Tiles::set(int r, int c, char l){
    cell[r,c] = l;
}

void Tiles::add(const Move&m){
    
}

void Tiles::print(std::ostream &os)const{
    
}

bool read(std::istream &is){
    
}

void Tiles::allocate(int r, int c){
     if (r > 0 && c > 0) {
        rows = r;
        columns = c;
        cell = new Tile[rows, columns];
    }
}

void Tiles::deallocate(){
    delete[] cell;
    initialize();
}

void Tiles::copy(Tiles t){
    int tCol = t.getWidth();  
    int tRows = t.getHeight();
    allocate(tRows, tCol);
    
    for (int i = 0; i < tRows; i++) {
        for(int k = 0; k < tCol; k++ ){
            set(i, k, t.get(i,k)); 
        }
    }
}

void initialize(){
    rows = 0;
    columns = 0;
    cell = nullptr;
}