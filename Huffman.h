//
// Created by Rafagan Abreu on 9/8/15.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include <string>
#include <queue>
#include <unordered_map>
#include <list>
#include "Node.h"

class Huffman {
private:
    auto buildAlphabet(std::string text);
    template <typename T> auto buildTree(T alphabet);
    template <typename T> auto buildDictionaryBits(T rootNode);
    template <typename T, typename U> void encode(T n, unsigned long code, std::queue<U>* codes);
    char decode(std::list<bool> mask, std::shared_ptr<Node> current);

    std::shared_ptr<Node> tree;
    std::unordered_map<char, unsigned long> dictionary;
    char overplus; //inteiro 8 bits
public:
    std::vector<bool> compress(std::string text);
    std::string uncompress(std::deque<bool> bits);
    std::unordered_map<char, unsigned long> getDictionary();
    int getOverplus();
};


#endif //HUFFMAN_HUFFMAN_H
