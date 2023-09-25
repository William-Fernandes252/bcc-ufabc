#include "trie.hpp"
#include "node.hpp"

template <class T> Trie<T>::Trie() : root(new Node<T>());

template <class T> Trie<T>::~Trie()
{
    delete root;
}

template <class T> void Trie<T>::set(std::string key, T value, Node<T> *root)
{
    auto aux = root;

    for (auto child : aux->getChildren())
    {
        if (child->getCode() == key[0])
        {
            return set(key.substr(1), value, child);
        }
    }

    auto leaf = new Node<T>(key[0]);
    aux->addChild(leaf);
    if (key.size() == 1)
    {
        leaf->setValue(value);
    }
    else
    {
        set(key.substr(1), value, leaf);
    }
}

template <class T> void Trie<T>::set(std::string key, T value)
{
    return set(key, value, root);
}

template <class T> std::optional<T> Trie<T>::get(std::string key)
{
    auto aux = root;
    for (auto child : aux->getChildren())
    {
        if (child->getCode() == key[0])
        {
            return search(key.substr(1));
        }
    }

    if (key.size() == 1 && key[0] == aux->getCode())
    {
        return aux->getValue();
    }

    return false;
}
