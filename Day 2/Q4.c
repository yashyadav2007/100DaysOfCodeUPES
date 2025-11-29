//Q4: Write a program to calculate the area and circumference of a circle given its radius.

/*
Sample Test Cases:
Input 1:
7
Output 1:
Area=153.94, Circumference=43.96

Input 2:
3
Output 2:
Area=28.27, Circumference=18.85

*/
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    double radius, area, circumference;

    printf("Enter the radius of your circle: ");
    scanf("%lf", &radius);

    area = M_PI * radius * radius;
    circumference = 2 * M_PI * radius;

    printf("\nfor a circle with a radius of %.2f:\n", radius);
    printf(" -> The Area is %.2f\n", area);
    printf(" -> The Circumference is %.2f\n", circumference);

    return 0;
}
