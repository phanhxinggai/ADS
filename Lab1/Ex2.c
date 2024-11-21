#include<stdio.h>

void findMax(int *max, int a){
    if ( a > *max )
    {
        *max = a;
    }
}

int main(){
    int size;
    printf("Please enter the size of array : " );
    scanf("%d",&size);
    printf("Please enter all the number of the array : ");
    int a[size];
    for (int i = 0; i< size; i++){
        scanf("%d", &a[i]); // đọc từng ptu của mảng
    }
    
    int max = a[0];
    for ( int i = 1; i < size; i++){
        findMax(&max,a[i]);
    }
    printf("The maximum number is %d ", max);

}