void reverseArray(int *arr, int size){
    int temp;
    for(int i=0;i<size/2;i++){
        temp=*(arr+size-i-1);
        *(arr+size-i-1)=*(arr+i);
        *(arr+i)=temp;
        
        
    }
}

    void findMinMax(int *arr, int size, int *max, int *min){
        
        for(int i=0; i<size;i++){//remember to initialise pointer
            if(*(arr+i)>*max)*max=*(arr+i);
            if(*(arr+i)<*min)*min=*(arr+i);
        }
    }

    void rowColSum(int matrix[3][3], int rowSum[3], int colSum[3]){
        for(int i=0;i<3;i++){
            rowSum[0] +=matrix[0][i];
            rowSum[1] +=matrix[1][i];
            rowSum[2] +=matrix[2][i];
        
            colSum[0]+=matrix[i][0];
            colSum[1]+=matrix[i][1];
            colSum[2]+=matrix[i][2];
        }

    }


int myStrlen(char *str){
    int len=0;
    for(int i=0;;i++){
        if(*(str+i)=='\0')len=i+1;break;
    }
    return len;
}

int myStrcmp(char *str1, char *str2){
    for(int i=0;;i++){
        if(*(str1+i)==*(str2+i))continue;
        if(*(str1+i)<*(str2+i))return -1;
        if(*(str1+i)>   *(str2+i))return 1;
    }
    return 0;
}