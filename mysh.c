#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#define MAX_SYS 128
bool cmd_help(int argc, char* argv[]);
bool cmd_quit(int argc, char* argv[]);
bool cmd_exit(int argc, char* argv[]);
bool cmd_cd(int argc, char*argv[]);
int check(char *line[]);
int tokenize(char *buf, char *delims, char *tokens[], int max);
bool run(char *line);

struct shell {  //shell sturcture
        char *key;
        char *key_ex; bool (*intr_func)(int argc, char *argv[]);
};
struct shell cmd[] = {
        {"help", "Show this help ", cmd_help},
        {"quit", "Quit this Shell", cmd_quit},
        {"exit", "Exit this shell", cmd_exit},
        {"cd", "Change directory", cmd_cd},
        {">", "Redirection"},
        {"&", "Run task on background"}
};

int main(){ // main 함수
        char line[1024], usr[MAX_SYS], cwd[MAX_SYS];
        getlogin_r(usr, MAX_SYS);
        getcwd(cwd, MAX_SYS);
        while(1){
                printf("%s@%s $ ", usr, cwd);
                fgets(line, sizeof(line) - 1, stdin);
                if(run(line) == false) break;
        }
        return 0;
}

bool cmd_help(int argc, char* argv[]) {  // ���� ��� �Լ�
        int i;
        printf("-----------------Seongwon's Shell -----------------\n");





        printf("CMD\t FUNCTION\n------------------------------------------------\n");
        for (i = 0; i < 4; i++) printf("%s\t %s\n", cmd[i].key, cmd[i].key_ex);
        printf("------------------------------------------------\n");
        printf("KEY\t FUNCTION\n------------------------------------------------\n");
        for (i = 4; i < 8; i++) printf("%s\t %s\n", cmd[i].key, cmd[i].key_ex);
        return true;
}

bool cmd_quit(int argc, char*argv[]){return 0;}

bool cmd_exit(int argc, char* argv[]) { return 0; }

bool cmd_cd(int argc, char*argv[]){  // ���丮 ���� �Լ�
        if(argc == 1);
        else if(argc == 2) {
                if(chdir(argv[1])) printf("type correct directory\n");
        }
        else printf("USAGE: %s [dir_name]\n", argv[0]);
        return true;
}

void cmd_redirection(int argc, char *argv[]){  // redirection
        int fd;
        if (argc != 4) { printf("USAGE: %s input > output\n", argv[0]); return; }
        if((fd = open(argv[3], O_WRONLY | O_CREAT, 0664)) < 0) {
                printf("Can't open %s file with errno %d\n", argv[3], errno);
                return;
        }
        dup2(fd, STDOUT_FILENO);
        argv[2] = NULL;
        close(fd);
}


int check(char *line[]){  // check
        int i;
        for(i=0; line[i] != NULL; i++){
                if(!strcmp(line[i], ">")) return 1;
                if(!strcmp(line[i], "&")) {line[i] = NULL; return 2;}
        }
        return 0;


int tokenize(char *buf, char *delims, char *tokens[], int max){  // tokenize
        int token_count = 0;
        char *token = strtok(buf, delims);
        while(token != NULL && token_count < max){
                tokens[token_count] = token; token_count++;
                token = strtok(NULL, delims);
        }
        tokens[token_count] = NULL;
        return token_count;
}

void cmd_BackgroundExec(char *token[]) {
 pid_t pid;
 int fd_bg;
 printf("!!! : %s\n",token[0]);
 if((pid = fork()) == 0) {
     fd_bg = open("/dev/null", O_RDONLY);
     dup2(fd_bg, STDOUT_FILENO);
     execvp(token[0],token);
     exit(0);
 }
}

bool run(char *line){  // run(execute)함수
    int flag = 0;
    char delims[] = " \n";
    char *tokens[MAX_SYS];
    pid_t pid;
    int i, stat, chk;
        int token_count = tokenize(line, delims, tokens, sizeof(tokens) / sizeof(char*));
        if(token_count == 0) return true;
        chk = check(tokens);
        for(i = 0; i < 4; i++) {
        if(strcmp(cmd[i].key, tokens[0]) == 0)
                return cmd[i].intr_func(token_count, tokens);
    }
        if((pid=fork()) < 0) {
                perror("fork error caused\n");
                exit(-1);
        }
        else if(pid == 0) {
                if(chk == 1){  // redirection
                flag++;
                cmd_redirection(token_count, tokens);
                execvp(tokens[0], tokens);
 }

        }
        else {
                if(chk == 2) {
                        flag++;  // background
                        cmd_BackgroundExec(tokens);
                }
        }

        if (flag ==0){
                execvp(tokens[0], tokens);
                exit(0);
        }

        return true;


}
















                                                            

