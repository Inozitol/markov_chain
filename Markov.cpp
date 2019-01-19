#include "Markov.h"

Markov::Markov(std::string input)
: _point_buffer(0), _init_switch(false), _special_switch(false){
    loadFile(input);
    fillRelation();
    srand(time(NULL));
}

void Markov::loadFile(std::string file_name){
    std::ifstream file(file_name);

    file.seekg(0, std::ios::end);
    _file_buffer.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    _file_buffer.assign((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

    file.close();

    std::transform(_file_buffer.begin(), _file_buffer.end(), _file_buffer.begin(), ::tolower);
}

std::string Markov::getWord(){
    bool trigger=false;
    std::string word_buffer;

    if(_end_file==true){
        return "-1";
    }
    if(_special_switch==true){
        _special_switch=false;
        return _special_char;
    }
    if(_file_buffer[_point_buffer]==' '){
        _point_buffer++;
    }
    while(trigger!=true){
        if(_point_buffer>=_file_buffer.length()){
            _end_file=true;
            trigger=true;
        }
        if((_file_buffer[_point_buffer]<='z' && _file_buffer[_point_buffer]>='a') || _file_buffer[_point_buffer]=='’'){
            word_buffer += _file_buffer[_point_buffer];
            _point_buffer++;
        }else{
            if(_file_buffer[_point_buffer]== '.' || _file_buffer[_point_buffer]==',' || _file_buffer[_point_buffer]==';' || _file_buffer[_point_buffer]=='&' || _file_buffer[_point_buffer]=='-'){
                trigger=true;
                _special_char = _file_buffer[_point_buffer];
                _special_switch = true;
                _point_buffer++;
            }else{
                _point_buffer++;
                trigger=true;
            }
        }
    }
    return word_buffer;
}

void Markov::fillRelation(){
    std::string word;
    bool equal_switch;

    while(true){
        word = getWord();
        if(word=="-1") break;

        equal_switch=false;

        if(_prev_word=="."){
            word[0]-=32;
        }

        if(_init_switch == true){
            for(std::vector<relation>::iterator i = _relation_list.begin(); i != _relation_list.end(); ++i){
                if(i->word==_prev_word){
                    i->follow_list.push_back(word);
                }
                else{
                    if(i->word == word){
                        equal_switch = true;
                    }
                }
            }
            if(equal_switch==false){
                if(word!="."){
                    _relation_list.emplace_back(word);
                    auto i = _relation_list.back();
                }
            }
        }
        else{
            _relation_list.emplace_back(word);
            auto i = _relation_list.back();
            _init_switch=true;
        }
        _prev_word = word;
    }
}

void Markov::generateChain(int sentence_count){
    std::string word;
    int rand_index;
    while(sentence_count!=0){
        while(true){
            rand_index = rand() % _relation_list.size();
            word=_relation_list[rand_index].word;
            if(word[0]>=65 && word[0]<=90) break;
        }
        std::cout << word;
        word=_relation_list[rand_index].follow_list[rand() % _relation_list[rand_index].follow_list.size()];
        std::cout << ' ' << word;
            while(word != "."){
                for(int i=0; i != _relation_list.size(); i++){
                    if(_relation_list[i].word==word){
                        word = _relation_list[i].follow_list[rand() % _relation_list[i].follow_list.size()];
                        if(word == "." || word == ";" || word == ",") std::cout << word;
                        else std::cout << ' ' << word;
                    }
                }
            }
            sentence_count--;
            std::cout << '\n' << '\n';
    }
}

void Markov::listVector(){
    std::cout << "<" << _relation_list.size() << ">";
    for(std::vector<relation>::iterator i = _relation_list.begin(); i != _relation_list.end(); ++i){
        std::cout << ">>> " << i->word << " <<< => ";
        for(std::vector<std::string>::iterator y = i->follow_list.begin(); y != i->follow_list.end(); ++y){
            std::cout << *y << " | ";
        }
        std::cout << '\n';
    }
}

