#include<iostream>//static array  
using namespace std;
#define Capacity 1000
struct unboundedInt{
    
    int size;
    int digit[Capacity]; // Mảng lưu các chữ số của số, có kích thước tối đa MAX_DIGIT.
};
unboundedInt *init(unboundedInt *num, int sign){
    num = new unboundedInt();//Cấp phát bộ nhớ động cho đối tượng num
    num->digit[0]=sign;// vị trí 0 trong dãy digit sẽ là dấu
    for (int i=1 ;i<Capacity; i++){
        num->digit[i]=-1;//các phần tử của mảng digit được khởi tạo là -1 để biểu thị rằng vị trí đó chưa được sử dụng
    }
    num->size = 0;//khởi tạo kích thước ban đầu
    return num;
}
void addDigit(unboundedInt *num,int digit,int pos){ 
    if( pos <= 0 || pos > num->size+1){// check valid position( không ở vị tri =0 của sign và không thêm vào bên trái số)
        cout << "Invalid Position, cannot ADD \n ";// không ở ví trị mà quá kích thước cho phép
        return;
    }

    for(int i = num->size; i >= pos; i--){//num->size là vị trí cuối cùng
        num->digit[i+1] = num->digit[i]; // các chữ số được dịch sang phải để tạo chỗ trống mới để add
    }
     
    num->digit[pos]=digit;
    num->size++;
    
}
void removeDigit(unboundedInt *num , int pos){
    if( pos <= 0 || pos > num->size){
        cout << "Invalid Position, cannot REMOVE \n ";
        return;
    }
    for(int i = pos; i < num->size; i++){
        num->digit[i] = num->digit[i+1]; 
    }
    num->digit[num->size]= -1; // -1 để đánh dấu các vị trí không hợp lệ hoặc chưa dùng tới
    num-> size--; // sau khi xóa thì giảm size
}
int sumofDigit(unboundedInt *num){
    int sum=0;
    for(int i = 1; i<= num->size; i++){
        sum+=num->digit[i];
    }
    return sum;
}
void display(unboundedInt *num){
    if (num->digit[0]==-1){
    cout <<"-";
    }

    for( int i = 1; i<= num->size ; i++){
        if(num->digit[i] != -1)
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


