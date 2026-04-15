#include <stdio.h>

void A() {
    while(1) {
        printf("A\n");
        co_yield();
    }
}

void B() {
    while(1){
        printf("B\n");
        co_yield();
    }
}

int main() {
    A();
    B();
}