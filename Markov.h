#ifndef MARKOV_H_INCLUDED
#define MARKOV_H_INCLUDED

#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

struct relation{
    std::string word;
    std::vector<std::string> follow_list;
    relation(std::string inp_word)
    : word(inp_word){}
};

class Markov{
public:
    Markov(std::string);
    void listVector();
    void generateChain(int);
private:
    void loadFile(std::string);
    std::string getWord();
    void fillRelation();
    std::string _file_buffer;
    std::vector<relation> _relation_list;
    unsigned long long int _point_buffer;
    bool _end_file;
    std::string _prev_word;
    bool _init_switch;
    bool _special_switch;
    std::string _special_char;
};


#endif
