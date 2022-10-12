//
// Created by Rafagan Abreu on 9/8/15.
//

#include "Node.h"

using namespace std;

Node::Node() : weight(0) {

}

Node::Node(unsigned long count) : weight(count) { }

Node::Node(unsigned long count, char letter) : weight(count), letter(letter) { }

shared_ptr<Node> Node::getLeft() const {
    return left;
}

void Node::setLeft(shared_ptr<Node> left) {
    this->left = left;
}

shared_ptr<Node> Node::getRight() const {
    return this->right;
}

void Node::setRight(shared_ptr<Node> right) {
    this->right = right;
}

weak_ptr<Node> Node::getParent() const {
    return this->parent;
}

void Node::setParent(weak_ptr<Node> parent) {
    this->parent = parent;
}

unsigned long Node::getCount() const {
    return this->weight;
}

void Node::setWeight(unsigned long count) {
    this->weight = count;
}

char Node::getLetter() const {
    return letter;
}

void Node::setLetter(char letter) {
    this->letter = letter;
}

bool Node::hasLeft() {
    return getLeft() != nullptr;
}

bool Node::hasRight() {
    return getRight() != nullptr;
}

void Node::setWeight(shared_ptr<Node> left, shared_ptr<Node> right) {
    setLeft(left);
    setRight(right);
    setWeight(left->getCount() + right->getCount());
}

Node::~Node() {
    left = nullptr;
    right = nullptr;
}

ostream &operator<<(ostream &out, Node &other) {
    out << "L: " << other.letter << ", N: " << other.weight << endl;

    if(other.left != nullptr) {
        out << "* Entering left: \n" << *other.left << endl;
        out << "L: " << other.letter << ", N: " << other.weight << endl;
    }


    if(other.right != nullptr) {
        out << "* Entering right: \n" << *other.right << endl;
    }

    return out;
}
