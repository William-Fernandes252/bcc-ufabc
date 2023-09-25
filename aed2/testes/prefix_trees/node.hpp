#ifndef NODE_HPP
#include <list>
#include <optional>
#include <string>

template <class T> class Node
{
  private:
    std::string code;
    std::optional<T> value;
    Node<T> *parent = nullptr;
    std::list<Node<T> *> *children = new std::list<Node<T> *>();

  public:
    Node();
    Node(std::string code);
    Node(std::string code, T value);
    Node(std::string code, Node<T> *parent);
    Node(std::string code, T value, Node<T> *parent);
    ~Node();
    std::optional<T> getValue();
    void setValue(T value);
    std::string getCode();
    void setCode(std::string code);
    Node<T> *getParent();
    void setParent(Node<T> *parent);
    void addChild(Node<T> *child);
    Node<T> removeChild(Node<T> *child);
    std::list<Node<T> *> *getChildren();
};

#endif