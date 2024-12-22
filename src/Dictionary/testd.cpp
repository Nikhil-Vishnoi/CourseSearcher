#include <iostream> 
#include "query.hpp" 
#include "searcher.hpp" 
#include "../Dictionary/dictionary.hpp"
/*
 * Where the engine takes in search queues. 
*/
int main(int arg_len, char ** arg) {
    char * c = arg[1]; 
    dictionary d = dictionary(); 
    d.populate("data/Oxford English Dictionary.txt");
    // std::string s = c; 


    // std::cout<<s<<"\n"; 
}