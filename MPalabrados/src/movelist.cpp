/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 **/

// Alumno

#include <iostream>
#include <ostream>
#include <string>

#include "movelist.h"
#include "move.h"
#include <stdexcept>

using namespace std;

/// Private
void Movelist::allocate(int n)
{
    nMove = n ;
    moves = new Move[nMove] ;
}

void Movelist::deallocate()
{
    nMove = 0 ;
    delete [] moves ;
    moves = 0 ;
}

void Movelist::copy(const Movelist& ml)
{
	// Si tienen distinta capacidad
	if( nMove != ml.nMove ) {

		nMove = ml.nMove ;
		
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


Movelist::Movelist() {}

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
	this->copy(orig) ;
        return *this ;
}

Move Movelist::get(int p) const
{
    if( !(0<=p && p < nMove) )
        throw bad_alloc ;
    
    return moves[p] ;
}

void Movelist::set(int p,const Move& m)
{
    if( !(0<=p && p < nMove) )
        throw bad_alloc ;
    moves[p] = m ;
}

int Movelist::find(const Move& mov) const
{
    bool found = false ;
    int pos=0;
    
    for( ; pos < nMove && !found ; pos++ )
        if( moves[pos]==mov )
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
    if( !(0<=p && p < nMove) )
        throw bad_alloc ;
    
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
    int count = 0 ; Move move_word ;
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

void Movelist::getScore()
{
    int score_total = 0 ; 
    int score_tmp = 0 ;
    bool bad_score = false ;
    
    for(size_t i=0 ; i < nMove && !bad_score; ++i) {
        score_tmp = moves[i].score() ;
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
    size_t count = 0 ;
    
    Move in ;
    
    //Lectura anticipada
    in.read(is) ; 
    
    if(is.eof())
        return !ok ;
    
    while(in.letters != "_") {
        
        this->add(in) ;
           
        in.read(is) ; 
        
        if(is.eof())
            return !ok ;
    }
    
    return ok ;
}