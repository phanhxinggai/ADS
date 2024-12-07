#include <bits/stdc++.h>1  5 6
using namespace std;

void findMax( int *max, int a){
    if(a>*max) *max=a;
}
int main(){
    cout << "Enter the size of array:  ";
    int n ; 
    cin >> n;
    cout << "Enter the elements of array : ";
    int a[n];
    for(int &x : a) cin >> x;// &x: tham chiếu đến từng phần tử trong mảng a và cin để nhập

    int max_ele = INT_MIN;// khởi tạo hằng số INT_MIN đê đảm bảo max đc gán ban đầu là gtrị nhỏ nhất có thể có trong int// hoặc có thể set max_ele =0
    for(int i = 0 ; i < n; i++){
        findMax(&max_ele, a[i]);
    }
    cout << "Max elemnt is : " << max_ele<<endl;
}
