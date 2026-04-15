#include<iostream>
#include<algorithm>
using namespace std;

void select_sort(int* a, int n) {
    for (int i = 0; i < n; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            if (a[index] > a[j]) {
                index = j;
            }
        }
        swap(a[i],a[index]);
    }
}

int main() {
    int a[10] = {5, 7, 9, 6, 3, 1, 4, 8};
    select_sort(a, 8);
    for (int i = 0; i < 8; i++) {
        cout << a[i] << " ";
    }
    return 0;
}