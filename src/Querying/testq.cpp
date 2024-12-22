#include "user.hpp"

#include <iostream>
int main(int len, char ** args) {
    std::cout<<"Welcome to the UIUC Searchable Course Database!\n"; 
    std::cout<<"Setting up system...\n"; 
    user u = user("data/courses.csv"); 
    std::cout<<"Guest User Finished Setting up!\nBooting up browser...\n"; 
    u.start(); 
}