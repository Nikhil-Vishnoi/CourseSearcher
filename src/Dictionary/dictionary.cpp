#include "dictionary.hpp"
#include <fstream> 


std::string read_line(std::ifstream& r) {
    std::string product; 
    char c; 
    // int i = 75; 
    while (c!='\n' ) {
        c = r.get(); 
        product += c;  
        // i--; 
    }
    return product; 
}
void dictionary::populate(std::string filename) {
    std::ifstream reader; 
    reader.open(filename); 
    while (reader){
        std::string line = read_line(reader); 
        // if(line.length()<=1) continue; 
        if(!(line != "\n" && line.length()>=4))
            continue; 
        // std::cout<<line; 
        // word  definition 
        
    }
}