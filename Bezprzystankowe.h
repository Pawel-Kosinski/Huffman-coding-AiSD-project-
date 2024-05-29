class PrefixFreeCode {
public:
    struct PFNode {
        PFNode* left;
        PFNode* right;
        char ch;
        int count;
    };

    PrefixFreeCode() : root(nullptr) {}

    ~PrefixFreeCode() {
        DFSRelease(root);
    }

    std::string ans;

    void createTree() {
        std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,?.:-";
        MakeTree(root, alphabet);
        generateCodes(root, "");
        displayCodes();
    }

    void encodeMessage(const string& message) {
        ans.clear();
        for (char c : message) {
           ans += prefixFreeCodes[c];
        }
        std::cout << ans << std::endl;
    }

    void decodeMessage() {
        PFNode* p = root;
        std::string encodedMessage;
        std::cout << "Enter the encoded message to decode: ";
        std::getline(std::cin, encodedMessage); // Wczytywanie zakodowanej wiadomo�ci
        std::cout << "Decoded message: ";

        for (char c : encodedMessage) {
            // Przemieszczanie si� w drzewie w zale�no�ci od warto�ci bitu
            if (c == '0') {
                p = p->left;
            }
            else {
                p = p->right;
            }

            // Je�li dotarli�my do li�cia, wy�wietlamy znak i wracamy do korzenia
            if (!p->left && !p->right) {
                std::cout << p->ch;
                p = root;
            }
        }

        std::cout << std::endl;
    }

private:
    PFNode* root; 
    std::unordered_map<char, std::string> prefixFreeCodes; // Mapa przechowuj�ca kody prefiksowe

    // Funkcja tworz�ca drzewo na podstawie alfabetu
    void MakeTree(PFNode*& root, const std::string& s) {
        // Tworzenie posortowanej listy znak�w
        std::vector<char> chars(s.begin(), s.end());
        sort(chars.begin(), chars.end());

        // Tworzenie w�z��w dla ka�dego znaku
        std::vector<PFNode*> nodes;
        for (char c : chars) {
            nodes.push_back(new PFNode{ nullptr, nullptr, c, 0 });
        }

        // Budowanie drzewa przez ��czenie w�z��w
        while (nodes.size() > 1) {
            std::vector<PFNode*> newNodes;
            for (size_t i = 0; i < nodes.size(); i += 2) {
                if (i + 1 < nodes.size()) {
                    PFNode* parent = new PFNode{ nodes[i], nodes[i + 1], '\0', 0 };
                    newNodes.push_back(parent);
                }
                else {
                    newNodes.push_back(nodes[i]);
                }
            }
            nodes = newNodes;
        }

        root = nodes[0]; // Korze� drzewa
    }

    // Funkcja generuj�ca kody prefiksowe na podstawie drzewa
    void generateCodes(PFNode* node, const std::string& str) {
        if (!node) return;

        // Je�li w�ze� jest li�ciem, zapisujemy kod
        if (!node->left && !node->right) {
            prefixFreeCodes[node->ch] = str;
        }

        // Rekurencyjne generowanie kod�w dla lewego i prawego potomka
        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    }

    // Funkcja wy�wietlaj�ca kody prefiksowe
    void displayCodes() {
        std::cout << "Prefix-Free Codes:" << std::endl;
        for (const auto& pair : prefixFreeCodes) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // Funkcja rekurencyjnie zwalniaj�ca pami�� drzewa
    void DFSRelease(PFNode* node) {
        if (node) {
            DFSRelease(node->left);
            DFSRelease(node->right);
            delete node;
        }
    }
};