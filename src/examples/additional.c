#include<stdio.h>
#include<stdlib.h>
#include<syscall.h>

int main(int argc, char * argv[]){
    int arr[4];
    for(int i=1;i<=4;i++){
        arr[i-1]=atoi(argv[i]);
    }
    printf("%d %d\n", fibonacci(arr[0]), max_of_four_int(arr[0], arr[1], arr[2], arr[3]));


    return 0;
}