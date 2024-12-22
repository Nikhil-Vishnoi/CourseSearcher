#include <string>
#include <iostream> 
#include <vector> 

struct Word{
    std::string word; 
    std::string word_type; 
    std::string definition; 
};
class dictionary {
    public: 
        void populate(std::string filename);
        std::vector<Word> pull() { return dict; }
        dictionary() = default; 
    private:
        std::vector<Word> dict; 
}; 
