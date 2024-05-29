#ifndef TREECREATIONUTILITY_H
#define TREECREATIONUTILITY_H

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

class TreeCreationUtility {
public:
    struct Node {
        Node* left;
        Node* right;
        char key;
        int count;
        Node(char k = '\0', int c = 0) : left(nullptr), right(nullptr), key(k), count(c) {}
    };

    static Node* createPrefixTree(int n, const std::vector<std::pair<char, std::string>>& codes) {
        Node* root = new Node;
        for (const auto& pair : codes) {
            char s = pair.first;
            const std::string& b = pair.second;
            Node* p = root;
            for (char c : b) {
                if (c == '0') {
                    if (!p->left) {
                        p->left = new Node;
                    }
                    p = p->left;
                }
                else {
                    if (!p->right) {
                        p->right = new Node;
                    }
                    p = p->right;
                }
            }
            p->key = s;
        }
        return root;
    }

    static Node* createHuffmanTree(const std::string& s) {
        std::unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }

        auto compare = [](Node* left, Node* right) {
            return left->count > right->count;
        };
        std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> minHeap(compare);

        for (const auto& pair : frequency) {
            Node* newNode = new Node(pair.first, pair.second);
            minHeap.push(newNode);
        }

        while (minHeap.size() > 1) {
            Node* left = minHeap.top();
            minHeap.pop();
            Node* right = minHeap.top();
            minHeap.pop();

            Node* merged = new Node('\0', left->count + right->count);
            merged->left = left;
            merged->right = right;
            minHeap.push(merged);
        }

        return minHeap.top();
    }

    static void releaseTree(Node* node) {
        if (node) {
            releaseTree(node->left);
            releaseTree(node->right);
            delete node;
        }
    }
};
#endif
