#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
char* concat(int num,...){
	va_list lst;
	va_start(lst,num);
	char** arr=(char**)malloc(num*sizeof(char*));
	char* result=(char*)malloc(num*80*sizeof(char));
	for(int i=0;i<num;i++){
		arr[i]=(char*)malloc(80*sizeof(char));
		strcpy(arr[i],va_arg(lst,char*));	
	}
	char* ch=arr[num-1];
	int index=0;
	for(int i=0;i<num-1;i++){
		char* target=arr[i];
		int k=0;
		while(target[k]!='\0'){
			result[index]=target[k];
			k++;
			index++;
		}
		if(i!=num-2){
			result[index]=ch[0];
			index++;
		}
		
	}
	ch[index]='\0';
	va_end(lst);
	return result;
}
int main(){
	int n=4;
	printf("%s",concat(n,"asd","bcd","efd","@"));	
	return 0;
}
