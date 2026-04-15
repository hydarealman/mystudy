#include <iostream>
using namespace std;

// 合并函数
void merge(int* a, int low, int mid, int high) {
    int *b =  new int[high - low + 1];
    int i = low,j = mid + 1,k = 0;
    while(i <= mid && j <= high) {
        if (a[i] < a[j]) {
            b[k++] = a[i++];
        }
        else {
            b[k++] = a[j++];
        }
    }
    while(i <= mid) {
        b[k++] = a[i++];
    }

    while(j <= mid) {
        b[k++] = b[j++];
    }

    for (int i = low; i <= high; i++) {
        a[i] = b[i-low];
    }
    delete[] b;
}


// 归并排序函数
void mergeSort(int* a, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(a,low,mid);
        mergeSort(a,mid + 1,high);
        merge(a,low,mid,high);
    }
}

// 主函数
int main() {
    int a[] = {42, 15, 20, 6, 8, 38, 50, 12};
    int n = sizeof(a) / sizeof(a[0]);
    mergeSort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}