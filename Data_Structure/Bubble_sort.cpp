#include<iostream>
using namespace std;

void BubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int s[10] = {8, 1, 9, 7, 2, 4, 5, 6, 10, 3};
    cout << "初始序列：";
    for (int j = 0; j < 10; j++) {
        cout << s[j] << " ";
    }
    cout << endl;

    BubbleSort(s, 10);

    cout << "排序结果：";
    for (int j = 0; j < 10; j++) {
        cout << s[j] << " ";
    }
    cout << endl;

    system("pause");
    return 0;
}