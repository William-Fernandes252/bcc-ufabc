#include "trie.hpp"
#include <iostream>
#include <string>

int main()
{
    Trie<int> *trie = new Trie<int>();
    trie->set(std::string("a"), 1);
    auto value = trie->get(std::string("a"));
    if (value)
        std::cout << *value << std::endl;
}