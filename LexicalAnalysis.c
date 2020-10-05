#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
#define BEGIN 1
#define END 2
#define FOR 3
#define IF 4
#define THEN 5
#define ELSE 6
#define IDSY 7
#define INTSY 8
#define COLONSY 9
#define PLUSSY 10
#define STARSY 11
#define COMSY 12
#define LPARSY 13
#define RPARSY 14
#define ASSIGNSY 15
char token[150];
int num,symbol;
char c;
FILE *fp;
bool isSpace(){
	if(c==' ') return true;
	return false;
}
bool isNewline(){
	if(c=='\n' || c=='\r') return true;
	return false;
}
bool isTab(){
	if(c=='\t') return true;
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
	symbol=0;
	printf("Unknown\n");
	exit(0);
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
	if(strcmp(token,"BEGIN")==0) {
		symbol=BEGIN;
		printf("Begin\n");
		return 1;
	}
	else if(strcmp(token,"END")==0) {
		symbol=END;
		printf("End\n");
		return 1;
	}
	else if(strcmp(token,"FOR")==0) {
		symbol=FOR;
		printf("For\n");
		return 1;
	}
	else if(strcmp(token,"IF")==0) {
		symbol=IF;
		printf("If\n");
		return 1;
	}
	else if(strcmp(token,"THEN")==0){
		symbol=THEN;
		printf("Then\n");
		return 1;
	}
	else if(strcmp(token,"ELSE")==0) {
		symbol=ELSE;
		printf("Else\n");
		return 1;
	}
	else return 0;
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
		if(resultValue==0) {//标识符
			symbol=IDSY;
			printf("Ident(%s)\n",token);
		} 
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
		printf("Int(%d)\n",num);
	}
	else if(isColon()){
		c=fgetc(fp);
		if(isEqu()) {
			symbol=ASSIGNSY;
			printf("Assign\n");
		}
		else{
			fseek(fp,-1,SEEK_CUR);
			symbol=COLONSY;
			printf("Colon\n");
		}
	}
	else if(isPlus()) {
		symbol=PLUSSY;
		printf("Plus\n");
	}
	else if(isStar()) {
		symbol=STARSY;
		printf("Star\n");
	}
	else if(isComma()) {
		symbol=COMSY;
		printf("Comma\n");
	}
	else if(isLpar()) {
		symbol=LPARSY;
		printf("LParenthesis\n");
	}
	else if(isRpar()) {
		symbol=RPARSY;	
		printf("RParenthesis\n");
	}
	else {
		if(c==EOF) return 0;
		error();
	}
	return 0;
}
int main(int argc, char *argv[]){
	fp = fopen(argv[1], "r");
	while(c!=EOF) {
		symbol=0;
		getsym();
	}
	fclose(fp);
	return 0;
}
