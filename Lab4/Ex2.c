/*
    AUTHOR: Do Nguyen Gia Nhu
    ID: 22BA13248
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Website{
    char *url;
    char *title;
    struct Website *next;
} Website;

typedef struct Stack{
    int size;
    Website *top;
} Stack;

Website *makeWebsite(char *url, char *title){
    Website *newWebsite = (Website *)malloc(sizeof(Website));
    newWebsite->url = strdup(url);
    newWebsite->title = strdup(title);
    newWebsite->next = NULL;

    return newWebsite;
}

Stack *makeStack(){
    Stack *newStack = (Stack *)malloc(sizeof(Stack));
    newStack->size = 0;
    newStack->top = NULL;

    return newStack;
}

int isEmpty(Stack *st){
    return st->size == 0;
}

void push(Stack *st, Website *web){
    web->next = st->top;
    st->top = web;
    st->size++;
}

Website *pop(Stack *st){
    if(isEmpty(st))
        return NULL;
    Website *tmp = st->top;
    st->top = st->top->next;
    tmp->next = NULL;
    st->size--;

    return tmp;
}

void clearStack(Stack *st){
    while(!isEmpty(st)){
        Website *web = pop(st);
        free(web->url);
        free(web->title);
        free(web);
    }
}

void visitWebsite(Stack *backwardStack, Stack *forwardStack, Website **current, char *url, char *title){
    if(*current != NULL){
        push(backwardStack, *current);
    }
    clearStack(forwardStack);
    *current = makeWebsite(url, title);
    printf("Visited: %s - %s\n", url, title);
}

void goBackward(Stack *backwardStack, Stack *forwardStack, Website **current){
    if(isEmpty(backwardStack)){
        printf("No previous website to go back to.\n");
        return;
    }
    push(forwardStack, *current);
    *current = pop(backwardStack);
    printf("Went back to: %s - %s\n", (*current)->url, (*current)->title);
}

void goForward(Stack *backwardStack, Stack *forwardStack, Website **current){
    if(isEmpty(forwardStack)){
        printf("No forward website to go to.\n");
        return;
    }
    push(backwardStack, *current);
    *current = pop(forwardStack);
    printf("Went forward to: %s - %s\n", (*current)->url, (*current)->title);
}

void displayStacks(Stack *backwardStack, Stack *forwardStack, Website *current){
    Website *temp;
    printf("\n===== Browser History =====\n");

    printf("\nBackward Stack:\n");
    temp = backwardStack->top;
    while(temp != NULL){
        printf("%s - %s\n", temp->url, temp->title);
        temp = temp->next;
    }

    if(current != NULL){
        printf("\nCurrent Website:\n");
        printf("%s - %s (You are here)\n", current->url, current->title);
    } 
	else{
        printf("\nCurrent Website:\nNone\n");
    }

    printf("\nForward Stack:\n");
    temp = forwardStack->top;
    while(temp != NULL){
        printf("%s - %s\n", temp->url, temp->title);
        temp = temp->next;
    }
    printf("===========================\n");
}

int main(){
    Stack *backwardStack = makeStack();
    Stack *forwardStack = makeStack();
    Website *current = NULL;

    visitWebsite(backwardStack, forwardStack, &current, "https://example.com", "Example Home");
	visitWebsite(backwardStack, forwardStack, &current, "https://example1.com", "Example Website 1");
    visitWebsite(backwardStack, forwardStack, &current, "https://example2.com", "Example Website 2");
    visitWebsite(backwardStack, forwardStack, &current, "https://example3.com", "Example Website 3");
    visitWebsite(backwardStack, forwardStack, &current, "https://example4.com", "Example Website 4");
    visitWebsite(backwardStack, forwardStack, &current, "https://example5.com", "Example Website 5");
    visitWebsite(backwardStack, forwardStack, &current, "https://example6.com", "Example Website 6");
    visitWebsite(backwardStack, forwardStack, &current, "https://example7.com", "Example Website 7");
    visitWebsite(backwardStack, forwardStack, &current, "https://example8.com", "Example Website 8");

    int choice;
    char url[100];
    char title[100];

    while(1){
        displayStacks(backwardStack, forwardStack, current);

        printf("Menu:\n");
        printf("1. Visit a new website\n");
        printf("2. Go backward\n");
        printf("3. Go forward\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(choice){
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                printf("Enter Title: ");
                scanf("%s", title);
                visitWebsite(backwardStack, forwardStack, &current, url, title);
                break;
            case 2:
                goBackward(backwardStack, forwardStack, &current);
                break;
            case 3:
                goForward(backwardStack, forwardStack, &current);
                break;
            case 4:
                printf("Exiting...\nGood bye !!!\n");
                break;
            default:
                printf("Invalid choice. Please try again!!!\n");
                break;
        }
		if(choice == 4) break;
    }

    if(current != NULL){
        free(current->url);
        free(current->title);
        free(current);
    }
    clearStack(backwardStack);
    clearStack(forwardStack);
    free(backwardStack);
    free(forwardStack);
}