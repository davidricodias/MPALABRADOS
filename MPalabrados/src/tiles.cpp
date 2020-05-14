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
    // To_do
}

Tiles::~Tiles(){
    // To_do destructor
}

void Tiles::setSize(int r, int c){
    columns = c;
    rows = r;
}

Tiles&::operator=(const Tiles& orig){
    // To_do igualar this a orig
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
    
}

void Tiles::deallocate(){
    
}

void Tiles::copy(Tiles t){
    
}
