#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
#define BEGIN 1
#define END 2
#define FOR 3
#define DO 4
#define IF 5
#define THEN 6
#define ELSE 7
#define IDSY 8
#define INTSY 9
#define COLONSY 10
#define PLUSSY 11
#define STARSY 12
#define COMSY 13
#define LPARSY 14
#define RPARSY 15
#define ASSIGNSY 16
char token[150];
int num,symbol;
char c;
FILE *fp;
bool isSpace(){
	if(c==' ') return true;
	return false;
}
bool isNewline(){
	if(c=='\n') return true;
	return false;
}
bool isTab(){
	if(c=='\r') return true;
	return false;
}
bool isLetter(){
	if((c>='a'&&c<='z')||(c>='A'&&c<='Z')) return true;
	return false;
}
bool isDigit(){
	if(c>='0'&&c<='9') return true;
	return false;
}
bool isColon(){
	if(c==':') return true;
	return false;
}
bool isEqu(){
	if(c=='=') return true;
	return false;
}
bool isPlus(){
	if(c=='+') return true;
	return false;
}
bool isStar(){
	if(c=='*') return true;
	return false;
}
bool isComma(){
	if(c==',') return true;
	return false;
}
bool isLpar(){
	if(c=='(') return true;
	return false;
}
bool isRpar(){
	if(c==')') return true;
	return false;
}
void error(){
	printf("词法错误\n");
}
void clearToken(){
	int l=strlen(token);
	int i=0;
	for(i=0;i<l;i++)
		token[i]=0;
}
void catToken(){
	token[strlen(token)]=c;
}
int reserver(){
	if(strcmp(token,"BEGIN")==0) symbol=BEGIN;
	if(strcmp(token,"END")==0) symbol=END;
	if(strcmp(token,"FOR")==0) symbol=FOR;
	if(strcmp(token,"DO")==0) symbol=DO;
	if(strcmp(token,"IF")==0) symbol=IF;
	if(strcmp(token,"THEN")==0) symbol=THEN;
	if(strcmp(token,"ELSE")==0) symbol=ELSE;
	return 0;
}
int getsym(){
	clearToken();
	do{
		c=fgetc(fp);
//			printf("%c\n",c);
	}while(isSpace() || isNewline() || isTab());
	if(isLetter()){
		while(isLetter() || isDigit()){
			catToken();
			c=fgetc(fp);
//				printf("c1 %c\n",c);
		} 
		fseek(fp,-1,SEEK_CUR);
//			c=fgetc(fp);
//			printf("c2 %c\n",c);
		int resultValue=reserver();
		if(resultValue==0) symbol=IDSY;//标识符 
		else symbol=resultValue;
	}
	else if(isDigit()){
		while(isDigit()){
			catToken();
			c=fgetc(fp);
		}
		fseek(fp,-1,SEEK_CUR);
		num=atoi(token);
		symbol=INTSY;
	}
	else if(isColon()){
		c=fgetc(fp);
		if(isEqu()) symbol=ASSIGNSY;
		else{
			fseek(fp,-1,SEEK_CUR);
			symbol=COLONSY;
		}
	}
	else if(isPlus()) symbol=PLUSSY;
	else if(isStar()) symbol=STARSY;
	else if(isComma()) symbol=COMSY;
	else if(isLpar()) symbol=LPARSY;
	else if(isRpar()) symbol=RPARSY;
	else error();
	return 0;
}
int main(){
	fp = fopen("test.txt", "r");
	while(c!=EOF) {
		getsym();
		printf("%d\n",symbol);
	}
	fclose(fp);
	return 0;
}
