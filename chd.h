#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
extern int argc;
void chd(char *argv[],char history[]){
	argv[0]+=3;
	 if(argc >1 && strcmp(argv[1],"-") == 0){
 		if((strlen(history)-1) != 0) {
 			strcpy(argv[0],history);
 			getcwd(history,100);
 			if(chdir(argv[0])<0)
				cout<< "cd: NO such file or Directory";
		}
 		else
 			cout<<"error: OLDPWD not set \n";
 	}
	else if(argc > 1){
		getcwd(history,100);
		if(chdir(argv[0])<0)
				cout<< "cd: NO such file or Directory";
	}
	else {
 		getcwd(history,100);
 		argv[1]=strtok(history," ");
		if(chdir(argv[0])<0)
			cout<< "cd: NO such file or Directory";
	}
}
