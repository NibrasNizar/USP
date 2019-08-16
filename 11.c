//for output: ls -l |grep source2.txt
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<utime.h>
#include<time.h>
#include<fcntl.h>
int main(){
struct utimbuf times;
struct stat mystat;
umask(0066);
if(creat("source2.txt",0666)<0){
printf("Error");
return 0;
}
stat("source2.txt",&mystat);
times.actime=mystat.st_atime;
times.modtime=mystat.st_mtime;
utime("source2.txt",&times);
printf("%s %s",ctime(&times.actime),ctime(&times.modtime));
printf("%s %s",ctime(&mystat.st_atime),ctime(&mystat.st_mtime));
}
