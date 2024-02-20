#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int n=0;
    int mang[16] ={0};
    do
    {
        printf("Hay nhap so phan tu cua mang: ");
        scanf("%d",&n);

    }while(!((n>0)&&(n<=16)));

    printf("Khoi tao mang int array[%d] \n",n);
    printf("hay nhap cac phan tu cua mang: \n");
    for(int i=0;i<n;i++)
    {
        printf("arr[%d] = ",i);
        scanf("%d",&mang[i]);
    }
    printf("arr[] = { ");
    for(int i=0;i<n;i++)
    {
        printf("%d ",mang[i]);
    }
    printf("}\n");

    printf("Dia chi cua tung phan tu la: \n");
    for(int i=0;i<n;i++)
    {
        printf("&arr[%d] = %p\n",i,(void*)&mang[i]);
    }



    return 0;
}
