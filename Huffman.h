class HuffmanCode {
public:
    // Struktura wêz³a drzewa Huffmana
    struct HTNode {
        HTNode* next;  
        HTNode* left;  
        HTNode* right; 
        char ch;       
        int count;     
    };

   
    HuffmanCode() : root(nullptr) {}

    
    ~HuffmanCode() {
        DFSRelease(root);
    }

    string code; // zmienna przechowuj¹ca zakodowan¹ wiadomoœæ

    // Funkcja tworz¹ca drzewo Huffmana na podstawie wejœciowego ci¹gu znaków
    void createTree(const string& s) {
        MakeList(root, s);  // Tworzenie listy wêz³ów na podstawie czêstotliwoœci znaków
        MakeTree(root);     // Budowanie drzewa na podstawie listy wêz³ów
        generateCodes(root, "");  // Generowanie kodów Huffmana na podstawie drzewa
        displayCodes();     // Wyœwietlanie kodów Huffmana
    }

    // Funkcja koduj¹ca wiadomoœæ
    void encodeMessage(const string& s) {
        code.clear(); 
        for (char c : s) {
            code += huffmanCodes[c]; 
        }
        cout << code << endl; 
    }

private:
    HTNode* root; 
    unordered_map<char, string> huffmanCodes; // Mapa przechowuj¹ca kody Huffmana

    // Funkcja tworz¹ca listê wêz³ów na podstawie czêstotliwoœci znaków
    void MakeList(HTNode*& root, const string& s) {
        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++; // Zliczanie czêstotliwoœci ka¿dego znaku
        }

        auto compare = [](HTNode* left, HTNode* right) {
            return left->count > right->count;
        };
        priority_queue<HTNode*, vector<HTNode*>, decltype(compare)> minHeap(compare); // Ten fragment kodu definiuje sposób porównywania wêz³ów i tworzy kopiec minimalny, gdzie element o najmniejszej czêstotliwoœci jest na szczycie

        for (const auto& pair : frequency) {
            HTNode* newNode = new HTNode{ nullptr, nullptr, nullptr, pair.first, pair.second };
            minHeap.push(newNode); // Tworzenie wêz³ów dla ka¿dego znaku i dodawanie ich do kopca
        }

        while (minHeap.size() > 1) {
            HTNode* left = minHeap.top();
            minHeap.pop();
            HTNode* right = minHeap.top();
            minHeap.pop();

            HTNode* merged = new HTNode{ nullptr, left, right, '\0', left->count + right->count };
            minHeap.push(merged); // £¹czenie dwóch najmniejszych wêz³ów w jeden
        }

        root = minHeap.top(); 
    }

    // Funkcja buduj¹ca drzewo Huffmana
    void MakeTree(HTNode*& root) {
        HTNode* p, * r, * v1, * v2;

        while (true) {
            v1 = root;
            v2 = v1->next;

            // Jeœli nie ma drugiego wêz³a, oznacza to, ¿e drzewo zosta³o zbudowane
            if (!v2) break;

            root = v2->next;

            // Tworzenie nowego wêz³a p, który jest rodzicem v1 i v2
            p = new HTNode;
            p->left = v1;
            p->right = v2;
            p->count = v1->count + v2->count;

            // Szukamy w³aœciwego miejsca w liœcie, aby wstawiæ nowy wêze³ p i wstawiamy
            if (!root || (p->count <= root->count)) {
                p->next = root;
                root = p;
                continue;
            }
            
            r = root;
            while (r->next && (p->count > r->next->count)) {
                r = r->next;
            }

            p->next = r->next;
            r->next = p;
        }
    }


    // Funkcja generuj¹ca kody Huffmana na podstawie drzewa
    void generateCodes(HTNode* node, const string& str) {
        if (!node) return;

        // Jeœli wêze³ jest liœciem, zapisujemy kod
        if (!node->left && !node->right) {
            huffmanCodes[node->ch] = str;
        }

        // Rekurencyjne generowanie kodów dla lewego i prawego potomka
        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    }

    // Funkcja wyœwietlaj¹ca kody Huffmana
    void displayCodes() {
        cout << "Huffman Codes:" << endl;
        for (const auto& pair : huffmanCodes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    // Funkcja rekurencyjnie zwalniaj¹ca pamiêæ drzewa
    void DFSRelease(HTNode* v) {
        if (v) {
            DFSRelease(v->left);
            DFSRelease(v->right);
            delete v;
        }
    }
};