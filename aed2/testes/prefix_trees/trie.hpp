#ifndef TRIE_HPP
#include "node.hpp"
#include <optional>
#include <string>

template <class T> class Trie
{
  public:
    Trie();
    ~Trie();
    void set(std::string key, T value);
    std::optional<T> get(std::string);

  private:
    Node<T> *root;
    void set(std::string key, T value, Node<T> *root);
};

#endif // TRIE_HPP