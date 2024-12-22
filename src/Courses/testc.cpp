#include "csvParser.hpp"
#include "courseDictionary.hpp"
#include <iostream>
#include <stdio.h> 

int main(int len, char ** args) {
    // std::string s = "Testing,Tester,Testee,,,";
    // std::vector<std::string> prod = parse(s,','); 
    // for (std::string s: prod) {
    //     std::cout<<s<<"\tw\n"; 
    // }
    courseDictionary cd = courseDictionary("data/courses.csv");
    bool keeprunnin = true; 
    while(keeprunnin) {
        std::cout<<"\n\n__________________________________________\nSearch: "; 
        std::string input; 
        getline(std::cin, input, '\n');
        if (input == "quit") {
            keeprunnin = false; 
            continue; 
        }
        std::vector<course *> answer = cd.simple_query(input); 
        for (course *c : answer) {
            std::cout<<"\n"<<c->code<<" "<<c->number<<"  "<<c->name<<"\n"; 
            // for (int credit_hour: c->credit_hours) {
            //     std::cout<<credit_hour<<" "; 
            // }
            // std::cout<<"\t"; 
            std::cout<<c->desc; 
            // std::cout<<"\nPrerequisites: ";
            // for(std::string prereq : c->prereq) {
            //     if(prereq.size() > 1)
            //         std::cout<<prereq<<" ";
            // }
            std::cout<<"\n\n"; 
        }
    }
    
}