#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<errno.h>
#include<stddef.h>
#include<unistd.h>

#define MAX_CONNECT_NUM 2
#define BUFFER_SIZE 1024
const char *filename="uds-tmp";

int main()
{
    int fd,new_fd,len,i;
    struct sockaddr_un un;
    fd = socket(AF_UNIX,SOCK_STREAM,0);
    if(fd < 0){
        printf("Request socket failed!\n");
        return -1;
    }
    un.sun_family = AF_UNIX;
    unlink(filename);
    strcpy(un.sun_path,filename);
    if(bind(fd,(struct sockaddr *)&un,sizeof(un)) <0 ){
        printf("bind failed!\n");
        return -1;
    }
    if(listen(fd,MAX_CONNECT_NUM) < 0){
        printf("listen failed!\n");
        return -1;
    }
    while(1){
        struct sockaddr_un client_addr;
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);
        len = sizeof(client_addr);
        new_fd = accept(fd,(struct sockaddr *)&client_addr,(socklen_t*)&len);
        printf(" clent_addr.sun_path:%s \n",client_addr.sun_path);
        //new_fd = accept(fd,NULL,NULL);
        if(new_fd < 0){
            printf("accept failed\n");
            return -1;
        }
        int ret = recv(new_fd,buffer,BUFFER_SIZE,0);
        if(ret < 0){
            printf("recv failed\n");
        }
        for(i=0; i<10; i++){
            printf(" %d \n",buffer[i]);
        }
        close(new_fd);
        break;
    }
    close(fd);
}
