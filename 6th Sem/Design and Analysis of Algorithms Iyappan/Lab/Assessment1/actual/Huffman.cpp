#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

vector<HuffmanNode*> createLeaves(char data[], int frequency[], int size) {
    vector<HuffmanNode*> nodes;
    for (int i = 0; i < size; i++) {
        nodes.push_back(new HuffmanNode(data[i], frequency[i]));
    }
    return nodes;
}

void swap(HuffmanNode*& a, HuffmanNode*& b) {
    HuffmanNode* temp = a;
    a = b;
    b = temp;
}

void heapify(vector<HuffmanNode*>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l]->freq > arr[largest]->freq)
        largest = l;
    if (r < n && arr[r]->freq > arr[largest]->freq)
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<HuffmanNode*>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

HuffmanNode* buildTree(vector<HuffmanNode*>& nodes) {
    int size = nodes.size();
    while (size > 1) {
        heapSort(nodes, size);

        HuffmanNode* left = nodes[size - 1];
        HuffmanNode* right = nodes[size - 2];
        HuffmanNode* combined = new HuffmanNode('=', left->freq + right->freq);

        combined->left = left;
        combined->right = right;

        nodes[size - 2] = combined;
        size--;
    }
    return nodes[0];
}

void encode(HuffmanNode* root, string code) {
    if (!root) return;
    if (root->data != '=') 
        cout << root->data << ": " << code << endl;
    encode(root->left, code + "0");
    encode(root->right, code + "1");
}

char decode(HuffmanNode* root, string& encoded, int& index) {
    if (!root->left && !root->right)
        return root->data;
    if (encoded[index] == '0') {
        index++;
        return decode(root->left, encoded, index);
    } else {
        index++;
        return decode(root->right, encoded, index);
    }
}

string decodeString(HuffmanNode* root, string& encoded) {
    string result = "";
    int index = 0;
    while (index < encoded.length()) {
        result += decode(root, encoded, index);
    }
    return result;
}

int main() {
    char chars[] = {'c', 'd', 'g', 'u', 'm', 'a'};
    int frequencies[] = {34, 9, 35, 2, 2, 100};
    int size = sizeof(frequencies) / sizeof(int);

    vector<HuffmanNode*> leaves = createLeaves(chars, frequencies, size);
    HuffmanNode* root = buildTree(leaves);

    cout << "Huffman Codes:" << endl;
    encode(root, "");

    string encodedMessage = "0101101101001";
    string decodedMessage = decodeString(root, encodedMessage);

    cout << "\nDecoded Message: " << decodedMessage << endl;
    return 0;
}
