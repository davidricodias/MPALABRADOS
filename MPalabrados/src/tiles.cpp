/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "tiles.h"
#include <stdexcept>

using namespace std;

Tiles::Tiles(){
    setSize(0,0) ;
    allocate(1, 1) ;
}

Tiles::Tiles(int r, int c){
    setSize(r,c);
}

Tiles::Tiles(const Tiles & orig){
    copy(orig);
}

Tiles::~Tiles(){
    deallocate() ;
}

void Tiles::setSize(int r, int c){
    columns = c;
    rows = r;
}

Tiles&::operator=(const Tiles& orig){
    if (this != &orig) {
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
    // Tiles start at 0,0
    if(0<= r-1 && r-1 < rows && 0 <= c-1 && c-1 < columns) ; 
        throw invalid_argument("Intentó acceder a una posición inválida") ;
    return cell[r-1][c-1] ;     
}

void Tiles::set(int r, int c, char l){
    if(0<= r-1 && r-1 < rows && 0 <= c-1 && c-1 < columns) ; 
        throw invalid_argument("Intentó escribir en una posición inválida") ;
    cell[r-1][c-1] = l;
}

// TODO
void Tiles::add(const Move&m){
    cout << "TODO" ;
}

void Tiles::print(std::ostream &os)const{
    for( int i=0 ; i<columns ; ++i ) {
        for( int j=0 ; j<rows ; ++j ) {
            *os << cell[i][j] << ' ' ;
        }
        *os << '\n' ;
    }
}

bool Tiles::read(std::istream &is){
    bool end = false ;
    
    for( int i=0 ; i<columns && !end ; ++i ) {
        for( int j=0 ; j<rows && !end ; ++j ) {
            if(is->eof())
                end = true
            *is >> cell[i][j] ;
        }
    }
    return !end ;
}

void Tiles::allocate(int r, int c){
    if (r > 0 && c > 0) {
        rows = r;
        columns = c;
        
        // Espacio para las columnas
        // [ *char1, *char2, ... ]
        cell = new char[columns] ;
        
        
        // Espacio para las filas
        // [ *char1,  *char2,  ... ]
        // [ *char11, *char21, ... ]
        // [ *char12, *char22, ... ] 
        for( int i=0 ; i<columns ; ++i)
            *cell[i] = new char[rows] ;
         
    } else {
        throw invalid_argument("No se pudo reservar memoria") ;
    }
}

void Tiles::deallocate(){
    if( cell != nullptr) {
        // Borra cada fila
        for( int i=0 ; i<columns ; ++i)
            delete [] *cell[i] ;

        delete [] cell ;    
    }
}

void Tiles::copy(Tiles &t){
    
    rows = t.rows ;
    columns = t.columns ;
    
    deallocate() ;
    allocate(rows, columns);
    
    for (int r = 0; r < rows; ++r ) {
        for(int c = 0; c < columns; ++ c ) {
            set( r, c, t.cell[r][c] ) ;
        }
    }
}
