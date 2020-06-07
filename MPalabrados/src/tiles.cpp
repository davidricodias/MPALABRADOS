/**
 * @file tiles.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
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

Move Tiles::findMaxWord(int r, int c, bool hrz) const{
    Move current_move;
    if(hrz){
        
        // Vamos a desplazarnos por la fila hasta el inicio
        int k=c;
        while(get(r,k-1)!=EMPTY || k!=0){
               k--;
        }
        
        // En este punto k es la posición donde comienza la palabra
        int j = 0;
        // Calculo el número de letras que tiene este movimiento
        while(get(r,k+j)!=EMPTY || j<getWidth()){
            j++;
        }

        char *letras;
        letras = new char [j];

        // Relleno el vector con las letras del movimiento
        for(int i=0; i<j; i++){
            letras[i] = get(r,k+i);
        }

        current_move.set(r,k,'H',letras);

		delete [] letras;

    }else{
        // Vamos a desplazarnos por la columna hasta el inicio
        int k=r;
        while(get(k-1,c)!=EMPTY || k!=0){
            k--;
        }
        
        // En este punto k es la posición donde comienza la palabra
        int j = 0;
        // Calculo el número de letras que tiene este movimiento
        while(get(k+j,c)!=EMPTY || j<getHeight()){
            j++;
        }

        char *letras;
        letras = new char [j];

        // Relleno el vector con las letras del movimiento
        for(int i=0; i<j; i++){
            letras[i] = get(k+i,c);
        }

        
        current_move.set(k,c,'V',letras);

		delete [] letras;
    }
    
    return current_move;
    
}

Movelist Tiles::findCrosswords(const Move &m, const Language &l) const{
    
    Movelist current_movelist;
    // Guardo las posiciones donde comienza el movimiento y donde terminaría
    int m_col = m.getCol();
    int m_row = m.getRow();
    int m_col_end = m_col + m.getLetters().size();
    int m_row_end = m_row + m.getLetters().size();
 
    
    Move current_move;
    // Regla 3: Cruce intermedio
    current_move = findMaxWord(m_row, m_col, m.isHorizontal());
    current_move.findScore(l);
    
    // Regla 2:
    if(l.query(current_move.getLetters())){
        current_movelist.add(m);
    }
    // Regla 6: Se sale de la matriz
        // Exeso de tamaño en horizontal
    bool exec_H = m.isHorizontal() && (m_col + m.getLetters().size()) > this->getWidth();
        // Exeso de tamaño en vertical
    bool exec_V = !m.isHorizontal() && (m_col + m.getLetters().size()) > this->getHeight();
    
    if(exec_H || exec_V){
        current_move.setScore(-2); // -2 indica BOARD_OVERFLOW
        current_movelist.add(current_move);
        return current_movelist;
        
    // Regla 8: La palabra no existe en el lenguaje
    } else if(!l.query(current_move.getLetters())){
        current_move.setScore(-3); // -3 indica NONEXISTENT_WORD
        current_movelist.add(current_move);
        return current_movelist;
        
    // Regla 10: Primera casilla ocupada
    } else if(get(m_row, m_col)!=EMPTY){
        current_move.setScore(-5); // -5 indica NOT_FREE
        current_movelist.add(current_move);
        return current_movelist;
           
    // Regla 9: No hay cruces    
    } else if(current_move.isHorizontal()){
        // Compruebo si hay letras antes o después del movimiento para ver si complementa otra letra
        if((get(m_row, m_col-1) == EMPTY) && (get(m_row, m_col_end+1) == EMPTY)){
            // Si no hay letras a los laterales recorro todas las letras del movimiento buscando
            // letras encima o abajo
            int i=0;
            while((get(m_row+1, m_col+i)==EMPTY) && (get(m_row-1, m_col+i)==EMPTY)){
                i++;
                if(m_row+1 > m_row_end){
                    
                    // Regla 1: inicio de partida
                    bool vacio = true; // nos indicará si la matriz está vacia
                    for(int i=0; i<getWidth(); i++){
                        for(int j=0; j<getHeight(); i+=2){
                            if(get(i,j)!=EMPTY){
                                vacio=false;
                                break;
                            }
                        }
                    }
                    
                    if(vacio){
                        current_move.setScore(m.findScore(l));
                    }else{
                        current_move.setScore(-6); // -6 indica MISSING_CROSSWORDS
                        current_movelist.add(current_move);
                        return current_movelist;
                    }
                    break;
                }
            }
        }
        
    } else if(!m.isHorizontal()){
        // Compruebo si hay letras antes o después del movimiento para ver si complementa otra letra
        if((get(m_row-1, m_col) == EMPTY) && (get(m_row+1, m_col_end) == EMPTY)){
            // Si no hay letras a los laterales recorro todas las letras del movimiento buscando
            // letras encima o abajo
            int i=0;
            while((get(m_row+i, m_col+1)==EMPTY) && (get(m_row-i, m_col+1)==EMPTY)){
                i++;
                if(m_col+1 > m_col_end){
                    
                    // Regla 1: inicio de partida
                    bool vacio = true; // nos indicará si la matriz está vacia
                    for(int i=0; i<getWidth(); i++){
                        for(int j=0; j<getHeight(); i+=2){
                            if(get(i,j)!=EMPTY){
                                vacio=false;
                                break;
                            }
                        }
                    }
                    
                    if(vacio){
                        current_move.setScore(current_move.findScore(l));
                    }else{
                        current_move.setScore(-6); // -6 indica MISSING_CROSSWORDS
                        current_movelist.add(m);
                        return current_movelist;
                    }
                    break;
                }
            }
        }
    } 
    
    
    // Regla 11: Algún cruce no válido
    for(int i=0; i<m.getLetters().size(); i++){
        Move aux_move;
        if(m.isHorizontal()){
            aux_move = findMaxWord(m_row, m_col+i, !m.isHorizontal());
            if(!l.query(aux_move.getLetters())){
                aux_move.setScore(-3); // -3 indica NONEXISTENT_WORD
                current_movelist.add(aux_move);
                return current_movelist;
            }else{ //Regla 4: Cruce multiple
                aux_move.setScore(current_move.findScore(l));
                current_movelist.add(aux_move);
            }
            
        }else{
            aux_move = findMaxWord(m_row+i, m_col, !m.isHorizontal());
            if(!l.query(aux_move.getLetters())){
                aux_move.setScore(-3); // -3 indica NONEXISTENT_WORD
                current_movelist.add(aux_move);
                return current_movelist;
            }else{ //Regla 4: Cruce multiple
                aux_move.setScore(aux_move.findScore(l));
                current_movelist.add(aux_move);
            }
        }
    }
    
        
    return current_movelist;
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


