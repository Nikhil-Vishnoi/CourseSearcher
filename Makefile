CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes 

dictionary: bin/exec
search: bin/course_searchability
engine: bin/engine 

bin/dictionary: ./src/Dictionary/testd.cpp  ./src/Dictionary/dictionary.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

bin/course_searchability: ./src/Courses/*.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

bin/engine: ./src/Courses/courseDictionary.cpp ./src/Courses/csvParser.cpp ./src/Querying/*.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := engine
.PHONY: exec tests clean search engine 

clean:
	rm -f bin/*