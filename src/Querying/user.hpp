#pragma once 

#include "../Courses/courseDictionary.hpp"
#include <iostream> 

class user{
    public:
        user(std::string csv_data); 
        // Nests the User's actions in one function 
        void start(); 
        ~user();
        void printData(); 
    private:    
        courseDictionary* data; 
        void _print(); 
        void merge(std::vector<course *> to_merge);
        void filter(std::vector<course *> to_filter);
        std::vector<course *> last_search; 
        
};