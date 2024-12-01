#include <stdio.h>
#include <string.h>
//#include <conio.h>  // Uncomment this if using DOS-based systems with conio.h
void main() {
    char icode[10][30], str[20], opr[10];
    int i = 0;

    // Accepting intermediate code input from the user
    printf("\nEnter the set of intermediate code (terminated by exit):\n");
    do {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0); // Continue reading until 'exit' is encountered

    // Start target code generation
    printf("\nTarget Code Generation");
    printf("\n************************");

    // Reset i for target code generation
    i = 0;

    // Generate target code based on intermediate code
    do {
        strcpy(str, icode[i]);

        // Handle the operator in the intermediate code
        switch (str[3]) {
            case '+': strcpy(opr, "ADD "); break;
            case '-': strcpy(opr, "SUB "); break;
            case '*': strcpy(opr, "MUL "); break;
            case '/': strcpy(opr, "DIV "); break;
            default: 
                strcpy(opr, "UNKNOWN ");
                break;
        }

        // Printing assembly instructions based on the intermediate code
        printf("\n\tMOV %c, R%d", str[2], i); // Move operand into a register
        printf("\n\t%s%c, R%d", opr, str[4], i); // Perform the operation
        printf("\n\tMOV R%d, %c", i, str[0]); // Move the result to the left

    } while (strcmp(icode[++i], "exit") != 0); // Loop until 'exit' is encountered

    // getch();  // Uncomment this if using DOS-based systems to wait for user input
}
