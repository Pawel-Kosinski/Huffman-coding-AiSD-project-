class HuffmanCode {
public:
    // Struktura w�z�a drzewa Huffmana
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

    string code; // zmienna przechowuj�ca zakodowan� wiadomo��

    // Funkcja tworz�ca drzewo Huffmana na podstawie wej�ciowego ci�gu znak�w
    void createTree(const string& s) {
        MakeList(root, s);  // Tworzenie listy w�z��w na podstawie cz�stotliwo�ci znak�w
        MakeTree(root);     // Budowanie drzewa na podstawie listy w�z��w
        generateCodes(root, "");  // Generowanie kod�w Huffmana na podstawie drzewa
        displayCodes();     // Wy�wietlanie kod�w Huffmana
    }

    // Funkcja koduj�ca wiadomo��
    void encodeMessage(const string& s) {
        code.clear(); 
        for (char c : s) {
            code += huffmanCodes[c]; 
        }
        cout << code << endl; 
    }

private:
    HTNode* root; 
    unordered_map<char, string> huffmanCodes; // Mapa przechowuj�ca kody Huffmana

    // Funkcja tworz�ca list� w�z��w na podstawie cz�stotliwo�ci znak�w
    void MakeList(HTNode*& root, const string& s) {
        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++; // Zliczanie cz�stotliwo�ci ka�dego znaku
        }

        auto compare = [](HTNode* left, HTNode* right) {
            return left->count > right->count;
        };
        priority_queue<HTNode*, vector<HTNode*>, decltype(compare)> minHeap(compare); // Ten fragment kodu definiuje spos�b por�wnywania w�z��w i tworzy kopiec minimalny, gdzie element o najmniejszej cz�stotliwo�ci jest na szczycie

        for (const auto& pair : frequency) {
            HTNode* newNode = new HTNode{ nullptr, nullptr, nullptr, pair.first, pair.second };
            minHeap.push(newNode); // Tworzenie w�z��w dla ka�dego znaku i dodawanie ich do kopca
        }

        while (minHeap.size() > 1) {
            HTNode* left = minHeap.top();
            minHeap.pop();
            HTNode* right = minHeap.top();
            minHeap.pop();

            HTNode* merged = new HTNode{ nullptr, left, right, '\0', left->count + right->count };
            minHeap.push(merged); // ��czenie dw�ch najmniejszych w�z��w w jeden
        }

        root = minHeap.top(); 
    }

    // Funkcja buduj�ca drzewo Huffmana
    void MakeTree(HTNode*& root) {
        HTNode* p, * r, * v1, * v2;

        while (true) {
            v1 = root;
            v2 = v1->next;

            // Je�li nie ma drugiego w�z�a, oznacza to, �e drzewo zosta�o zbudowane
            if (!v2) break;

            root = v2->next;

            // Tworzenie nowego w�z�a p, kt�ry jest rodzicem v1 i v2
            p = new HTNode;
            p->left = v1;
            p->right = v2;
            p->count = v1->count + v2->count;

            // Szukamy w�a�ciwego miejsca w li�cie, aby wstawi� nowy w�ze� p i wstawiamy
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


    // Funkcja generuj�ca kody Huffmana na podstawie drzewa
    void generateCodes(HTNode* node, const string& str) {
        if (!node) return;

        // Je�li w�ze� jest li�ciem, zapisujemy kod
        if (!node->left && !node->right) {
            huffmanCodes[node->ch] = str;
        }

        // Rekurencyjne generowanie kod�w dla lewego i prawego potomka
        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    }

    // Funkcja wy�wietlaj�ca kody Huffmana
    void displayCodes() {
        cout << "Huffman Codes:" << endl;
        for (const auto& pair : huffmanCodes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    // Funkcja rekurencyjnie zwalniaj�ca pami�� drzewa
    void DFSRelease(HTNode* v) {
        if (v) {
            DFSRelease(v->left);
            DFSRelease(v->right);
            delete v;
        }
    }
};