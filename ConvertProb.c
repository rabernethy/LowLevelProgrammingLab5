/*

    Number converter

    Menu
    Convert between integer, binary, octal and hexadecimal

    This program should accept numeric values in hexadecimal,
    decimal, octal and binary formats as:

        Hex 0x0 to 0xFFFFFFFF
        Dec 0 to 4294967295
        Oct o0 to o37777777777
        Bin b0 to b11111111111111111111111111111111

    After a value is input the code in main will interpret the
    data types above an process the conversion to an unsigned
    int.  The unsigned int will be used to convert the input to
    strings containing hexadecimal, octal and binary strings.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int input_to_decimal(char *input);
unsigned int bin_to_uint(char *input);
unsigned int oct_to_uint(char *input);
unsigned int hex_to_uint(char *input);
unsigned int dec_to_uint(char *input);
void uint_to_hex(unsigned int n, char *output);
void uint_to_oct(unsigned int n, char *output);
void uint_to_bin(unsigned int n, char *output);


int error = 0;


int main(){

    char input[50];
    unsigned int n;
    char output[50];



    // Write code here to test your functions
    // Uncomment code below when done

    printf("Enter a binary, octal, decimal or hexadecimal number\n");
    printf("convert > ");
    gets(input);

    // Detect input data type
    // Hexadecimal
    if(input[0] == '0' && input[1] == 'x'){
        n = hex_to_uint(input);
    }
    // Decimal
    else if(input[0] >= '0' && input[0] <= '9'){
        n = dec_to_uint(input);
    }
    // Octal
    else if(input[0] == 'o'){
        n = oct_to_uint(input);
    }
    // Binary
    else if(input[0] == 'b'){
        n = bin_to_uint(input);
    }
    // Unknown
    else{
        printf("ERROR: Unknown data type: %s\n", input);
    }

    // Print results
    printf("The decimal value of %s is %u\n", input, n);
    uint_to_hex(n, output);
    printf("The hexadecimal value of %s is %s\n", input, output);
    uint_to_oct(n, output);
    printf("The octal value of %s is %s\n", input, output);
    uint_to_bin(n, output);
    printf("The binary value of %s is %s\n", input, output);


    return 0;
}

// Convert a hexadecimal char array to uint
unsigned int hex_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    unsigned int mult = 1;
    int i;
    // Loop through value part of input string
    for( i = strlen(input) - 1; i > 1; i--) {
        // If between 0 and 9 add 0 to 9 to res with multiplier
        if(input[i] >= '0' && input[i] <= '9') {
            res += ((input[i] - '0') * mult); 
        }
        // If between A and F add 10 to 15 to res with multiplier
        else if( input[i] >= 65 && input[i] <= 70) {
            res += ((( input[i] - '0') - 55) * mult); 
        }
        // Error - exit
        else {
            printf("Error in hex_to_uint(). Exiting.\n");
            exit(0);
        }
        // Advance multiplier to next position value
        mult *= 16;
    }
    return res;
}

// Convert a unsigned integer char array to uint
unsigned int dec_to_uint(char *input){
    
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    unsigned int mult = 1;

    int i;
    // Loop through value part of input string
    for( i = strlen(input) - 1; i >= 0; i--) {
        // If between 0 and 9 add 0 to 9 to res with multiplier
        if(input[i] >= '0' && input[i] <= '9') {
            res += ((input[i] - '0') * mult); 
        }
    
        // Error - exit
        else {
            printf("Error in hex_to_uint(). Exiting.\n");
            exit(0);
        }
        
        // Advance multiplier to next position value
        mult *= 10;
    }
    return res;

}

// Convert a octal char array to uint
unsigned int oct_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    unsigned int mult = 1;
    int i;

    for( i = strlen(input) - 1; i > 0; i--) {
        // If between 0 and 7:
        if( input[i] >= '0' && input[i] <= '7') {
            res += ((input[i] - '0') * mult);
        }
        else {
            printf("Error in oct_to_uint. Exiting.\n");
            exit(0);
        }

        mult *= 8;
    } 
    return res;
}

// Convert a binary char array to unsigned int
unsigned int bin_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    unsigned int mult = 1;

    int i;

    for( i = strlen(input) - 1; i > 0; i--) {
        // If between 0 and 1:
        if ( input[i] >= '0' && input[i] <= '1') {
            res += ((input[i] - '0') * mult);
        }
        // Error - Exit
        else {
            printf("Error in bin_to_uint(). Exiting.\n");
            exit(0);
        }
        mult *= 2;
    }
    return res;
}


// Convert a unsigned integer char array to hexadecimal
void uint_to_hex(unsigned int n, char *output){
    // Declare a uint for remainder

    unsigned int rem;
    // Declare an int for division

    
    // Declare a char array buffer
    char buffer[55];

    // Use a loop to generate a hex string - string will be reverse
    int i = 0;
    while (n > 16) {
        
        buffer[i++] = n % 16;
        n /= 16;
    }
    
    // Get last hex char
    buffer[i++] = n + '0';
    // Put null at end of buffer
    buffer[i] = '\0';
    // Copy 0x to output string
    strcpy("0x", output);
    // Copy chars from buffer in reverse order to output string
    for( i = 0; i < strlen(buffer); i++) 
        output[i+2] = buffer[strlen(buffer) - i - 1];
    output[i] = '\0';

}

// Convert a unsigned integer char array to octal
void uint_to_oct(unsigned int n, char *output){
// Declare a uint for remainder
    unsigned int rem;
    // Declare an int for division
    int div;
    // Declare a char array buffer
    char buffer[20];
    // Use a loop to generate a hex string - string will be reverse
    int i = 0;
    while (n > 7) {
        buffer[i++] = n % 8 + '0';
        n /= 8;
    }
    
    // Get last hex char
    buffer[i++] = n + '0';
    // Put null at end of buffer
    buffer[i] = '\0';
    // Copy 0x to output string
    strcpy("o", output);
    // Copy chars from buffer in reverse order to output string
    for( i = 0; i < strlen(buffer); i++) 
        output[i+1] = buffer[strlen(buffer) - i - 1];
    output[i] = '\0';
}

// Convert a unsigned integer char array to binary
void uint_to_bin(unsigned int n, char *output){
    unsigned int rem = n;
    // Declare an int for division
    unsigned int div = 2;
    // Declare a char array buffer
    char buffer[20];
    // Use a loop to generate a bin string - string will be reverse
    int i = 0;
    while (n > 1) {
        buffer[i++] = rem % div + '0';
        rem /= div;
    }
    
    // Get last bin char
    buffer[i++] = rem + '0';
    // Put null at end of buffer
    buffer[i] = '\0';
    // Copy b to output string
    strcpy("b", output);
    // Copy chars from buffer in reverse order to output string
    for( i = 0; i < strlen(buffer); i++) 
        output[i] = buffer[strlen(buffer) - i - 1];
    output[i] = '\0';
}

