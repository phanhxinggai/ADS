#include<iostream>
using namespace std;

typedef struct unboundedInt{
    int size;
    int sign;
    int *digit;
}unboundedInt;

unboundedInt *init(unboundedInt *num, int sign){
    num = (unboundedInt*)malloc(sizeof(unboundedInt));
    num->size=0;
    num->digit=NULL;
    num->sign=sign;
    return num;
}
void addDigit(unboundedInt*num, int digit, int pos){
    if(pos<=0 || pos > num->size+1){
        cout << "Invalid possition cannot ADD, try again";
        return;
    }
    num->digit=(int*)realloc(num->digit,num->size *sizeof(int));
    num->size++;
    for (int i = num->size ; i >= pos; i--){
        num->digit[i+1]=num->digit[i];
    }
    num->digit[pos]=digit;

}
void removeDigit(unboundedInt*num,int pos){
    if(pos<=0 || pos > num->size+1){
        cout << "Invalid possition cannot REMOVE, try again";
        return;
    }
    for(int i=pos; i<num->size;i++){
        num->digit[i]=num->digit[i+1];
    }
    num->digit=(int*)realloc(num->digit,num->size *sizeof(int));
    num->size--;
}
int sumofDigit(unboundedInt *num){
    int sum=0;
    for(int i=1 ; i<=num->size; i++){
        sum+=num->digit[i];
    }
    return sum;
}
void display(unboundedInt*num){
    if(num->digit[0]==-1)
    cout << "-";
    for (int i=1 ; i<=num->size;i++){
        if (num->digit[0]!=-1)
        cout << num->digit[i];
    }
    cout << endl;
}

int main(){
    
    unboundedInt *num = init(num,1);
    addDigit(num, 1, 1);
    addDigit(num, 3, 1);
    addDigit(num, 2, 2);
    addDigit(num, 4, 3);
    cout << "Size: " << num->size << endl;
    cout << "The number is: ";
    display(num);

    removeDigit(num, 2);
    cout << "Size after remove: " << num->size << endl;
    cout << "The number is: ";
    display(num);

    cout << "Sum of digits: " << sumofDigit(num) << endl;

    delete num;
    return 0;
}
