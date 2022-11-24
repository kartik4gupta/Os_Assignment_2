#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    float SOURCE[4][4]={{1.0,2.0,3.0,4,0},{1.0,2.0,3.0,4.0},{1.0,2.0,3.0,4.0},{1.0,2.0,3.0,4.0}};
    float DESTINATION[4][4];

    printf("Initial Matrix: \n");
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            printf("%f ",SOURCE[x][y]);
        }
        printf("\n");
    }
    printf("\n");

    if(syscall(451 ,DESTINATION,SOURCE,4)<0){    //451 SYS_kernel_2Dcpy
        printf("ERROR OCCURED! Could not perform syscall.\n");
        exit(1);
    }
     printf("Final Matrix: \n");
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            printf("%f ",DESTINATION[x][y]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}
