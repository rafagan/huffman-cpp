//
// Created by Rafagan Abreu on 9/8/15.
//

#include "Huffman.h"
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <map>

using namespace std;

auto Huffman::buildAlphabet(std::string text) {
    unordered_multiset<char> uset;
    for(auto c : text)
        uset.insert(c);

    auto f = [](const unsigned long& a, const unsigned long& b) {
        return a < b;
    };

    multimap<unsigned long, shared_ptr<Node>, decltype(f)> letterCounter(f);
    unordered_set<char> skip;

    for(auto v : uset) {
        if(skip.count(v) > 0) continue;
        skip.insert(v);

        auto count = uset.count(v);
        auto node = shared_ptr<Node>(new Node(count, v));
        letterCounter.insert(pair<unsigned long, decltype(node)>(
                pair<unsigned long, decltype(node)>(count, node)
        ));
    }

    return letterCounter;
}

template <typename T>
auto Huffman::buildTree(T alphabet) {
    while(alphabet.size() > 1) {
        auto it = alphabet.begin();
        auto left = *it;
        alphabet.erase(it);

        it = alphabet.begin();
        auto right = *it;
        alphabet.erase(it);

        auto count = left.first + right.first;
        auto parent = decltype(left)(count, shared_ptr<Node>(new Node()));
        parent.second->setWeight(left.second, right.second);
        alphabet.insert(parent);
    }

    return alphabet.begin()->second;
}

template <typename T>
auto Huffman::buildDictionaryBits(T rootNode) {
    queue<pair<char, unsigned long>> codes;
    encode(rootNode, 0, &codes);

    auto dictionary = unordered_map<char, unsigned long>();
    while(!codes.empty()) {
        auto current = codes.front();
        dictionary[current.first] = current.second;
        codes.pop();
    }

    return dictionary;
}

vector<bool> Huffman::compress(string text) {
    auto rootNode = buildTree(buildAlphabet(text));
    this->dictionary = buildDictionaryBits(rootNode);
    vector<bool> result;

    for(auto c : text) {
        auto bits = dictionary[c];

        if(bits == 0)
            result.push_back(0);
        else {
            vector<bool> subset;
            while(bits != 0) {
                bool bit = static_cast<bool>(bits & 1);
                subset.push_back(bit);
                bits >>= 1;
            }
            reverse(subset.begin(),subset.end());
            result.insert(result.end(), subset.begin(), subset.end());
        }
    }
    this->tree = rootNode;
    this->overplus = char(8 - result.size() % 8);

    return result;
}

template <typename T, typename U>
void Huffman::encode(T n, unsigned long code, queue<U>* codes) {
    if(n->hasLeft())
        encode(n->getLeft(), code << 1, codes);

    if(n->hasRight())
        encode(n->getRight(), (code << 1) + 1, codes);

    if(!n->hasRight() && !n->hasLeft())
        codes->push(U(n->getLetter(), code));
}

char Huffman::decode(list<bool> mask, shared_ptr<Node> current) {
    if(current == nullptr)
        return '\0';

    if(!current->hasLeft() && !current->hasRight())
        return current->getLetter();

    if(mask.empty())
        return '\0';

    bool path = mask.front();
    mask.pop_front();
    return this->decode(mask, path ? current->getRight() : current->getLeft());
}

string Huffman::uncompress(deque<bool> bits) {
    if (this->tree == nullptr)
        throw runtime_error("You can't uncompress before compress");

    for(int i = 0; i < this->overplus; i++)
        bits.pop_back();

    string result;
    list<bool> letterMask;
    while (!bits.empty()) {
        letterMask.push_back(bits.front());

        char letter = decode(list<bool>(letterMask), tree);
        if (letter != '\0') {
            result += letter;
            letterMask.clear();
        }

        bits.pop_front();
    }

    return result;
}

unordered_map<char, unsigned long> Huffman::getDictionary() {
    return this->dictionary;
}

int Huffman::getOverplus() {
    return this->overplus;
}
