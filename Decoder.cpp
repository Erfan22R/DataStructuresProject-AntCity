#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class CircularQueue {
private:
    vector<string> queue;
    int front, rear, size, capacity;
public:
    CircularQueue(int cap) : capacity(cap), size(0), front(0), rear(-1) {
        queue.resize(cap);
    }

    bool isFull() { return size == capacity; }
    bool isEmpty() { return size == 0; }

    void enqueue(const string& data) {
        if (!isFull()) {
            rear = (rear + 1) % capacity;
            queue[rear] = data;
            size++;
        }
    }

    string dequeue() {
        if (!isEmpty()) {
            string data = queue[front];
            front = (front + 1) % capacity;
            size--;
            return data;
        }
        return "";
    }
};

struct HuffmanNode {
    char ch;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode() : ch('\0'), left(nullptr), right(nullptr) {}
};


HuffmanNode* buildHuffmanTreeFromTable(const unordered_map<char, string>& huffmanTable) {
    HuffmanNode* root = new HuffmanNode();
    for (const auto& pair : huffmanTable) {
        HuffmanNode* node = root;
        for (char bit : pair.second) {
            if (bit == '0') {
                if (!node->left) node->left = new HuffmanNode();
                node = node->left;
            } else {
                if (!node->right) node->right = new HuffmanNode();
                node = node->right;
            }
        }
        node->ch = pair.first;
    }
    return root;
}

string decodeHuffman(HuffmanNode* root, const string& encodedStr) {
    string decoded;
    HuffmanNode* node = root;
    for (char bit : encodedStr) {
        node = (bit == '0') ? node->left : node->right;
        if (!node->left && !node->right) {
            decoded += node->ch;
            node = root;
        }
    }
    return decoded;
}

int main() {
    ifstream orderFile("order.txt");
    if (!orderFile){
        cout<<"Error: Unable to open order.txt!"<<endl;
        return 1;
    }
    string line;

    while (getline(orderFile, line)) {
        if (line == "Huffman Codes:") break;
    }
    
    unordered_map<char, string> huffmanTable;
    char ch;
    string code;
    while (getline(orderFile,line)) {
        istringstream lineStream(line);
        lineStream>>ch>>code;
        if (ch == 'E') break;
        huffmanTable[ch] = code;
    }
    orderFile.clear();
    orderFile.seekg(0,ios::beg);

    HuffmanNode* root = buildHuffmanTreeFromTable(huffmanTable);

    while (getline(orderFile, line)) {
        if (line =="Encoded Data:") break;
    }

    CircularQueue cq(1000); 
    string encodedStr;
    while (orderFile >> encodedStr) {
        cq.enqueue(encodedStr);
    }

    while (!cq.isEmpty()) {
        cout << decodeHuffman(root, cq.dequeue()) << endl;
    }

    return 0;
}