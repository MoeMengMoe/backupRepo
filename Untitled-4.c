void merge(int* nums1, int m, int* nums2, int n){
    for(int i=0;i<n;i++){
        nums1[i+m]=nums2[i];
    }
    for(int i=m+n-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(nums1[i]<nums1[i+1]){
                int temp =nums1[i];
                nums1[i]=nums1[i+1];
                nums1[i+1]=temp;

            }
        }
    }
}

void spiralPrint(int** matrix, int rows, int cols){
    int* read=calloc(rows*cols,sizeof(int));
    int direction[]={1,2,3,4};
    int status=1;
    int row_status=0,col_status=0;
    //1-> 2down 3<- 4 up
    while(1){
        if(status==1){
            int start=0;
            for(int i=0;i<cols;i++){
                if(read[row_status][i]!=1){
                printf("%d",matrix[row_status][i]);
                read[row_status][i]=1;}
                else {
                    start++;
                    if(start)break;
                    continue;
                }
            }
            status++;
        }



    }
}
int** createMatrix(int rows, int cols){
    int **matrix=(int *)malloc(rows*sizeof(int));
    for(int i=0;i<cols;i++){
        matrix[i]=malloc(cols*sizeof(int));
    }
    return matrix;
}
int** transpose(int** mat, int rows, int cols){
    int x=0,y=0;
    for(int i=0;i<rows;i++){
        for(int j=i;j<cols;j++){
            int temp=mat[x][y];
            mat[x][y]=mat[y][x];
            mat[y][x]=temp;

        }
    }
    return mat;

}
void freeMatrix(int** mat, int rows){
    for(int i=0;i<rows;i++){
        free(mat[i]);
    }
    free(mat);
}
typedef struct Node {
    int data;
    struct Node* next;
} Node;
Node* createNode(int value){
    Node node;
    Node* ptr=&node;
    ptr->data=value;
    ptr->next=NULL;


}
void insertAtHead(Node** head, int value){
    (*head)->data=value;
    (*head)->next=NULL;

}
typedef struct Student {
    char name[20];
    int score;
} Student;
void sortStudentsByScore(Student* students, int n){
    Student *ptr=students;
    for(int i=n-1;i>0;i--){
        for(int j=0;j<i;j++){
            if((*ptr).score>(*(ptr+1)).score){
                Student temp=*ptr;
                *ptr=*(ptr+1);
                *(ptr+1)=temp;

            }
            *ptr=*(students+j);
        }
        *ptr=*(students+i);

    }
}
typedef struct Point {
    double x, y;
} Point;
Point* createPoint(double x, double y){
    Point* ptr=(Point*)malloc(sizeof(Point));
    if(!(*ptr))return NULL;
    ptr->x=x;
    ptr->y=y;
}