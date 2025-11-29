/*Q39: Write a program to find the product of odd digits of a number.

/*
Sample Test Cases:
Input 1:
12345
Output 1:
15 (1*3*5)

Input 2:
2468
Output 2:
1 (no odd digits, assume 1)

*/
#include <stdio.h>

int main() {
    int n, digit;
    int product = 1;  
    int Odd = 0;   

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0) {
        n = -n;  
    }

    while (n > 0) {
        digit = n % 10;  
        if (digit % 2 != 0) {  
            product =product* digit;
            Odd = 1;
        }
        n = n / 10;  
    }

    
    if (!Odd) {
        product = 1;
    }

    printf("Product of odd digits = %d\n", product);

    return 0;
}