#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int n=0;
    int array[16];

    //Nhap so phan tu tu ban phim, neu khong thoa dieu kien thi nhap lai
    do
    {
        printf("Nhap so phan tu n: ");
        scanf("%d",&n);

    } while (n < 0 || n > 16);

    //Nhap gia tri cho tung phan tu tu ban phim
    printf("Khoi tao mang int arr[%d] \n",n);
    printf("Nhap gia tri tung phan tu: \n");
    for (int i=0; i<n; i++)
    {
        printf("arr[%d] = ",i);
        scanf("%d",&array[i]);
    }
    printf("arr[] = { ");
    for(int i=0;i<n;i++)
    {
        printf("%d ",array[i]);
    }
    printf("}\n");

    printf("Dia chi cua tung phan tu la: \n");
    for(int i=0;i<n;i++)
    {
        printf("&arr[%d] = %p\n",i,(void*)&array[i]);
    }



    return 0;
}