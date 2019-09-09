#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
#include "chd.h"
using namespace std;
#define MAXL 55
int argc;
void exe(char *argv[]){
	pid_t pid;
    int status;
        if( (pid = fork()) < 0)
            cout<<"fork error";
        else if(pid == 0) {
            execvp(argv[0] , argv);
            cout<<"couldn't execute:";
        }

        if((pid = waitpid(pid, &status, 0) )<0)
            printf("waitpid error");
    }
void pipeexe(char*argv[],int np){
	int status;
	pid_t pid;
	int pifds[2*np];
	//cout<<np;
	int i,v=0;
	for(i=0;i<np;i++){  //number of pipes = commands - 1
		if(pipe(pifds+(i*2))< 0){
			perror("pipe failed");
		}
	}
	int j,k,b,m = 0;
	while(k<np+1){
		char * temp[1000];
		argc=parse(temp,argv[k]);
	    //for(int i=0;i<argc;i++)cout<<temp[i]<<endl;
		pid = fork();
		if(pid == -1){
			perror("fork error");
		}
		else if(pid == 0) {
			if(argv[k+1]){
				if(dup2(pifds[j+1],1)<0){
					perror("dup2");
				}
			}
			if(j!=0){
				if(dup2(pifds[j-2],0) < 0){
					perror("dup2");
				}
			}
			for(v=0;v<2*np;v++){
				close(pifds[v]);
			}
			if(execvp(temp[0],temp)<0){
				perror(temp[0]);
			}
		}
		k++;
		j+=2;
		/*if(k==np){
		char te[100];
		if(argv[k]!=0)strcpy(te,argv[k]);
		char *toke=strtok(te,">");
		argv[k]=toke;
		toke=strtok(NULL,">");
		char*file=toke;
    	dup2(pifds[2*(np-1)], 0);  // Set stdin to a copy of the reading end of pipe
    	close(pifds[2*(np-1)]);   
    	int fd=open(file, O_WRONLY|O_CREAT|O_TRUNC, 0600);
    	if (fd < 0){
        perror("open failed");
        exit(1);
    	}  
    	dup2(fd,1);  // redirect stdout to a copy of fd
    	close(fd);   // original fd no longer needed
		}*/
	}
	for(b=0;b<2*np;b++){
		close(pifds[b]);
	}
	for(m=0;m<np+1;m++){
		wait(NULL);
	}
 }
int main()
{
    char buf[MAXL];
    cout<<"$  ";
    char *argv[1000];
    char history[1000];
    int p;
    while(fgets(buf, MAXL, stdin) !=NULL) {
        int check=strlen(buf) - 1 ;
        buf[check] = 0;
        p=pipeparse(argv,buf);
        //cout<<p;
    	if(p<=1){
    	argc=parse(argv,buf);
        if(check!=0 && strcmp(argv[0],"cd") == 0){
        	chd(argv,history);
		}
        else if(check!=0) 
        	exe(argv);
    	}	
    	else{
    		pipeexe(argv,p-1);
    		//cout<<p;
    	}
        cout<<"$  ";
 	}	
    return 0;
}