#include <stdio.h>
#include <stdint.h> 

int main() {
    int n;

    //Nhap so phan tu tu ban phim, neu khong thoa dieu kien thi nhap lai
    do {
        printf("Nhap so phan tu n: ");
        scanf("%d", &n);
    } while (n < 0 || n > 16);

    // Dinh nghia lai mang voi cac kieu du lieu
    uint8_t arr8[n];
    uint16_t arr16[n];
    uint32_t arr32[n];
    uint64_t arr64[n];

    // In ra dung lượng của từng phần tử trong mảng với kiểu dữ liệu uint8_t
    printf("\nDung luong cua tung phan tu voi kieu uint8_t: %zu byte\n", sizeof(uint8_t));
    
    // In ra dung lượng của từng phần tử trong mảng với kiểu dữ liệu uint16_t
    printf("Dung luong cua tung phan tu voi kieu uint16_t: %zu byte\n", sizeof(uint16_t));
    
    // In ra dung lượng của từng phần tử trong mảng với kiểu dữ liệu uint32_t
    printf("Dung luong cua tung phan tu voi kieu uint32_t: %zu byte\n", sizeof(uint32_t));
    
    // In ra dung lượng của từng phần tử trong mảng với kiểu dữ liệu uint64_t
    printf("Dung luong cua tung phan tu voi kieu uint64_t: %zu byte\n", sizeof(uint64_t));

    return 0;
}

