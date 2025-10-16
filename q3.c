#include<stdio.h>
void merge_sort_array(int array1[],int array2[],int array[],int n1,int n2){
    
    for(int i=0;i<n1;i++){
        array[i]=array1[i];
    }
    for(int i=0;i<=n2;i++){
        array[i+n1]=array2[i];
    }
    for (int i = 0; i < n1+n2 - 1; i++) {
        for (int j = 0; j < n1+n2 - 1 - i; j++) {
            if (array[j] < array[j + 1]) {  // 降序：前面 < 后面，就交换
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    // for(int i=0;i<n1+n2;i++){
        
    //     if(array[i]<array[i+1]){int temp=array[i];array[i]=array[i+1];array[i+1]=temp;}
    // }

}



int main(){
    int n1,n2;
    printf("Input the number of elements in the first array:");
    scanf("%d",&n1);
    int array1[n1];
    printf("Input the %d elements in the array:\n",n1);
    for(int i=0;i<n1;i++){
        printf("element[%d]:",i);
        scanf("%d",&array1[i]);
    }
    printf("Input the number of elements in the second array:");
    scanf("%d",&n2);
    int array2[n2];
    printf("Input the %d elements in the array:\n",n2);
    for(int i=0;i<n2;i++){
        printf("Element[%d]:",i);
        scanf("%d",&array2[i]);
    }
    int array[n1+n2+1];
    merge_sort_array(array1,array2,array,n1,n2);


    printf("The merged array in descending order is:\n");
    for(int i=0;i<n1+n2;i++){
        printf("%d\t",array[i]);
    }
    
}