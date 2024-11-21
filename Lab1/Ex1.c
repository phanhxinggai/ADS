#include<stdio.h>
#include<string.h>

//pseudocode
//Input: A positive integer
//Output : A integer after swapping the first and the last digit
//Process:
//BEGIN
//      Get num(char array)
//      Set n <- length of num #determine the length of the character array num and store it in the variable n
//      Swap (num[0],num[n-1])
//      print num
//      END
 void swappedNumber(char num[], int n){    // n là giá trị của length
    char temp = num[0];
    num[0] = num[n-1];
    num[n-1]=temp;
 }
 int main(){
    printf("Please enter the number : ");
    char num[100];
    scanf("%s",&num);
    int length = strlen(num);
    swappedNumber(num,length);
    printf("Number after swapped is : %s ", num);
    return 0;
}
