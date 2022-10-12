//
// Created by Rafagan Abreu on 9/8/15.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <memory>
#include <iostream>

class Node {
friend std::ostream& operator<<(std::ostream& out, Node& other);

private:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::weak_ptr<Node> parent;
    unsigned long weight;
    char letter = '\0';
public:
    explicit Node();
    explicit Node(unsigned long count);
    explicit Node(unsigned long count, char letter);

    std::shared_ptr<Node> getLeft() const;
    void setLeft(std::shared_ptr<Node> left);

    std::shared_ptr<Node> getRight() const;
    void setRight(std::shared_ptr<Node> right);

    std::weak_ptr<Node> getParent() const;
    void setParent(std::weak_ptr<Node> parent);

    unsigned long getCount() const;
    void setWeight(unsigned long count);
    void setWeight(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

    char getLetter() const;
    void setLetter(char letter);

    bool hasLeft();
    bool hasRight();

    virtual ~Node();
};


#endif //HUFFMAN_NODE_H
