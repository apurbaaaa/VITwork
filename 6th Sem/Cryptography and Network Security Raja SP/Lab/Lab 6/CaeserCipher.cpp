#include <iostream>
#include <cmath>

using namespace std;
string encrypt(string text, int s){
 string result = "";
 for (int i = 0; i < text.length(); i++){
 if (isupper(text[i])){
 result += char(int(text[i] + s - 65) % 26 + 65);
 }
 else {
 result += char(int(text[i] + s - 97) % 26 + 97);
 }
 }

 return result;
}
string decrypt(string text, int s){
 string result = "";
 for (int i = 0; i < text.length(); i++){
 if (isupper(text[i])){
 result += char(int(text[i] - s - 65 + 26) % 26 + 65);
 }
 else {
 result += char(int(text[i] - s - 97 + 26) % 26 + 97);
 }
 }

 return result;
}
int main()
{
 string text;
 int s;
 cin>>text;
 cin>>s;
 cout<<"Text: "<<text<<"\n";
 cout<<"Shift: "<<s<<"\n";
 string encrypted_text = encrypt(text, s);
 cout<<"Cipher text: "<<encrypted_text<<"\n";
 cout<<"Decrypted text: "<<decrypt(encrypted_text, s);
 return 0;
}