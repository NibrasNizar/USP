/* How to Run:-
Open 2 terminals, in one do cc client -o client, in the other do cc server -o server
Then ./client hello in client terminal and ./server in server terminal.
*/
//Client
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#define MAX 80

int main(int argc,char* argv[])
{char buffer[MAX];
int in,out,n;
in = open("server_to_client",O_RDWR,0777);
out = open("client_to_server",O_RDWR,0777);
printf("Sending Message\n");
n = strlen(argv[1]);
write(out,argv[1],n);
read(in,buffer,n);
buffer[n]='\0';
printf("Message Received : %s\n",buffer);
close(in);
close(out);
}
//Server
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#define MAX 80

int main()
{char buffer[MAX];
int in,out,n;
mkfifo("server_to_client",0777);
mkfifo("client_to_server",0777);
while(1)
{in = open("client_to_server",O_RDWR,0777);
out = open("server_to_client",O_RDWR,0777);
memset(buffer,0,MAX);
printf("Waiting for Message\n");
n = read(in,buffer,MAX);
printf("Message : %s\n",buffer);
buffer[0] = toupper(buffer[0]);
printf("Sending Reply\n");
write(out,buffer,n);
close(in);
close(out);
}
return 0;
}
