#include<bits/std++.h>
using namespace std;

bool itPrime(int n){
    if (n < 1) return false;
    for(int n = 2;i < sqrt(n); i++ ){
        if( n % i == 0) return false;
    }
    return true;
}
bool isSphenic(int n){
    int cnt = 0;
    for( int i=2; i<n;i++ ){
        if(n % i==0 && itPrime(n)){
            cnt++;
            n/=i;
        }
        if(n%i==0) return false;
    }
    if (n>2)
}