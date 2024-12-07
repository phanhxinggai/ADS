#include <bits/stdc++.h>
using namespace std;

struct complexNumber{
    int real,img;

void enter (){
    cin >>real >> img;
}

void print(){
    cout << real <<"+" <<img <<"i"<<endl;
}
}   ;

complexNumber add(complexNumber a, complexNumber b){
    complexNumber res;
    res.real = a.real + b.real;
    res.img  = a.img  + b.img;
    return res;
}
complexNumber mul(complexNumber a, complexNumber b){
    complexNumber res;
    res.real = a.real*b.real - a.img*b.img;
    res.img  = a.real*b.img + a.img*b.real;
    return res;
}

int main(){
    complexNumber a, b;
    cout << "Enter the components of the first complex number : ";
    a.enter();// gọi a trước hàm enter vì enter là hàm thành viên của hàm complexNumber
    cout << "Enter the components of the second complex number : ";
    b.enter();
    complexNumber sum = add(a,b);
    complexNumber product = mul(a,b);
    cout << "Sum of a and b is : ";
    sum.print();
    cout << "Product of a and b is :";
    product.print();
return 0;
}