#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//瀛樻斁褰撳墠璇昏繘鐨勫瓧绗?
char nowChar;

//瀛樻斁鍗曡瘝鐨勫瓧绗︿覆
char token[50];

//瀛樻斁褰撳墠璇诲叆鐨勬暣鍨嬫暟鍊?
int num;

//鏂囦欢鎸囬拡锛岀敤鏉ュ紩鐢ㄥ綋鍓嶈緭鍏ョ殑鏂囦欢
FILE *fd;

//浠巉d涓鍏ヤ竴涓瓧绗?
void myGetchar(){
    nowChar = (char)fgetc(fd);
}

//娓呯┖token
void clearToken(){
    for(int i = 0;i < 30;i++){
        token[i] = 0;
    }
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓虹┖鏍?
bool isSpace(){
    if(nowChar == ' '){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓烘崲琛?
bool isNewline(){
    if(nowChar == '\n' || nowChar == '\r'){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓哄埗琛ㄧ
bool isTab(){
    if(nowChar == '\t'){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓哄瓧姣?
bool isLetter(){
    if(isalpha(nowChar)){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓烘暟瀛?
bool isDigit(){
    if(isdigit(nowChar)){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓哄啋鍙?
bool isColon(){
    if(nowChar == ':'){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓洪€楀彿
bool isComma(){
    if(nowChar == ','){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓虹瓑鍙?
bool isEqu(){
    if(nowChar == '='){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓哄姞鍙?
bool isPlus(){
    if(nowChar == '+'){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓烘槦鍙?
bool isStar(){
    if(nowChar == '*'){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓哄乏鎷彿
bool isLpar(){
    if(nowChar == '('){
        return true;
    }
    return false;
}

//鍒ゆ柇褰撳墠瀛楃鏄惁涓哄彸鎷彿
bool isRpar(){
    if(nowChar == ')'){
        return true;
    }
    return false;
}

//灏嗗綋鍓嶈鍒扮殑瀛楃鎷兼帴鍒皌oken鍚庨潰
void catToken(){
    strcat(token, &nowChar);
}

//fd鍥為€€涓€鏍?
void retract(){
    ungetc(nowChar, fd);
}

//鍒ゆ柇鏄惁鏄繚鐣欏瓧
bool reserver(){
    if(strcmp(token, "BEGIN") == 0){
        printf("Begin\n");
        return true;
    }
    else if(strcmp(token, "END") == 0){
        printf("End\n");
        return true;
    }
    else if(strcmp(token, "FOR") == 0){
        printf("For\n");
        return true;
    }
    else if(strcmp(token, "IF") == 0){
        printf("If\n");
        return true;
    }
    else if(strcmp(token, "THEN") == 0){
        printf("Then\n");
        return true;
    }
    else if(strcmp(token, "ELSE") == 0){
        printf("Else\n");
        return true;
    }
    else{
        return false;
    }
}

//灏唗oken涓殑瀛楃涓茶浆鍖栨垚鍗佽繘鍒舵暟瀛楀苟瀛樺埌num涓?
void transNum(){
    char *stop;
    num = strtol(token, &stop, 10);
}

//閿欒澶勭悊
void error(){
    printf("Unknown");
    exit(0);
}

//涓诲垎鏋愬嚱鏁?
void getsym(){
    clearToken();
    myGetchar();
    while(isSpace() || isNewline() || isTab()){
        myGetchar();
    }
    if(isLetter()){
        while(isLetter() || isDigit()){
            catToken();
            myGetchar();
        }
        retract();
        if(!reserver()){
            printf("Ident(%s)\n", token);
        }
    }
    else if(isDigit()){
        while(isDigit()){
            catToken();
            myGetchar();
        }
        retract();
        transNum();
        printf("Int(%d)\n", num);
    }
    else if(isColon()){
        myGetchar();
        if(isEqu()){
            printf("Assign\n");
        }
        else{
            retract();
            printf("Colon\n");
        }
    }
    else if(isPlus()){
        printf("Plus\n");
    }
    else if(isStar()){
        printf("Star\n");
    }
    else if(isComma()){
        printf("Comma\n");
    }
    else if(isLpar()){
        printf("LParenthesis\n");
    }
    else if(isRpar()){
        printf("RParenthesis\n");
    }
    else{
        if(feof(fd)){
            return;
        }
        error();
    }
}
int main(int argc, char *argv[]) {
    fd = fopen(argv[1], "r");
    while(!feof(fd)){
        getsym();
    }
    fclose(fd);
    return 0;
}
