//Q22: Write a program to find profit or loss percentage given cost price and selling price.

/*
Sample Test Cases:
Input 1:
1000 1200
Output 1:
Profit 20%

Input 2:
1000 800
Output 2:
Loss 20%

Input 3:
1000 1000
Output 3:
No Profit No Loss

*/
#include <stdio.h>

int main() {
    double cp, sp;
    
    printf("Enter cost price and selling price: ");
    scanf("%lf %lf", &cp, &sp);

    if (sp > cp) {
        double profit_percent = ((sp - cp) / cp) * 100;
        printf("Profit %d%%\n", (int)profit_percent);
    } else if (cp > sp) {
        double loss_percent = ((cp - sp) / cp) * 100;
        printf("Loss %d%%\n", (int)loss_percent);
    } else {
        printf("No Profit No Loss\n");
    }

    return 0;
}

