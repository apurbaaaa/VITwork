#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

unsigned char compute_checksum(const unsigned char *buffer, int size) {
    unsigned int total = 0;
    for (int i = 0; i < size; ++i) {
        total += buffer[i];
        if (total > 0xFF) {
            total = (total & 0xFF) + 1;
        }
    }
    return ~((unsigned char)total);
}

int validate_checksum(const unsigned char *buffer, int size, unsigned char checksum) {
    unsigned int total = 0;
    for (int i = 0; i < size; ++i) {
        total += buffer[i];
        if (total > 0xFF) {
            total = (total & 0xFF) + 1;
        }
    }
    total += checksum;
    if (total > 0xFF) {
        total = (total & 0xFF) + 1;
    }
    return (total == 0xFF);
}

void display_binary(unsigned char byte) {
    for (int i = 7; i >= 0; --i) {
        putchar((byte & (1 << i)) ? '1' : '0');
    }
}

int main() {
    char input[BUFFER_SIZE];
    unsigned char buffer[BUFFER_SIZE / 8];
    int size = 0;

    printf("Input binary data: ");
    fgets(input, sizeof(input), stdin);

    char *segment = strtok(input, " \n");
    while (segment != NULL) {
        if (strlen(segment) == 8) {
            unsigned char byte = (unsigned char)strtol(segment, NULL, 2);
            buffer[size++] = byte;
        }
        segment = strtok(NULL, " \n");
    }

    unsigned char checksum = compute_checksum(buffer, size);

    printf("Data Segments:\n");
    for (int i = 0; i < size; ++i) {
        display_binary(buffer[i]);
        putchar('\n');
    }
    
    printf("Checksum:\n");
    display_binary(checksum);
    putchar('\n');

    unsigned char transmitted_data[size + 1];
    memcpy(transmitted_data, buffer, size);
    transmitted_data[size] = checksum;

    int valid = validate_checksum(transmitted_data, size, checksum);

    printf("Validation Result:\n");
    if (valid) {
        printf("Data verified.\n");
    } else {
        printf("Data corrupted hence error.\n");
    }

    return 0;
}
