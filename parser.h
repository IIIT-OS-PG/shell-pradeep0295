#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
int pipeparse(char * argv[],char buf[]){
	char * token =strtok(buf, "|");
	int i=0;
	argv[i]=token;
	while(token!=NULL){
		token=strtok(NULL, "|");
		i++;
		argv[i]=token;
	}
	return i;
}
int parse(char*c[],char *p){
	char temp[1000];
	if(p!=NULL){
		strcpy(temp,p);
	}
	char * token =strtok(temp, " ");
	int i=0;
	c[i]=token;
	while(token!=NULL){
		token=strtok(NULL, " ");
		i++;
		c[i]=token;
	}
	return i; 
}