#include <iostream>
#include <cctype>   // For toupper
#include <cstring>  // For standard string operations

// Function to calculate the length of a string
int string_length(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to copy one string into another
void string_copy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Null-terminate the destination string
}

// Function to convert a string to uppercase
void string_uppercase(char* str) {
    while (*str != '\0') {
        *str = toupper(*str); // Convert character to uppercase
        str++;
    }
}

// Function to concatenate two strings
void string_concatenate(char* dest, const char* src) {
    while (*dest != '\0') {
        dest++; // Move to the end of the destination string
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Null-terminate the result
}

int main() {
    char str1[100], str2[100], str3[100];

    std::cout << "Enter the first string: ";
    std::cin.getline(str1, 100);

    std::cout << "Enter the second string: ";
    std::cin.getline(str2, 100);

    // Length of the first string
    std::cout << "Length of '" << str1 << "': " << string_length(str1) << std::endl;

    // Copy first string to a new string
    string_copy(str3, str1);
    std::cout << "Copied string: " << str3 << std::endl;

    // Convert first string to uppercase
    string_uppercase(str1);
    std::cout << "Uppercase string: " << str1 << std::endl;

    // Concatenate the two strings
    string_concatenate(str1, str2);
    std::cout << "Concatenated string: " << str1 << std::endl;

    return 0;
}
// g++ -o stringManipulation stringManipulation.cpp && ./stringManipulation