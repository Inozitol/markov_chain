#include "Markov.h"

std::string doc_name;
Markov chain(/*INPUT DOC NAME HERE*/);
int main()
{
    std::cout << "|------------------------------------------|\n";
    std::cout << "|Gandalf made simple Markov chain generator|\n";
    std::cout << "|------------------------------------------|\n";
    std::cout << '\n';

    //chain.listVector();
    chain.generateChain(/*INPUT NUMBER OF SENTECES HERE*/);
    return 0;
}
