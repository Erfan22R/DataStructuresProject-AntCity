#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>

using namespace std;

bool KMP(const string& text, const string& pattern) {
    int m = pattern.size(), n = text.size();
    vector<int> lps(m, 0);

    for (int i = 1, length = 0; i < m;) {
        if (pattern[i] == pattern[length]) {
            lps[i++] = ++length;
        } else if (length) {
            length = lps[length - 1];
        } else {
            lps[i++] = 0;
        }
    }

    return text.substr(0, pattern.size()) == pattern;
}

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

HuffmanNode* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left, merged->right = right;
        pq.push(merged);
    }
    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanTable) {
    if (!root) return;
    if (root->ch != '\0') huffmanTable[root->ch] = code;
    generateHuffmanCodes(root->left, code + "0", huffmanTable);
    generateHuffmanCodes(root->right, code + "1", huffmanTable);
}

int main() {
    vector<string> queens;
    string ant;

    ifstream parentFile("parents.txt");
    int nQueen, nWorker;
    parentFile >> nQueen >> nWorker;
    queens.resize(nQueen);

    for (int i = 0; i < nQueen; i++) parentFile >> queens[i];

    vector<string> validAnts;
        cout<<"Enter ants(22 for End):\n";
    while (cin >> ant && ant != "22") {
        for (const auto& queen : queens) {
            if (KMP(queen, ant)) {
                if(ant!=queen){    
                    validAnts.push_back(ant);
                    break;
                }
            }
        }
    }

    unordered_map<char, int> freqMap;
    for (const auto& ant : validAnts) {
        for (char ch : ant) freqMap[ch]++;
    }

    HuffmanNode* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> huffmanTable;
    generateHuffmanCodes(root, "", huffmanTable);

    ofstream orderFile("order.txt");
    orderFile<<"Huffman Codes:\n";
    for (const auto& pair : huffmanTable) {
        orderFile<<pair.first<<" "<<pair.second<<endl;
    }
    orderFile<<"Encoded Data:"<<endl;
    for (const auto& ant : validAnts) {
        for (char ch : ant) orderFile << huffmanTable[ch];
        orderFile << " ";
    }
    orderFile.close();

    return 0;
}
