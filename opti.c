#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 미완료 코드입니다 */

int getsize(int *arr){

    int tmp;
    tmp = sizeof(arr)/4;
    return tmp;
}


int calc1(int *arr){

    int i,j,least,val;
    int sum_result = 0;
    int mul_result = 0;

    struct timeval stime, etime, gap;

    gettimeofday(&stime, NULL);
    for (i = 0; i < getsize(arr); i++) {
                least = i;
                for (j = i + 1; j < getsize(arr); j++)
                        if (arr[j] < arr[least])
                                least = j;
                val = arr[least];
                arr[least] = arr[i];
                arr[i] = val;
        }
    gettimeofday(&etime, NULL);
    gap.tv_usec = etime.tv_usec - stime.tv_usec;

    printf("calc1 selection  elapsed time  = %ldusec\n",gap.tv_usec);

   val = 0;

   gettimeofday(&stime, NULL);
   for (i = getsize(arr) - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
                if (arr[j] > arr[j + 1]) {
                        val = arr[j];
                        arr[j] = arr[j - 1];
                        arr[j + 1] = val;
                }
        }
}
    gettimeofday(&etime, NULL);

    gap.tv_usec = etime.tv_usec - stime.tv_usec;
    printf("calc1 mul elapsed time = %ldusec\n",gap.tv_usec);

}


int calc2(int size,int *arr){

    int i,j,val,least;
    int sum_result = 0;
    int mul_result = 0;
    struct timeval stime, etime, gap;

    gettimeofday(&stime, NULL);
    for (i = 0; i < getsize(arr); i++) {
                least = i;
                for (j = i + 1; j < getsize(arr); j++)
                        if (arr[j] < arr[least])

                                least = j;
                val = arr[least];
                arr[least] = arr[i];
                arr[i] = val;
        }


    gettimeofday(&etime, NULL);
    gap.tv_usec = etime.tv_usec - stime.tv_usec;

    printf("calc2 sum elapsed time = %ldusec\n",gap.tv_usec);


    gettimeofday(&stime, NULL);

for (i = size - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
                if (arr[j] > arr[j + 1]) {
                        val = arr[j];
                        arr[j] = arr[j - 1];
                        arr[j + 1] = val;
                }
        }
}


    gettimeofday(&etime, NULL);
    gap.tv_usec = etime.tv_usec - stime.tv_usec;

    printf("calc2 mul elapsed time = %ldusec\n",gap.tv_usec);



}


int main(){


   int i;
   int size;
   size = 200;
   struct timeval stime, etime, gap;

   int* arr = (int*)malloc(sizeof(int) * size);

   for (i = 0; i<size; i++){
        arr[i] = rand() % 9;
     }


   gettimeofday(&stime, NULL);
   calc1(arr);
   gettimeofday(&etime, NULL);
   gap.tv_usec = etime.tv_usec - stime.tv_usec;

   printf("calc1 elapsed time = %ldusec\n",gap.tv_usec);


   gettimeofday(&stime, NULL);
   calc2(size,arr);
   gettimeofday(&etime, NULL);
   gap.tv_usec = etime.tv_usec - stime.tv_usec;

   printf("calc2 elapsed time = %ldusec\n",gap.tv_usec);



    return 0;
}






