#pragma once 

#include <vector> 
#include <string>
#include <fstream> 

std::vector<std::string> parse(const std::string& line, char delim); 

std::vector<std::vector<std::string>> decompose(std::string filename, char delim); 
