#include <iostream>
#include "Huffman.h"
#include "utils.h"

using namespace std;

int main() {
    Huffman h = Huffman();

    string textRead = readStringFromFile("example.txt");
    cout << "\nArquivo lido: \n" << textRead << "\n" << endl;

    vector<bool> bits = h.compress(textRead);
    cout << "Arquivo comprimido: \n" << generateStringFromBits(bits) << "\n" << endl;
    cout << "Salvando bits no arquivo: " << endl;
    saveCompressedFile(bits);

    cout << "\nDicionario gerado: " << endl;
    for(auto v : h.getDictionary())
        cout << "(" << v.first << "," << bitset<4>(v.second) << ")" << endl;
    cout << endl;

    cout << "Total de bits excedentes: " << h.getOverplus() << endl;

    cout << "\nLendo bits do arquivo: " << endl;
    deque<bool> bitsRead = readBitsFromFile("huffman.txt");
    cout << "\nDescomprimindo arquivo: " << endl;
    string result = h.uncompress(bitsRead);
    cout << result << endl;

    return 0;
}