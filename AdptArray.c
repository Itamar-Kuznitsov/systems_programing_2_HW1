// imports:
#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * First assigment in systems progaming cours No.2  - Adaptive array.
 * Author: Itamar Kuznitsov
 * Since : 2023
*/

// difining struct for adaptive array - AdptArray
typedef struct AdptArray_{
    int Arr_size;
    DEL_FUNC delete_func;
    COPY_FUNC copy_func;
    PRINT_FUNC print_func;
    PElement* PAdpt_element;

}AdptArray;



// initiat empty AdptArray:
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print){
    // allocating memory for new AdptArray
    PAdptArray newArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (newArr == NULL){
        return NULL;
    }
    // initiat AdptArray varuables - the function are given when you call CreateAdptArray
    newArr->Arr_size = 0;
    newArr->delete_func = del;
    newArr->copy_func = copy;
    newArr->print_func = print;
    newArr->PAdpt_element = NULL;
    
    return newArr;
}


// deleat AdptArray: 
void DeleteAdptArray(PAdptArray Parray){
    // if AdptArray not exist
    if(Parray == NULL){
        return;
    }

    for(int i= 0; i< Parray->Arr_size; i++){
        // if the item is null - dont call delete_func (becuse its not working with null)
        if((Parray->PAdpt_element)[i] == NULL){
            continue;
        }
        else{
            Parray->delete_func((Parray->PAdpt_element)[i]);
        }
    }
    // free PElement & free PAdptArray
    free(Parray->PAdpt_element);
    free(Parray);

}


// insert PElement item in the given lication
Result SetAdptArrayAt(PAdptArray Parray, int location, PElement element){
    // if AdptArray not exist
    if(Parray == NULL){
        return FAIL;
    }

    // if there is no place for the new item
    if(location >= Parray->Arr_size){
        // allocating new array in size of location+1
        PElement* newArray = (PElement*)calloc((location+1), sizeof(PElement));
        if(newArray == NULL){
            return FAIL;
        }

        // copy the elements from Parray to newArray
        memcpy(newArray, Parray->PAdpt_element, sizeof(PElement)*(Parray->Arr_size));
        free(Parray->PAdpt_element);
        Parray->PAdpt_element = newArray;

        // update AdptArray size
        Parray->Arr_size = location+1;
    }


    // only if item is not null - delete the previus item in array[location] 
    if((Parray->PAdpt_element)[location]!=NULL){
        Parray->delete_func((Parray->PAdpt_element)[location]);
    }
    // insert in array[location] copy of given element 
    (Parray->PAdpt_element)[location] = Parray->copy_func(element);
    return SUCCESS;
}


// return the element from the desire location:
PElement GetAdptArrayAt(PAdptArray Parray, int location){
    // if AdptArray not exist
    if (Parray == NULL){
        return NULL;
    }

    // if the index isn't valid 
    else if(location < 0 || location >= Parray->Arr_size){
        return NULL;
    }

    // if the item is null - dont call copy_func
    else if((Parray->PAdpt_element)[location] == NULL){
        return NULL;
    }

    PElement element = Parray->copy_func((Parray->PAdpt_element)[location]);
    return element;
}


// return the size of the array:
int GetAdptArraySize(PAdptArray Parray){
    int size = -1;
    // if AdptArray not exist
    if (Parray == NULL){
        return size;
    }

    size = Parray->Arr_size;
    return size;
}


// print AdptArray items:
void PrintDB(PAdptArray Parray){
    // if AdptArray not exist
    if(Parray == NULL){
        return;
    }

    for(int i= 0; i< Parray->Arr_size; i++){
        // if the item is null - dont call print_func
        if((Parray->PAdpt_element)[i] == NULL){
            continue;
        }
        else{
            Parray->print_func((Parray->PAdpt_element)[i]);
        }
    }
}

