#include <stdio.h>

int main() {
    int n;
    float sum = 0;

    // Yêu cầu người dùng nhập số phần tử và kiểm tra điều kiện
    do {
        printf("Nhap so phan tu (n > 5): ");
        scanf("%d", &n);
    } while (n <= 5);

    // Khai báo mảng với số phần tử là n
    int array[n];

    // Nhập giá trị cho từng phần tử của mảng
    printf("Nhap gia tri cho tung phan tu:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &array[i]);
    }

    // Tính tổng các phần tử
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }

    // Tính giá trị trung bình
    float average = sum / n;

    // In ra giá trị trung bình với 3 chữ số phần thập phân
    printf("Gia tri trung binh cua cac phan tu: %.3f\n", average);

    return 0;
}
