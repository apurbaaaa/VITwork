#include <iostream>
#include <string>

using namespace std;

string generateKey(string text, string key) {
    int textLength = text.size();
    int keyLength = key.size();

    for (int i = 0; key.size() < textLength; i++) {
        key.push_back(key[i % keyLength]);
    }
    return key;
}

string toUpperCase(string str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
    return str;
}

string encryptText(string text, string key) {
    string cipherText;
    for (size_t i = 0; i < text.size(); i++) {
        char encryptedChar = (text[i] + key[i] - 2 * 'A') % 26 + 'A';
        cipherText.push_back(encryptedChar);
    }
    return cipherText;
}

string decryptText(string cipherText, string key) {
    string originalText;
    for (size_t i = 0; i < cipherText.size(); i++) {
        char decryptedChar = (cipherText[i] - key[i] + 26) % 26 + 'A';
        originalText.push_back(decryptedChar);
    }
    return originalText;
}

int main() {
    string text, keyword;
    cout << "Enter the text: ";
    cin >> text;
    cout << "Enter the keyword: ";
    cin >> keyword;

    text = toUpperCase(text);
    keyword = toUpperCase(keyword);

    string key = generateKey(text, keyword);
    cout << "Generated Key: " << key << endl;

    string cipherText = encryptText(text, key);
    cout << "Encrypted Text: " << cipherText << endl;

    string originalText = decryptText(cipherText, key);
    cout << "Decrypted Text: " << originalText << endl;

    return 0;
}
