#include <iostream>
#include <cstring> // Để sử dụng strcmp
using namespace std;

struct railroad {
    int maxCapacity;
    int passengers;
    char *id;
    railroad *next;
};

// Hàm tạo một toa tàu mới
railroad* makeNewCar(int maxCapacity, int passengers, char *id) {
    if (passengers > maxCapacity) {
        cout << "Error: Passengers cannot exceed maximum capacity.\n";
        return nullptr;
    }
    railroad *newCar = new railroad();
    newCar->maxCapacity = maxCapacity;
    newCar->passengers = passengers;
    newCar->id = new char[strlen(id) + 1];
    strcpy(newCar->id, id);
    newCar->next = nullptr;
    return newCar;
}

// Hàm thêm toa tàu vào cuối danh sách
void addNewCar(railroad *&head, int maxCapacity, int passengers, char *id) {
    railroad *newCar = makeNewCar(maxCapacity, passengers, id);
    if (!newCar) return; // Nếu không hợp lệ thì thoát

    if (head == nullptr) {
        head = newCar; // Nếu danh sách rỗng, đặt newCar làm đầu danh sách
    } else {
        railroad *tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = newCar;
    }
}

// Hàm hiển thị thông tin các toa tàu
void displayCars(railroad *head) {
    if (head == nullptr) {
        cout << "The train is empty.\n";
        return;
    }
    railroad *tmp = head;
    while (tmp != nullptr) {
        cout << "Car ID: " << tmp->id << ", Max Capacity: " << tmp->maxCapacity
             << ", Passengers: " << tmp->passengers << "\n";
        tmp = tmp->next;
    }
}

// Hàm đếm số lượng toa tàu
int getRailroadLength(railroad *head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}

// Hàm xóa các toa không có hành khách
void removeEmptyCars(railroad *&head) {
    while (head != nullptr && head->passengers == 0) {
        railroad *toDelete = head;
        head = head->next;
        delete[] toDelete->id; // Giải phóng bộ nhớ cho chuỗi id
        delete toDelete;
    }

    railroad *current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->passengers == 0) {
            railroad *toDelete = current->next;
            current->next = toDelete->next;
            delete[] toDelete->id; // Giải phóng bộ nhớ cho chuỗi id
            delete toDelete;
        } else {
            current = current->next;
        }
    }
}

int main() {
    railroad *train = nullptr; // Đoàn tàu ban đầu rỗng

    // Thêm toa tàu
    addNewCar(train, 100, 50, (char *)"Car1");
    addNewCar(train, 120, 0, (char *)"Car2");
    addNewCar(train, 80, 60, (char *)"Car3");

    cout << "Initial train status:\n";
    displayCars(train);
    cout << "Train length: " << getRailroadLength(train) << "\n";

    // Xóa các toa không có hành khách
    removeEmptyCars(train);

    cout << "\nAfter removing empty cars:\n";
    displayCars(train);
    cout << "Train length: " << getRailroadLength(train) << "\n";

    return 0;
}
