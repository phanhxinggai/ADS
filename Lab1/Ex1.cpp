#include <iostream>
#include <string>
#include <algorithm> // có thể dùng thư viện  #include <bits/stdc++.h>,là thư viện chưa hầu hết các thư viện, nhưng có thể làm tăng thời gian biên dịch

using namespace std;

int main(){
    cout << " Enter the positive interger:  ";
    string s;
    cin >> s ;  //nhập string từ bàn phím
    swap(s[0],s[s.length()-1]);//swap là hàm có sẵn trong thư viện ở dong 3
    cout << " An integer afrter swapped is :" << s;
}