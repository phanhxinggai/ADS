#include<bits/stdc++.h>
using namespace std;

//Pseudocode
// Funtion isSphenic(n):                             Complexity is :
//     Set cnt = 0
//     for i <- 2 to sqrt(n) do:                          O(log(n)) 
//         if n % i == 0: 
//                 increase cnt by 1
//                 divide n by i      
//                 if n %i== 1: return False
//         endif
//     endfor
//     if n>1: increase cnt by 1
// End function if n==3;
// funtion main()
// display "enter the number"
// read n from keyboard
// Call isSphenic if n is Sphenic number
//                   display n is a sphenic number
//                else 
//                    display n is not a sphenic number
//                endif   
//end funtion                                 


bool isSphenic(int n){
    int cnt = 0;
    for (int i = 2 ; i < sqrt(n); i++ ){ 
        if(n % i == 0 ){
            cnt++;
            n/=i; 
            }
            if (n % i == 0) return false;
        }
    if(n > 1) cnt++;

    return cnt==3;
}

int main(){
    cout << "Enter the number: ";
    int n; cin >> n;
    if(isSphenic(n)){
        cout << n << " is a sephenic number" << endl;
    }
    else{
        cout << n << " is not a sphenic number " <<endl;
    }
}