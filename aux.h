#include <stdio.h>

void print2Darray(int arr[][2], int rows, int cols){
     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int min(int a,int b) {
    if (a<b){
        return(a);
    } else {
        return(b);
    }
}
int max(int a, int b) {
    if (a>b){
        return(a);
    } else {
        return(b);
    }
}

int msm_linha(int a, int b){
    if (a/8 == b/8){
        return(1);
    } else {
        return(0);
    }
}

int msm_coluna(int a, int b){
    if (a%8 == b%8){
        return(1);
    } else {
        return(0);
    }
}