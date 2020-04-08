/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <vector>           // Gestión de comandos


#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"

using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3

#define NUM_MAX_CMMDS 4
#define NUM_MIN_CMMDS 1
const string lang_flag = "-l" ;
const string input_flag = "-i" ;
const string random_flag = "-r" ;
const string bag_flag = "-b" ;

/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo="");       //Y una excepción?...

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param nwords Number of words found
 * @param score Number of points scored
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);


// Comando
struct Command{
        string flag ;
        string attribute ;
} ;

// Clase auxiliar para el manejo de comandos. ¿Mejor usando herencia?
class Commands{ //public: Command

private:
    
    //Comandos posibles
    string possible_cmmds[NUM_MAX_CMMDS] ;
    int num_possible_cmmds = 0 ;
    
    //Comandos introducidos
    Command cmmds[NUM_MAX_CMMDS] ;    
    int num_used_cmmds = 0 ;

public:
    
    //Comprueba si una flag esta en los comandos
    bool isIn(const string &s) const{
        bool found = false;
        for( int i=0 ; i < num_used_cmmds && !found ; i++ ) {
            if(cmmds[i].flag==s)
                found = true ;
        }
        return found ;
    }
    
    //Comprueba si una flag esta en los posibles comandos
    bool isPossible(const string &flag) {
        bool found = false;
        for( int i=0 ; i < num_possible_cmmds && !found ; i++ ) {
            if(possible_cmmds[i]==flag)
                found = true ;
        }
        return found ;
    }
    
    //Añade un posible comando
    void addPossible(const string &s) {
        possible_cmmds[num_possible_cmmds] = s ;
        num_possible_cmmds++ ;
    }

    //Añade un comando
    void add(const string &flag, const string &attribute) {

        if( isPossible(flag) ) {
            cmmds[num_used_cmmds].flag = flag ;
            cmmds[num_used_cmmds].attribute = attribute ;
            num_used_cmmds++ ;
        } else{
            errorBreak( ERROR_ARGUMENTS ) ;
        }
    }

    
    //Devuelve el atributo asociado a una flag. Debe usarse junto a isIn
    string getAttribute(const string &flag) const{
        string s = "" ;
        bool found = false ;
        for( int i=0 ; i < num_used_cmmds && !found ; i++ ) {
            if( cmmds[i].flag==flag ) {
                s = cmmds[i].attribute;
                found = true ;
            }
        }
        return s ;
    }
    
    //Devuelve la cantidad de posibles comandos
    int numPossibleCmmds( void ){
        return num_possible_cmmds ;
    }
    
    //Devuelve los comandos actuales
    int numUsedCmmds( void ){
        return num_used_cmmds ;
    }
    
} ;






/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char *args[]) {
    Bag bag;
    Player player;
    Language language;
    Move move;
    string word, lang="", goodmoves="", badmoves="", ifilename="", ofilename="";
    int random=-1, nwords=0, score=0;
    
    // I/O streams
    ifstream ifile; ofstream ofile;
    istream *input; ostream *output;
    
    //By deafult cin
    input = &cin ;
    
    /// @warning: Declare more vars when needed
    
    /// @warning: Check arguments

    /// @warning: Process arguments

	/*
	1. El main() recibe como parámetro obligatorio "-l <ID>" y co-
	mo parámetros opcionales "-i <file>" y "-r <random>" ,
	en cualquier orden entre los tres. Si se especifica "-i" se leen
	los datos desde ese fichero, si no, se leen desde el teclado. Si
	se especifica "-r" se define el aleatorio con el número indica-
	do, si no, no se define aleatorio.
	2. Crear una instancia de la clase Language con el anterior ID y
	mostrar el conjunto de caracteres permitido para ese lenguaje.
	3. Crear una instancia de la clase Bag, inicializar el generador de
	números aleatorios con el número aleatorio anterior, si es que
	se ha indicado, y definir su contenido en base al lenguaje que
	se ha declarado anteriormente.
	4. Crear una instancia de la clase Player y llenarla por comple-
	to con caracteres de la bolsa. Este objeto player deberá estar
	siempre ordenado de la A a la Z.
	5. Repetir la siguiente secuencia hasta que se lea un movimiento
	con la palabra "@"
	a) Usar el método read(...) para leer un movimiento (desde
	teclado o desde el fichero de entrada, según el parámetro
	"-i" ). Los valores para isHorizontal, row y column se leen
	pero se van a ignorar en el resto del programa, pues sólo se
	5Metodologı́a de la Programación
	MPALABRADOS (move)
	usará letters. En las anteriores prácticas se han usado pa-
	labras con letras controladas, pues, al fin y al cabo, todas
	provenı́an de bag, las cuales provienen del diccionario, y
	todas siguen el mismo patrón del juego scrabble: las letras
	son mayúsculas, no contienen tildes ni diéresis, aunque al-
	gunos caracteres internacionales están soportados, como
	la Ñ. Aunque no se ha usado hasta ahora, al incluir langua-
	ge.h en cualquier proyecto, también se incluye la definición
	de esta constante:
	static const std::string ALPHABET=toISO(” ABCDEFGHIJKLMNOPQRSTUVWXYZÑ”);
	Esto quiere decir que cualquier palabra que se consulte en
	el diccionario debe estar representada con caracteres de
	ese ALPHABET Esta es la primera vez que exponemos el
	programa a leer datos externos no controlados, por lo que
	habrı́a que transformar cada palabra de juego que se lee,
	a una palabra expresada en ese alfabeto. Y eso es lo que
	hace la función normalizeWord(...)
	b) Si la palabra leı́da es válida para el valor de Player (al me-
	nos ha de tener dos caracteres) entonces se anota la pala-
	bra, se calcula la puntuación de la palabra según el diccio-
	nario y se anota, se eliminan las letras de player, se sacan
	nuevas letras de bag para rellenar player, y se sigue ju-
	gando. Ya nos estamos acercando al ciclo de juego de la
	práctica final.
	c) Si la palabra leı́da no es compatible con el valor de player,
	se desecha y se lee el siguiente movimiento.
	6. Terminar con la llamada a HallOfFame para visualizar los re-
	sultados.
	7. Si en cualquier momento se presenta un error en los argumen-
	tos, en la apertura de ficheros o en la lectura de datos del fiche-
	ro, se debe usar la función errorBreak(...) para notificar el error
	y parar el programa.
	*/

    
    // Número de argumentos
    if( nargs % 2 != 0 && 2*NUM_MIN_CMMDS+1 <= nargs && nargs <= 2*NUM_MAX_CMMDS+1) {
    
        
        // Comandos a introducir
        Commands comandos ;
        
        // Posibles comandos
        comandos.addPossible(lang_flag) ;
        comandos.addPossible(input_flag) ;
        comandos.addPossible(random_flag) ;
        comandos.addPossible(bag_flag) ;
        
        //Añade los comandos introducidos por args
        
        for( int i=0 ; i < nargs/2 ; i++ ) {
            comandos.add(args[2*i+1], args[2*i+2] );
        }
        
        //Si no se ha introducido un lang o se ha introducido un lang incorrecto
        if( ! comandos.isIn(lang_flag) )
            errorBreak( ERROR_ARGUMENTS ) ;
        else
            lang = comandos.getAttribute(lang_flag) ;
        
        if( lang!="ES" && lang!="EN" && lang!="FR")
            errorBreak( ERROR_ARGUMENTS ) ;
        
        // Punto 3
        
        language.setLanguage(lang) ;
        
        cout << "LANGUAGE: " << lang << endl ;
        cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) << endl ;

        // Punto 4
        
        //Si se ha encontrado la flag de random, se asigna
        if(comandos.isIn( random_flag ) ) {
            random = stoi(comandos.getAttribute( random_flag )) ;
            bag.setRandom( random ) ;
        }
        
        bag.define(language) ;
        
        
        // Aunque se define la bolsa de forma aleatoria, se sobreescribe
        if( comandos.isIn( bag_flag ) )
            bag.set( comandos.getAttribute( bag_flag ) ) ;
        
        cout << "SEED: " << random  << endl ;
        
        cout << "BAG (" << bag.size() << ") : " << toUTF(bag.to_string()) ;
        
        
        // PUNTO 5
        
        player.clear() ;
        player.add( bag.extract(MAXPLAYER) ) ;

        //Comprueba el tipo de input
        if( comandos.isIn( input_flag ) ) {
            ifilename = comandos.getAttribute( input_flag ) ;
            ifile.open( ifilename ) ;
            if( !ifile ) {
                errorBreak( ERROR_OPEN, ifilename ) ;
            }
            input = &ifile ;
            cout << "Reading from " << ifilename << endl ;
        }

        // Punto 6
        
        // Lectura anticipada
            
        cout << endl << "PLAYER: " << toUTF(player.to_string()) ;

        // Lectura

        cout << endl << "READ: " ;
        
        move.read(*input) ;

        if( (*input).eof() )
                errorBreak( ERROR_DATA, ifilename ) ;
        
        word = toUTF(move.getLetters()) ;
        
        cout << endl << "THE WORD IS " << word << endl;
        
        while( word[0] != '@'  ) {
            
            if ( word.length() > 1 ) {
                
                   
                    nwords++;

                    score += move.findScore( language ) ;
                    
                    goodmoves += word + " - " ;

                    cout << " FOUND!" << move.findScore( language ) << " points" ;
                    
                    // Se limpia y se vuelve a rellenar
                    player.clear() ;
                    
                    player.add(bag.extract(MAXPLAYER-player.size())) ;

            } else {
                
                cout << " INVALID!" << endl;
            
            }
            

            
            cout << endl << "PLAYER: " << toUTF(player.to_string()) ;

            // Lectura

            cout << endl << "READ: " ;
            
            move.read(*input) ;

            if( (*input).eof() )
                errorBreak( ERROR_DATA, ifilename ) ;

            word = move.getLetters() ;
            
        }
        
//        // SOLUCION DO-WHILE MPALABRADOS 2
//        do {
//            player.add(bag.extract(7-player.size()));
//            cout << endl << "PLAYER: "<<toUTF(player.to_string())<<" BAG("<<bag.size()<<")"<<endl;
//            cout << "INPUT A WORD: ";
//            cin >> word;
//            word = toISO(word);
//            if (word.length()>1) {
//                cout << endl << toUTF(word);
//                if (player.isValid(word))  {
//                    if (language.query(word)) {
//                        nwords++;
//                        nletters += word.length();
//                        result += word+" - ";
//                        cout <<" FOUND!";
//                    } else {
//                        cout << " NOT REGISTERED!";
//                    }
//                    cout << endl<<endl;
//                    player.extract(word);
//                } else
//                    cout << " INVALID!" << endl;
//            }
//        }while (word.length()>1);
                
        
        // Cierra el archivo
        if( input == &ifile )
            ifile.close() ;
        
    } else {
        errorBreak( ERROR_ARGUMENTS ) ;
    }
    
    // Punto 7
    
    /// @warning: final report
    HallOfFame(language, random, bag, player, nwords, score, goodmoves);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " points "<<endl << 
            toUTF(result) << endl;    
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language>  [-r <randomnumber> -i <inputfile>]"<<endl;
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            //Modificado string, estaba "errors", se comprueba en test "error"
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
}


// Basura. Mejor y más bonito en la clase Commands
//bool getAttribute( const char c1[],char const *c2[], int n_c2) {
//    bool inside = false ;
//    for( int i=0 ; i<n_c2 && !inside; i++ ) {
//        //strcpm devuelve 0 si son iguales
//        if( strcmp(c1, c2[i] ) == 0 )
//            inside = true ;
//    }
//    return inside ;
//}
//
//void getAttribute( const char c1[],char const* c2[], const int n_c2, string &attribute ) {
//    
//    bool inside = false ;
//    for( int i=0 ; i<n_c2 && !inside; i++ ) {
//        //strcpm devuelve 0 si son iguales
//        if( strcmp(c1, c2[i] ) == 0 ) {
//            inside = true ;
//            //Usando & se copia el contenido de c2[i+1] directamente al string
//            strcpy(&attribute[0], c2[i+1]) ;       //Guarda el atributo asociado a la flag
//        }
//    }
//}
//
//
//bool isIn(const string &cad, const char &ch) {
//    
//    bool isin = false ;
//    
//    for( int i=0 ; i<cad.length() && !isin ; i++ ) {
//        if( cad[i] == ch )
//            isin = true ;
//    }
//    
//    return isin ;
//}
//Busca en la lista de comandos una flag, y si la encuentra le asigna al atributo
//bool assignAttribute(const Command commands[], int &n_commands, const string &flag, string &attribute){
//    unsigned short count_command  = 0;  //Por si se introduce más de una vez la misma flag
//    for( int i=0 ; i < n_commands ; i++ ) {
//        if( commands[i].flag == flag ) {
//            attribute = commands[i].attribute ;
//            count_command++ ;
//        }
//    }
//    
//    //Si el comando se repite
//    if(count_command > 1)
//        errorBreak( ERROR_ARGUMENTS ) ;
//    
//    if( count_command==0 )
//        return false ;
//    else
//        return true ;   //Se ha contado una vez la flag
//}
//
//bool assignAttribute(const Command commands[], int &n_commands, const string &flag, int &attribute){
//    unsigned short count_command  = 0;  //Por si se introduce más de una vez la misma flag
//    for( int i=0 ; i < n_commands ; i++ ) {
//        if( commands[i].flag == flag ) {
//            attribute = atoi(commands[i].attribute.c_str()) ;   //Transforma string a cstring para poder aplicar atoi
//            count_command++ ;
//        }
//    }
//    
//    //Si el comando se repite
//    if(count_command > 1)
//        errorBreak( ERROR_ARGUMENTS ) ;
//    
//    if( count_command==0 )
//        return false ;
//    else
//        return true ;   //Se ha contado una vez la flag
//}