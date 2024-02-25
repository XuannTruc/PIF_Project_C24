#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct infor{
    char name[32];
    char mssv[8];
    uint8_t course_c;

};

typedef struct infor in4;

void nhap(in4 *a)
{
    printf("Nhap thong tin \n");
    gets(a->name);
    gets(a->mssv);
    scanf("%hhu", &a->course_c);
}

void xuat(in4 *a)
{

    printf("%s\n", a->name);
    printf("%s\n", a->mssv);
    printf("%d\n", a->course_c);
}


int main()
{
    in4 a;
    nhap(&a);
    xuat(&a);

    return 0;
}