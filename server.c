#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
void ErrorMessage(const char *msg){
    perror(msg);
    return;
}
 
int main(int argc,char *argv[]){
 
  //  while(1==1)

    //{
    int sock_fd=0,new_sock_fd=0,port=0,clilen=0,n=0;
    char buffer[256];
    struct sockaddr_in serv_addr,cli_addr;
 
    if(argc<2){
        fprintf(stderr,"Error port is missing\n");
        return 0;
    }
 
    sock_fd=socket(AF_INET,SOCK_STREAM,0);
 
    if(sock_fd<0)
        fprintf(stderr,"Error opening socket");
 
    bzero((char *)&serv_addr,sizeof(serv_addr));
    port=atoi(argv[1]);
 
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
 
    if(bind(sock_fd, (struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
        ErrorMessage("Error in connection");
 
    listen(sock_fd,5);
 
 
    for(;;)
    {

    clilen=sizeof(cli_addr);
    new_sock_fd=accept(sock_fd,(struct sockaddr *)&cli_addr,&clilen);
    if(new_sock_fd<0)
    {
        printf("Waiting for another connection...\n");
	exit (10);
     }

 
    //bzero(buffer,256);
	//while(n=read(new_sock_fd,buffer,255))
   // {
	//n=read(new_sock_fd,buffer,255);
    //if(n<0)
      //  ErrorMessage("Error reading socket");
    //printf("Here is the message:%s",buffer);
 
    //n=write(new_sock_fd,"Got your message",16);
 
    //if(n<0)
      //  ErrorMessage("Error writing on socket");
//	}
        int childpid;
	if ((childpid = fork()) == 0) { //creating a child process
           close(sock_fd); 

	//Read Picture Byte Array and Copy in file
	printf("Reading Picture Byte Array\n");
	char p_array[10000];
	FILE *image = fopen("c1.wmv", "w");
	int nb = read(new_sock_fd, p_array, 10000);
	while (nb > 0 ) {
		fwrite(p_array, 1, nb, image);
		nb = read(new_sock_fd, p_array, 10000);
	}
        printf("Video received\n");
	fclose(image);
 	//close(new_sock_fd);
	//close(sock_fd);
	//sleep(10);
	
	  //int nb;
	//while( nb = read(new_sock_fd, p_array, 10000))
	//{
	  //      //nb = read(new_sock_fd, p_array, 10000);
	//	fwrite(p_array, 1, nb, image);
	//	nb = read(new_sock_fd, p_array, 10000);
	//}

	//if(nb<=0){
	//printf("Video received");
	//fclose(image);
	
	}
	}
 //    }

    return 0;
}
