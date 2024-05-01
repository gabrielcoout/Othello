#include <stdio.h>

int main() {
    printf("-----------------------------------------\n");
    for (int i = 0; i < 64; i++) {
        printf("| ");
        printf("%2d ", i);
        if ((i + 1) % 8 == 0) {
            printf("|\n-----------------------------------------\n");
        }
    }   
    
    return(0);
}
