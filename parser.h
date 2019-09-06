#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
int parse(char * argv[],char buf[]){
	char * token =strtok(buf, " \n\t");
	int i=0;
	argv[i]=token;
	while(token!=NULL){
		
		token=strtok(NULL, "  \n\t");
		i++;
		argv[i]=token;
	}
	return i;
}