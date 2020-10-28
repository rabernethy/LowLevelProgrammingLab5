/*
    Safe integer calculator - warns if an overflow or
    underflow error occurs.

    Menu
    Negation
    Safe unsigned ops
    Safe signed ops
    Arithmetic without + - * / % ++ or --

    Code the functions below and uncomment the code in main()
    when completed.

    Code the functions in order as they appear.  Subsequent
    functions depend on previous functions.  You cannot use
    any math operators (+ - * / % ++ or --) except simple
    assignment (=).  However, you may use relational and
    logical operators.

    The _add() function should only use bitwise operators.  All
    other functions can call functions necessary to complete the
    required operation.  I added some hints above functions.
*/

#include <stdio.h>

// Prototypes
int _add(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int neg(int a);
int mul(int a, int b);
int div(int a, int b);
int mod(int a, int b);
int pow(int a, int b);
int convert(char *input);
void menu();

// Main
int main(int argc, char *argv[]){

    int res = 0;        // Cumulative result - running total
    int n = 0;          // For number conversion from input string
    char input[50];     // Input string
    input[0] = '\0';    // Put null in operator char so loop works

    // Write code here to test your functions
    // Uncomment code below when done

    // Loop until quit is selected
    while(input[0] != 'q' && input[0] != 'Q'){
        // Show menu choices
        menu();
        // Print prompt with running total
        printf("\nres = %d > ", res);
        // Get input string
        gets(input);
        // Clear screen
        system("cls");

        // Switch on operator char input[0]
        switch (input[0]){
            case '+':
                res = add(res, convert(input));
                break;
            case '-':
                res = sub(res, convert(input));
                break;
            case '*':
                res = mul(res, convert(input));
                break;
            case '/':
                res = div(res, convert(input));
                break;
            case '%':
                res = mod(res, convert(input));
                break;
            case '~':
                res = neg(res);
                break;
            case '^':
                res = pow(res, convert(input));
                break;
            case 'c':
            case 'C':
                res = 0;
                break;
            case 'q':
            case 'Q':
                printf("Good-bye!\n");
                break;
            default:
                printf("Enter a valid operator and operand\n");

        }

    }


    return 0;
}


// Show menu choices
void menu(){
    printf("\nSafe Integer Calculator\n");
    printf("+ x to add\n");
    printf("- x to subtract\n");
    printf("* x to multiply\n");
    printf("/ x to divide\n");
    printf("%% x to modulus\n");
    printf("~ x to negate\n");
    printf("^ x to raise by power x\n");
    printf("c x to clear result\n");
    printf("q x to quit\n");
    return;
}

// Add operation using only bitwise operators
int _add(int a, int b){
    while(b != 0) {
        int c = a & b; /* carry bit */
        a = a ^ b; /* add stuff together */
        b = c << 1; /* shift everything over */
    }
    return a;
}

// Safe add operation
int add(int a, int b){
    int res = _add(a,b);
    int neg_over = a < 0 && b < 0 && res > 0;
    int pos_over = a > 0 && b > 0 && res < 0;
    if(neg_over || pos_over) 
        printf("Overflow error with %d and %d.\n", a, b);
    return res;
}

// Negate opperation
int neg(int a){
    return add(~a, 1);
}

// Subtract opperation
int sub(int a, int b){
    return add(a, neg(b));
}

// Define safe multiply by calling safe add b times
int mul(int a, int b){
    int res = 0;
    int sign = 1;
    if(a < 0) {
        a = neg(a);
        sign = neg(sign);
    }
    if(b < 0) {
        b = neg(b);
        sign = neg(sign);
    }
    int min = (a < b) ? a : b;
    int max = (a > b) ? a : b;
    while(min != 0) {
        res = add(res,max);
        min = sub(min,1);
    }
    return (sign < 0) ? neg(res) : res;
}

// Divide opperation
int div(int a, int b){
    int cnt = 0;
    int sign = 1;
    if(a < 0) {
        a = neg(a);
        sign = neg(sign);
    }
    if(b < 0) {
        b = neg(b);
        sign = neg(sign);
    }
    while(a > 0) {
        a = sub(a,b);
        cnt = add(cnt,1);
    }
    cnt = (sign < 0) ? neg(cnt) : cnt;
    return cnt;
}

// Modulus opperation
int mod(int a, int b) {
    if(a < 0)
        a = neg(a);
    if(b < 0)
        b = neg(b);
    while(a >= b)
        a = sub(a,b);
    return a;
}

// pow function
int pow(int n, int exp){
    int res = 0;
    if(exp == 0)
        return 1;
    while(exp != 0) {
        res = mul(res,n);
        exp = sub(exp,1);
    }
    return res;
}

// Extract the integer from the input string and convert to int
int convert(char *input){
    int res = 0;
    int sign = (input[2] == '-') ? -1 : 1;
    int i = (sign > 0) ? 2 : 3;
    int j = 0;
    char buffer[32];
    /* Read input into a buffer array. */
    while(input[i] != '\0') {
        if(input[i] >= '0' && input[i] <= '9') {
            buffer[j] = input[i];
            j = add(j,1);
        }
        i = add(i,1);
    } 
    buffer[j] = '\0';
    i = 0;
    while(i < j) {
        res = add(mul(res,10), sub(buffer[i], 48));
        i = add(i,1);
    }
    printf("%d\n", res);
    return (sign < 0) ? neg(res) : res;
}

