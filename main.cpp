#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;
#include "Bezprzystankowe.h"
#include "Huffman.h"

int main() {
    char choice;
    std::cout << "Wybierz opcje (k dla kodowania i porownania dwoch algorytmow, z dla odszyfrowania kodu za pomoca algorytmu bezprzystankowego: ";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 'k') {
        HuffmanCode hc;
        std::string input;
        PrefixFreeCode pfc;
        std::cout << "Podaj wiadomosc do zakodowania: ";
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::toupper); // zawsze wiadomosc jest cala z duzych liter
        pfc.createTree();
        pfc.encodeMessage(input);    
        hc.createTree(input);
        hc.encodeMessage(input);

        float l1 = pfc.ans.length();
        float l2 = hc.code.length();
        std::cout << "Dlugosc kodu bezprzystankowego: " << l1 << std::endl;
        std::cout << "Dlugosc kodu Huffmana: " << l2 << endl;
        std::cout << "Roznica pomiedzy nimi: " << l1 << " - " << l2 << " = " << l1 - l2 << std::endl;
        float comp = l2 / l1 * 100;
        std::cout << "Wspolczynnik kompresji: " << comp << "%" << std::endl;
    }

    else if (choice == 'z') {
        PrefixFreeCode pfc;
        pfc.createTree();
        pfc.decodeMessage();

    }

    else {
        std::cout << "Zly wybor." << std::endl;
    }

    return 0;
}
