#include "node.hpp"

template <class T> Node<T>::Node() : Node<T>("")
{
}

template <class T>
Node<T>::Node(std::string code, T value, Node<T> *parent) : code(code), value(value), parent(parent){};

template <class T> Node<T>::Node(std::string code, T value) : code(code), value(value){};

template <class T> Node<T>::~Node()
{
    for (auto child : *children)
    {
        delete child;
    }
    delete children;

    auto *parent = this->getParent();
    for (auto child : *parent->getChildren())
    {
        if (child == this)
        {
            parent->children->remove(this);
            break;
        }
    }
};

template <class T> std::optional<T> Node<T>::getValue()
{
    return value;
};

template <class T> void Node<T>::setValue(T value)
{
    this->value = value;
}

template <class T> std::string Node<T>::getCode()
{
    return code;
}

template <class T> Node<T> *Node<T>::getParent()
{
    return parent;
}

template <class T> void Node<T>::setParent(Node<T> *parent)
{
    this->parent = parent;
}

template <class T> void Node<T>::addChild(Node<T> *child)
{
    child->setParent(this);
    children->push_back(child);
}

template <class T> Node<T> Node<T>::removeChild(Node<T> *child)
{
    return children->remove(child);
}

template <class T> std::list<Node<T> *> *Node<T>::getChildren()
{
    return children;
}