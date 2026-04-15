#include <iostream>
using namespace std;

void InsertionSort(int *a, int len) {
    for (int j = 1; j < len; j++) {
        int key = a[j];
        int i = j - 1;
        while(i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}

int main() {
    int a[] = {5, 2, 4, 6, 1, 3};
    int len = sizeof(a) / sizeof(a[0]);
    InsertionSort(a, len);
    for (int i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}