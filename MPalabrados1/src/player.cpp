/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cstring>
#include "player.h"
///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos){
    cstr.iminar(pos+1, pos);
    
    return cstr;
}

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr){
    // Algoritmo QuickSort para ordenar alfabericamente
    int low, high;
    
    int pivot;
 
    if (high < low) {
        pivot = divide(array, start, end);
    
        // Ordeno la lista de los menores
        quicksort(array, start, pivot - 1);
 
        // Ordeno la lista de los mayores
        quicksort(array, pivot + 1, end);
    }
}
