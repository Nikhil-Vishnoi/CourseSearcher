#include "user.hpp"

user::user(std::string data_loc) { 
    data = new courseDictionary(data_loc); 
}

user::~user() {
    delete data; 
}
void user::printData(){
    std::cout << *data;
}
void print_result(std::vector<course *> to_print) {
    for (course *c : to_print) {
        std::cout << c << "\n\n"; 
    }
}
bool invect(std::vector<course*> vect, course* query) {
    for (course* c: vect){
        if ( c->name == query->name ) return true; 
    }
    return false; 
}
void user::merge(std::vector<course *> to_merge) { 
    for (course* c: to_merge) {
        if (invect(last_search, c) == false) {
            last_search.push_back(c); 
        }
    }
}
void user::filter(std::vector<course *> to_filter) {
    std::vector<course*> new_last_search; 
    for (course* c: last_search) {
        if (invect(to_filter,c)) {
            new_last_search.push_back(c); 
        }
    }
    last_search = new_last_search; 
}
void user::start() {
    bool keeprunnin = true; 
    bool conjoin = false;
    bool overlap = false; 
    while(keeprunnin | conjoin | overlap) {
        std::string input; 
        if (keeprunnin) {
            std::cout<<"\n\n__________________________________________\nSearch: "; 
            getline(std::cin, input, '\n');
            last_search = data->simple_query(input); 
        }else if (conjoin) {
            std::cout<<"______________________________________________\nJoin Prev Search Results With: "; 
            getline(std::cin, input, '\n'); 
            std::vector<course *> second_query = data->simple_query(input); 
            merge(second_query); 
        }else if (overlap) {
            std::cout<<"______________________________________________\nFilter Prev Search Results With: "; 
            getline(std::cin, input, '\n'); 
            std::vector<course *> second_query = data->simple_query(input); 
            filter(second_query); 
        }
        if (input == "quit") {
            keeprunnin = false; 
            continue; 
        }
        print_result(last_search); 
        std::cout<<"Search Options (1=AND,2=OR, anything else = NEXT_SEARCH): ";
        std::string inp; 
        getline(std::cin, inp, '\n');
        if(inp == "2") {
            conjoin = true; 
            keeprunnin = false; 
            overlap = false; 
        }else if (inp == "1") {
            conjoin = false; 
            keeprunnin = false; 
            overlap = true; 
        }else {
            conjoin = false; 
            keeprunnin = true; 
            overlap = false; 
        }
    }
 
}