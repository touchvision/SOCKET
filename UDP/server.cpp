 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <unistd.h>
 #include <errno.h>
 #include <string.h>
 #include <stdlib.h>

 #define SERV_PORT   12345

 int main()
 {
   int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
   int newsock = 0;
   struct sockaddr_in client_addr;
   int addr_len = sizeof(struct sockaddr_in);

   if(sock_fd < 0)
   {
     perror("socket");
     exit(1);
   }

   struct sockaddr_in addr_serv;
   int len;
   memset(&addr_serv, 0, sizeof(struct sockaddr_in));
   addr_serv.sin_family = AF_INET;
   addr_serv.sin_port = htons(SERV_PORT);
   addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
   len = sizeof(addr_serv);

   if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
   {
     perror("bind error:");
     exit(1);
   }

   listen(sock_fd, 5);
   printf("listen tcp connect\n");

   int recv_num;
   int send_num;
   char send_buf[20] = "i am server!";
   char recv_buf[20];
   struct sockaddr_in addr_client;

   while(1)
   {
     printf("server wait:\n");
     newsock = accept(sock_fd, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len);
     if(newsock < 0) {
        printf("accept fail");
        exit(1);
     }

     recv_num = recvfrom(newsock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);

     if(recv_num < 0)
     {
       perror("recvfrom error:");
       exit(1);
     }

     recv_buf[recv_num] = '\0';
     printf("server receive %d bytes: %s\n", recv_num, recv_buf);

     send_num = sendto(newsock, send_buf, recv_num, 0, (struct sockaddr *)&addr_client, len);

     if(send_num < 0)
     {
       perror("sendto error:");
       exit(1);
     }
   }

   close(sock_fd);

   return 0;
 }
