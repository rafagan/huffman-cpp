//
// Created by Rafagan Abreu on 10/14/15.
//

#ifndef HUFFMAN_UTILS_H
#define HUFFMAN_UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string generateStringFromBits(vector<bool> bits) {
    string result;
    for(bool bit : bits) result += bit ? "1" : "0";
    return result;
}

string readStringFromFile(string fileName) {
    ifstream myReadFile;
    myReadFile.open(fileName);
    stringstream output;

    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            string buffer;
            myReadFile >> buffer;
            output << buffer;
        }
    }

    myReadFile.close();
    return output.str();
}

auto readBitsFromFile(string fileName) {
    ifstream myReadFile;
    myReadFile.open(fileName);
    deque<bool> output;

    string stringRead;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof())
            myReadFile >> stringRead;

        for(char c : stringRead) {
            if(c != myReadFile.eof()) {
                bitset<8> byte = bitset<8>(static_cast<unsigned long long int>(c));
                cout << bitset<8>(c);
                for(int i = 0; i < 8; i++)
                    output.push_back(byte[7 - i]);
            }
        }
    }

    cout << endl;

    myReadFile.close();
    return output;
}

void saveCompressedFile(vector<bool> bits) {
    ofstream file;
    file.open("huffman.txt", std::ios::binary);

    int count = 0;
    bitset<8> toAppend;
    string result;
    for(bool bit : bits) {
        ++count;
        toAppend[0] = bit;
        if(count == 8) {
            char c = char(toAppend.to_ulong());
            result += c;
            count = 0;
            cout << bitset<8>(static_cast<unsigned long long int>(c));
            toAppend = 0;
        } else {
            toAppend <<= 1;
        }
    }

    if(count > 0) {
        toAppend <<= (8 - count) - 1;
        char c = char(toAppend.to_ulong());
        result += c;
        cout << bitset<8>(static_cast<unsigned long long int>(c));
    }

    cout << endl;
    file << result;
    file.close();
}

#endif //HUFFMAN_UTILS_H