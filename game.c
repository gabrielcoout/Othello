#include <stdio.h>

int printMatrix(int array[8][8]) {
    int i, j;
    printf("---------------------------------\n");
    for (i = 0; i < 8; i++) {
        printf("|");
        for (j = 0; j < 8; j++) {
            if (array[i][j]>=0 && array[i][j]<=2)
            {
                switch (array[i][j])
                {
                case 1:
                    printf(" x ");
                    break;
                case 2:
                    printf(" o ");
                    break;
                
                default:
                    printf("   ");
                    break;
                }
            }
        else{
            printf("error");
            return(1);
            }
        printf("|");
        }
        printf("\n---------------------------------\n");
    }
    return(0);
}


int main() {
    int array[8][8];
    int i, j;
    
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
        array[i][j]=0;
        }
    }
    array[3][3]=1;
    array[4][4]=1;
    array[3][4]=2;
    array[4][3]=2;


    printMatrix(array);

    return(0);
}