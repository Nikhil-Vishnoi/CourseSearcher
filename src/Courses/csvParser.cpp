#include "csvParser.hpp" 
#include <iostream>
/*
 * Helper function to read line by line with an input file stream reader 
 * @param r                  File that is having its next line grabbed from buffer 
 * @return std::string       The line is stored and returned in a std::string  
 */
std::string read_line(std::ifstream& r) {
    std::string product; 
    char c = '\0'; 
    // int i = 75; 
    while (c!='\n' && r) {
        c = r.get(); 
        product += c;  
    }
    if (r)
        return product; 
    else 
        return ""; 
}

/*
 * Parses through the file and returns a 2D Matrix of the file 
 * @param filename                                  String storing where the csv is located 
 * @param delim                                     Delim for the csv formatting 
 * @return std::vector<std::vector<std::string>>    The entire contents of the file in a 2D Matrix that is split up 
*/
std::vector<std::vector<std::string>> decompose(std::string filename, char delim){
    std::ifstream reader; 
    std::vector<std::vector<std::string>> prod; 
    reader.open(filename); 
    while (reader){
        std::string line = read_line(reader); 
        // Junk away lines that have no sustinance 
        if(!(line != "\n" && line.length()>=4)) {
            // std::cout<<"LINE JUNKED"<<"\n";
            continue;         
        }
        // std::cout<<line<<"\n";
        std::vector<std::string> line_data = parse(line, delim); 
        prod.push_back(line_data); 
    }
    return prod; 
}



/*
 * Parses through the line and splits it up using the delimeter 
 * @param line          Text being Processed 
 * @param delim         Character that symbolizes next item 
 */
std::vector<std::string> parse(const std::string& line, char delim) {
    std::vector<std::string> prod; 
    std::string wrk; 
    for (unsigned i = 0; i < line.size(); i++) {
        if (line.at(i) == delim) {
            prod.push_back(wrk); 
            wrk = std::string(); 
            continue; 
        }
        wrk = wrk + line.at(i); 
    }
    // if (wrk.length() >= 1)
    prod.push_back(wrk);
    return prod; 
}