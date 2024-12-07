#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product{
    char *name;
    int quantity;
    int price;
    Product *next;
    Product *prev;
} Product;

typedef struct Customer{
    char *name;
    char *productName;
    int productQuantity;
    int totalPrice;
    Customer *next;
} Customer;

typedef struct queue{
    Customer *front;
    Customer *back;
    int size;
} queue;

Product *makeProduct(char *name, int quantity, int price){
    Product *newProduct = (Product *)malloc(sizeof(Product));
    newProduct->name = strdup(name);
    newProduct->quantity = quantity;
    newProduct->price = price;
    newProduct->next = newProduct->prev = NULL;

    return newProduct;
}

void addProduct(Product *&head, char *name, int quantity, int price){
    Product *newProduct = makeProduct(name, quantity, price);

    if(head == NULL){
        head = newProduct;
        return;
    }

    Product *tmp = head;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = newProduct;
    newProduct->prev = tmp;
}

void removeProduct(Product *&head, char *name){
    if(head == NULL){
        printf("List is empty.\n");
        return;
    }

    Product *tmp = head;

    if(strcmp(head->name, name) == 0){
        Product *prod_remove = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(prod_remove->name);
        free(prod_remove);
        printf("Product %s is removed.\n", name);
        return;
    }

    while(tmp->next != NULL){
        if(strcmp(tmp->next->name, name) == 0){
            break;
        }
        tmp = tmp->next;
    }

    if(tmp->next == NULL){
        printf("Product %s is not in storage.\n", name);
        return;
    }

    Product *prod_remove = tmp->next;
    tmp->next = prod_remove->next;
    if(prod_remove->next != NULL){
        prod_remove->next->prev = tmp;
        printf("Product %s is removed.\n", name);
    } 
    else{
        printf("Product %s is removed.\n", name);
    }

    free(prod_remove->name);
    free(prod_remove);
}

void displayProducts(Product *head){
    if(head == NULL){
        printf("No products in storage.\n");
        return;
    }

    printf("All product in the storage:\n");
    Product *tmp = head;
    while(tmp != NULL){
        printf("Product Name: %s, Quantity: %d, Price: %d\n", tmp->name, tmp->quantity, tmp->price);
        tmp = tmp->next;
    }
}

int getProductQuantity(Product *head, char *name){
    Product *tmp = head;

    while(tmp != NULL){
        if(strcmp(tmp->name, name) == 0){
            return tmp->quantity;
        }
        tmp = tmp->next;
    }
    return 0;
}

void editProductInfo(Product *&head, char *name, int quantity, int price){
    //The product is already in the stock, add more quantity
    if(getProductQuantity(head, name) != 0){
        Product *tmp = head;
        while(tmp != NULL){
            if(strcmp(tmp->name, name) == 0){
                tmp->quantity += quantity;
                tmp->price = price;
                break;
            }
            tmp = tmp->next;
        }
    }
    else{
        //Add new product if it is not in the stock
        addProduct(head, name, quantity, price);
    }
}

Customer *makeCustomer(char *name){
    Customer *newCustomer = (Customer *)malloc(sizeof(Customer));
    newCustomer->name = strdup(name);
    newCustomer->productName = NULL;
    newCustomer->productQuantity = 0;
    newCustomer->totalPrice = 0;
    newCustomer->next = NULL;

    return newCustomer;
}

void init(queue *customerQueue){
    customerQueue->front = customerQueue->back = NULL;
    customerQueue->size = 0;
}

void enqueue(queue *customerQueue, Customer *newCustomer) {
    if(customerQueue->back == NULL){
        customerQueue->front = customerQueue->back = newCustomer;
    } 
    else{
        customerQueue->back->next = newCustomer;
        customerQueue->back = newCustomer;
    }
    customerQueue->size++;
    printf("Customer %s entered the queue.\n", newCustomer->name);
}

void dequeue(queue *customerQueue){
    if(customerQueue->front == NULL){
        printf("The queue is empty.\n");
        return;
    }

    Customer *tmp = customerQueue->front;
    customerQueue->front = customerQueue->front->next;

    if(customerQueue->front == NULL){
        customerQueue->back = NULL;
    }

    free(tmp->name);
    free(tmp->productName);
    free(tmp);
    customerQueue->size--;
}

void buyProduct(queue *customerQueue, Product *&head){
    if(customerQueue->front == NULL){
        printf("No customers in the queue.\n");
        return;
    }

    Customer *currentCustomer = customerQueue->front;

    while(1){
        printf("Customer %s is buying products.\n", currentCustomer->name);

        printf("Enter product name: ");
        char productName[50];
        gets(productName);

        Product *productSold = head;
        while(productSold != NULL){
            if(strcmp(productSold->name, productName) == 0){
                break;
            }
            productSold = productSold->next;
        }

        if(productSold == NULL){
            printf("Product %s is not in storage.\n", productName);
            printf("1. Continue shopping\n2. Stop buying and leave\nChoose an option: ");
            int option;
            scanf("%d", &option);
            getchar();

            if(option == 2){
                printf("Customer %s left the queue without buying anything.\n", currentCustomer->name);
                dequeue(customerQueue);
                return;
            }
            continue;
        }

        printf("Enter quantity: ");
        int quantity;
        scanf("%d", &quantity);
        getchar();

        if(productSold->quantity < quantity){
            printf("Not enough products in storage.\n");
            continue;
        } 
        else{
            productSold->quantity -= quantity;
            if(currentCustomer->productName == NULL){
                currentCustomer->productName = strdup(productName);
            } 
            else{
                char *newProductName = (char *)malloc(strlen(currentCustomer->productName) + strlen(productName) + 3);
                sprintf(newProductName, "%s, %s", currentCustomer->productName, productName);
                free(currentCustomer->productName);
                currentCustomer->productName = newProductName;
            }
            currentCustomer->productQuantity += quantity;
            currentCustomer->totalPrice += quantity * productSold->price;

            printf("Product %s purchased. Quantity: %d, Total Price: %d\n", productName, quantity, currentCustomer->totalPrice);
            displayProducts(head);

            if(productSold->quantity == 0){
                removeProduct(head, productName);
            }
        }

        printf("1. Continue shopping\n2. Stop buying and leave\nChoose an option: ");
        int option;
        scanf("%d", &option);
        getchar();

        if(option == 2){
            printf("%s left the queue\n", currentCustomer->name);
            dequeue(customerQueue);
            // printf("Total Price: %d\n", currentCustomer->totalPrice);
            return;
        }
    }
}

void printMainMenu(){
    printf("1. Product Management\n");
    printf("2. Customer Management\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

void printProductMenu(){
    printf("1. Add product to storage\n");
    printf("2. Remove product from storage\n");
    printf("3. Edit product in storage\n");
    printf("4. Display all products\n");
    printf("5. Back to main menu\n");
    printf("Choose an option: ");
}

void printCustomerMenu(){
    printf("1. Enter customer into queue\n");
    printf("2. Buy products\n");
    printf("3. Back to main menu\n");
    printf("Choose an option: ");
}

int main(){
    Product *head = NULL;
    queue customerQueue;
    init(&customerQueue);

    int choice, productChoice, customerChoice;
    char name[50];
    char productName[50];
    int quantity, price;

    while(1){
        printMainMenu();
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                while(1){
                    printProductMenu();
                    scanf("%d", &productChoice);
                    getchar();

                    switch(productChoice){
                        case 1:
                            printf("Enter product name: ");
                            gets(productName);
                            printf("Enter quantity: ");
                            scanf("%d", &quantity);
                            printf("Enter price: ");
                            scanf("%d", &price);
                            getchar();
                            addProduct(head, productName, quantity, price);
                            break;
                        case 2:
                            printf("Enter product name to remove: ");
                            gets(productName);
                            removeProduct(head, productName);
                            break;
                        case 3:
                            printf("Enter product name to edit (or add more): ");
                            gets(productName);
                            printf("Enter quantity you want to change (or new quantity): ");
                            scanf("%d", &quantity);
                            printf("Enter new price: ");
                            scanf("%d", &price);
                            getchar();
                            editProductInfo(head, productName, quantity, price);
                            break;
                        case 4:
                            displayProducts(head);
                            break;
                        case 5:
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                    }
                    if(productChoice == 5) break;
                }
                break;

            case 2:
                while(1){
                    printCustomerMenu();
                    scanf("%d", &customerChoice);
                    getchar();

                    switch(customerChoice){
                        case 1:
                            printf("Enter customer name: ");
                            gets(name);
                            enqueue(&customerQueue, makeCustomer(name));
                            displayProducts(head);
                            printf("-------------------------------------\n");
                            break;
                        case 2:
                            buyProduct(&customerQueue, head);
                            break;
                        case 3:
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                    }
                    if(customerChoice == 3) break;
                }
                break;

            case 3:
                printf("Exiting the program...\nGood bye!!!");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
