#include "courseDictionary.hpp" 
int indexOf(std::string s, char c) {
    for (unsigned i = 0; i < s.size(); i++) {
        if ( c == s.at(i) ) return i; 
    }
    return -1; 
}
// Populates the courses vector 
courseDictionary::courseDictionary(std::string csv_loc) {
    std::cout<<"Working on decomposing file...\n"; 
    std::vector<std::vector<std::string>> file_contents = decompose(csv_loc,'|');
    // Removes capitilizations in the description 
    // auto asciitolower = [] (char in) {
    //     if (in <= 'Z' && in >= 'A') {
    //         return static_cast<char>(in - ('Z'-'z'));
    //     }else {
    //         return in; 
    //     }
    // };
    // Skipping the first line because it is just meta data 
    for (unsigned l = 1; l < file_contents.size(); l++) {
        course *c = new course(); 
        std::string course_id = file_contents.at(l).at(0); 

        c->id     = course_id; 
        c->number = stoi(course_id.substr(indexOf(course_id,' ')+1)); 
        c->code   = course_id.substr(0,indexOf(course_id,' ')); 
        c->name   = file_contents.at(l).at(1); 
        std::string ch = file_contents.at(l).at(2);
        std::vector<std::string> split = parse(ch.substr(1,ch.size()-1),'_'); 
        for (std::string credit_hour: split) {
            c->credit_hours.push_back((stoi(credit_hour))); 
        }
        c->desc  = file_contents.at(l).at(3);
    //  Removes capitilizations in the description. 
    //    std::transform(c->desc.begin(), c->desc.end(), c->desc.begin(), asciitolower);


        std::string related = file_contents.at(l).at(4); 
        if(related.length() > 2)
            c->strong_relation = parse(related.substr(1,related.size()-3),'_'); 
        Courses.push_back(c);
    }
    std::cout<<"Finished decomposing file!\n";
}
std::vector<course *> courseDictionary::simple_query(std::string query) {
    std::vector<course*> prod; 
    for(course* c: Courses) {
        // Case 1 Query Small 
        if (c->desc.find(query) != -1 || c->name.find(query) != -1 || c->id.find(query) != -1)  
        {
            prod.push_back(c); 
            // std::cout<<"MATCHES\n"; 
            continue; 
        }
        // Case 2 Query Big 
        if ((c->desc.size()>1 && query.find(c->desc) != -1 ) || query.find(c->name) != -1 || query.find(c->id) != -1)  
        {
            prod.push_back(c); 
            // std::cout<<"MATCHES\n"; 
            continue; 
        }
    }
    return prod; 
}

// Binary Search. "DEPID NUMBER"
course* courseDictionary::search(std::string course_id) {
    return (Courses.at(0));
}
courseDictionary::~courseDictionary() {
    for (unsigned l = 0; l < Courses.size(); l++) {
        delete Courses.at(l);   
    }
}
// Courses are compared with their id to affirm no duplicates are created 
// when reading from webscraped data 
bool course::operator==(course* c1) {
    return (c1->id == id); 
}


std::ostream& operator<<(std::ostream& os, courseDictionary& cD) {
     for (auto datum:cD){
        os << datum; 
     }
     return os; 
}
std::ostream& operator<<(std::ostream& os, course* course) {
    os << course->id <<"\n" << course->name << "\n" << course->desc << "\n"; 
    bool flag = true; 
    for (auto rec : course->strong_relation) {
        if (flag && rec.length() > 1)  
            os << "Related to: "; 
        flag = false; 
        os << rec << " ";
    }
    os << "\n"; 
    return os; 
}
