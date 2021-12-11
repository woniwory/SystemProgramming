/* mycp program, by Jeongsw. woniwory@naver.com */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


#define MAX_BUF 64
int main(int argc, char *argv[])
{

    int fd,fd1, read_size,write_size;
    char buf[MAX_BUF];
    struct stat buffer;

    stat(argv[1], &buffer);

    if(argc != 3) {
        printf("USAGE : %s file_name \n", argv[0]); exit(-1);
 }

    fd = open(argv[1], O_RDONLY);
    fd1 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, buffer.st_mode);
    if (fd <0) {
        printf("can't open file1");
}
    if (fd1 < 0) {
        printf("can't open file2");
        exit(-1);
}


    while(1){
        read_size = read(fd, buf, MAX_BUF);
        if(read_size == 0){
                break;
        }
        else{
        write_size = write(fd1, buf, read_size);
        }
        }
    close(fd);
    close(f1);

