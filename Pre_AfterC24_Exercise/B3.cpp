#include <stdio.h>

int main() {
    int n;
    int array[16]; 

    // Nhap so phan tu tu ban phim, neu khong thoa dieu kien thi nhap lai
    do {
        printf("Nhap so phan tu n: ");
        scanf("%d", &n);
    } while (n <= 5);

    // Nhap gia tri cho tung phan tu tu ban phim
    printf("Nhap gia tri cho tung phan tu:\n");
    for (int i = 0; i < n; ++i) {
        printf("arr[%d]: ", i);
        scanf("%d", &array[i]);
    }

    // Tìm phan tu max va min
    int max = array[0];
    int min = array[0];
    for (int i = 1; i < n; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }

    // Xuat ket qua ra man hinh
    printf("Phan tu lon nhat trong mang: %d\n", max);
    printf("Phan tu nho nhat trong mang: %d\n", min);

    return 0;
}