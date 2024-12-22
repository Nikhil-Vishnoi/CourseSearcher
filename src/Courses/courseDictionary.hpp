#pragma once 

#include "csvParser.hpp" 
#include <algorithm> 
#include <iostream> 

enum RuleType{
    GreaterThan,
    LessThan
};
struct course{
    // DEPCODE COURSENUMBER 
    std::string id; 
    // Department Code 
    std::string code;
    // Course Number 
    int number;  
    std::string name; 
    std::vector<int> credit_hours; 
    std::string desc; 
    // Course ids that show up in the description are stored for seemless graph building 
    std::vector<std::string> strong_relation; 
    // Get Post Product Defined 
    std::vector<course *> closely_related_to;  

    bool operator==(course* c1); 
};
class courseDictionary{
    public: 
        // Populates the courses vector 
        courseDictionary(std::string csv_loc); 
        // Specifically finds the course_id and also does some work to 
        // figure out if 
        course* search(std::string course_id); 

        // Simple Searching 
        std::vector<course *> simple_query(std::string query); 
        // Search by Credit Hours 
        std::vector<course *> credit_hour_rule(int rule, RuleType ruletype);
        // std::vector<course *> 
        ~courseDictionary(); 

        // Iterator for course dictionary to make creating graphs easier 
        std::vector<course*>::iterator begin(){
            return std::begin(Courses); 
        };
        std::vector<course*>::iterator end(){
            return std::end(Courses);
        };

        friend std::ostream& operator<<(std::ostream& os, courseDictionary& cD); 
        
    private:
        std::vector<course*> Courses; 
};

std::ostream& operator<<(std::ostream& os, course* course);

// bool operator==(course*,course*); 