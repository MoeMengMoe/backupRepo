# include <stdio.h>
struct regt {
    int left;
    int right;
    int bottom;
    int top;
};
//you can only define one struct and use them for more times
typedef struct regt r;//remember use "struct name " to define
// struct regt2{
//     int left ;
//     int right;
//     int bottom;
//     int top;
// };
// typedef struct regt2 r2;
// struct regt{
//     int left;
//     int right;
//     int bottom;
//     int top;

// };
// typedef struct regt r;
int minium(int num1,int num2){
    if(num1>=num2){
        return num2;
    }
    else{
        return num1;
    }
}
int maxium(int num1,int num2){
    if(num1>=num2){
        return num1;
    }
    else {
        return num2;
    }

}
void GetCommonRect(r r1,r r2/*int r1l,int r1r,int r1t,int r1b,int r2l,int r2r,int r2t,int r2b*/){//you can pass struct here
    r r;//you made logical problems here,you haven't judge if the common rect exists.
    r.left=maxium(r1.left,r2.left) ;
    r.right=minium(r1.right,r2.right) ;
    r.bottom=maxium(r1.bottom,r2.bottom) ;
    r.top=minium(r1.top,r2.top);
   if (r.left < r.right && r.bottom < r.top) {
        printf("common area: left=%d, right=%d, bottom=%d, top=%d\n",
               r.left, r.right, r.bottom, r.top);
    } else {
        printf("no common area between the two rectangles\n");
    }//you can return a struct as well
}




int main (){
    r r1;
    r r2;
    scanf("%d %d %d %d",&r1.left,&r1.right,&r1.top,&r1.bottom);//remrember scanf need & to locate var

    scanf("%d %d %d %d",&r2.left,&r2.right,&r2.top,&r2.bottom);

    GetCommonRect(r1,r2);
    return 0;

    
}