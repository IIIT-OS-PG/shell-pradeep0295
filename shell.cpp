#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
#include "chd.h"
using namespace std;
#define MAXL 55
void exe(char * argv[]){
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
   int argc;
int main()
{
    char buf[MAXL];
    cout<<"%% ";
    char *argv[100];
    char history[100];
    while(fgets(buf, MAXL, stdin) !=NULL) {
        int check=strlen(buf) - 1 ;
        buf[check] = 0;
        argc=parse(argv,buf);
        //cout<<argv[0];
        //if(!argv[0])
        //	cout<<"found";
        //for(int i=0;i<3;i++)
        //	cout<<argv[i];
        //cout<<check;
        if(check!=0 && strcmp(argv[0],"cd") == 0){
        	chd(argv,history);
		}
        else if(check!=0) 
        	exe(argv);
        cout<< "%% ";
 		}	
    
    return 0;
}
