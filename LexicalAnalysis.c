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
char res[15][100]={"Begin","End","For","If","Then","Else","Ident","Int",
"Colon","Plus","Star","Comma","LParenthesis","RParenthesis","Assign"};
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
	if(strcmp(token,"BEGIN")==0) return BEGIN;
	else if(strcmp(token,"END")==0) return END;
	else if(strcmp(token,"FOR")==0) return FOR;
	else if(strcmp(token,"IF")==0) return IF;
	else if(strcmp(token,"THEN")==0) return THEN;
	else if(strcmp(token,"ELSE")==0) return ELSE;
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
	else {
		if(c==EOF) return 0;
		error();
	}
	return 0;
}
int main(int argc, char *argv[]){
	fp = fopen(argv[1], "r");
	while(c!=EOF) {
		getsym();
		if(symbol!=7&&symbol!=8)
			printf("%s\n",res[symbol-1]);
		else if(symbol==7)
			printf("%s(%s)\n",res[6],token);
		else printf("%s(%d)\n",res[7],num);
	}
	fclose(fp);
	return 0;
}
