/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 **/

// Alumnos: José David Rico Días 
//          Jorge Marín Sánchez

#include <iostream>
#include <ostream>
#include <string>
#include <assert.h>

#include "movelist.h"
#include "move.h"

using namespace std;

/// Private
void Movelist::allocate(int n)
{
    nMove = n ;
    moves = new Move[nMove] ;
}

void Movelist::deallocate()
{
    this->nMove = 0 ;
    delete[] this->moves ;
}

void Movelist::copy(const Movelist& ml)
{
	// Si tienen distinta capacidad
	if( nMove != ml.nMove ) {

		this->nMove = ml.nMove ;
		
		// Como quiero copiar, borro los movimientos actuales
		deallocate() ;
	
		// Reservo memoria para la copia
		allocate(nMove) ;
	}
	
	// Copia los movimientos
	for(size_t i=0 ; i < nMove ; ++i ) {
		moves[i] = ml.moves[i] ;
	}
}


Movelist::Movelist():nMove(0) {}

Movelist::Movelist(int nmov): nMove(nmov)
{
	allocate(nmov) ;
}

Movelist::Movelist(const Movelist& orig) {
	this->copy(orig) ;
}

Movelist::~Movelist()
{
	this->deallocate() ;
}

void Movelist::assign(const Movelist& orig)
{
	this->copy(orig) ;
}


void Movelist::operator=(Movelist& orig)
{
	orig.copy(*this) ;
}

Move Movelist::get(int p) const
{
    assert( !(0<=p && p < nMove) ) ;
    
    return moves[p] ;
}

void Movelist::set(int p,const Move& m)
{
    assert( !(0<=p && p < nMove) ) ;
        
    moves[p] = m ;
}

int Movelist::find(const Move& mov) const
{
    bool found = false ;
    int pos=0;
    
    for( ; pos < nMove && !found ; pos++ )
        if( moves[pos].getCol()==mov.getCol() && moves[pos].isHorizontal() == mov.isHorizontal()
            && moves[pos].getLetters()==mov.getLetters() && moves[pos].getRow() == mov.getRow()
            && moves[pos].getScore()==mov.getScore())
            found = true ;
    
    if(!found)
        return -1 ;
    
    return pos ;
    
}

void Movelist::add(const Move& mov)
{
    Movelist tmp = *this ;  //Guarda el objeto de forma temporal
    
    // Borra el objeto actual
    this->deallocate() ;
    
    // Crea uno nuevo con 1 más de espacio
    this->allocate(tmp.nMove+1) ;   // Ahora this->nMove a aumentado en 1

    // OJO, no hay que usar copy, ya que eso hace que los 2 objetos sean iguales
    // Lo que buscamos es cambiar el objeto
    
    // Copio los movimientos de tmp al objeto actual
    for( size_t i=0 ; i < tmp.nMove ; ++i ) {
        this->moves[i] = tmp.moves[i] ;
    }
 
    // Añado el nuevo objeto
    this->moves[tmp.nMove] = mov ;
    
}

void Movelist::remove(int p)
{
    assert( !(0<=p && p < nMove) ) ;
    
    nMove-- ;
    // Borra el movimiento en p sobreescribiendo
    for( size_t i=p ; i<nMove; ++i)
        moves[i] = moves[i+1] ;
    
    // Ahora hay que redimensionar la memoria, olvidándonos del último valor
    Movelist tmp = *this ;
    
    this->deallocate() ;
    this->allocate(nMove) ;
    
    // Copia desde tmp a *this
    for( size_t i=0 ; i < nMove ; ++i )
        this->moves[i] = tmp.moves[i] ;
}

void Movelist::remove(const Move& mov)
{
    // Si encuentra el movimiento, le pasa la posición a remove(int p)
    int pos=find(mov) ;
    if( pos>=0 ) {
        this->remove(pos) ;
    }
}


void Movelist::zip(const Language& l)
{
    int count = 0 ; string move_word ;
    while(count<nMove) {
        move_word = moves[count].getLetters() ;
        
        // Si no tiene al menos 2 letras o no es válida, se borra
        if( move_word.length() < 2 || !l.query(move_word) )
            this->remove(moves[count]) ;
        else
            count++ ;
    }
}

void Movelist::clear()
{
    deallocate() ;
}

int Movelist::getScore() const
{
    int score_total = 0 ; 
    int score_tmp = 0 ;
    bool bad_score = false ;
    
    for(size_t i=0 ; i < nMove && !bad_score; ++i) {
        score_tmp = moves[i].getScore() ;
        if( score_tmp != -1 )
            score_total += score_tmp ;
        else
            bad_score = true ;
    }
    
    if( bad_score )
        return -1 ;

    return score_total ;
}

bool Movelist::print(std::ostream &os, bool scores) const
{
    bool res=true;
    for ( size_t i=0; i<size() && res; ++i ) {
        get(i).print(os);
        if (scores)
            os << " ("<<get(i).getScore()<<") - ";
        else
            os << " - ";
        if (os.bad())
            res=false;
    }
    return res;
}

bool Movelist::read(std::istream &is)
{
    
    bool ok = true ;
    //size_t count = 0 ;
    
    Move in ;
    
    //Lectura anticipada
    in.read(is) ; 
    
    while(in.getLetters() != "_") {
        
        if(is.eof())
            return !ok ;
        
        this->add(in) ;
           
        in.read(is) ;
        

    }
    
    return ok ;
}