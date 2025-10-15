#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
// <ctype.h>提供如下函数：
// isdigit(c) -- 判断是否为十进制数字字符
// isalpha(c) -- 判断是否为字母（大写或小写）
// isspace(c) -- 判断是否为空白字符（空格、换行等）
// ...
// 具体详情请自行了解

#define INPUT_MAXSIZE 45//示例输入不会超，但是很小

// Token类型定义
typedef enum{
    NUM,     // 整数
    ID,      // 标识符
    KEYWORD, // 关键字
    PLUS,    // +
    MINUS,   // -
    MUL,     // *
    DIV,     // /
    ASSIGN,  // =
    LPAREN,  // (
    RPAREN,  // )
    SEMI,    // ;
    EOF_TOKEN, // 结束标记
} TokenType;

// Token结构
typedef struct Token{
    TokenType type; // Token类型
    char *value; // Token的值（字符串形式）
} Token;

// 全局变量
char* input; //存储输入字符串
int pos; // 存储当前位置

// 初始化词法分析器
void init_lexer(char *input_str){
    input = input_str;
    pos = 0;
}

// 跳过空白字符
void skipwhitespace(){
    while(input[pos] != '\0'  && isspace(input[pos])){
         pos++;
    }
}

// 读取关键字和标识符
Token read_identifier(){
     int start = pos;//起始位置
     if (isalpha(input[pos]) || input[pos] == '_') {
        pos++;//第一个字符要是字母/下划线
        while (isalnum(input[pos]) || input[pos] == '_') {
            pos++;//后面接的是字母、数字/下划线
        }
     }
    int length = pos - start;
    char *value = (char*)malloc(length + 1);//分配内存
    strncpy(value, &input[start], length);//复制
    value[length] = '\0';//添加结束符
    
    Token token;
    if (strcmp(value, "int") == 0) {
        token.type = KEYWORD;//判为关键字int
    } else {
        token.type = ID;//判为标识符
    }
    token.value = value;
    
    return token;
}

// 读取整数（即连续数字）
Token read_number() {
    int start = pos;
    
    while (isdigit(input[pos])) {
        pos++;//循环所有数字
    }
    
    int length = pos - start;
    char *value = (char*)malloc(length + 1);
    strncpy(value, &input[start], length);
    value[length] = '\0';
    
    Token token;
    token.type = NUM;//创建NUM类型的Token
    token.value = value;
    
    return token;
}


// 获取Token
Token get_next_token(){
    skipwhitespace();

    if(input[pos] == '\0'){
        Token token;
        token.type = EOF_TOKEN;
        token.value = NULL;
        return token;
    }

    char c = input[pos];
    if (isalpha(c) || c == '_') {//数字或者下划线开头
        return read_identifier();
    }
     else if (isdigit(c)) {
        return read_number();
    }//数字开头
     else {
        Token token;
        token.value = NULL;

         switch (c) {//字符类型与token类型进行一一对应
            case '+': token.type = PLUS; pos++; break;
            case '-': token.type = MINUS; pos++; break;
            case '*': token.type = MUL; pos++; break;
            case '/': token.type = DIV; pos++; break;
            case '=': token.type = ASSIGN; pos++; break;
            case '(': token.type = LPAREN; pos++; break;
            case ')': token.type = RPAREN; pos++; break;
            case ';': token.type = SEMI; pos++; break;
            default://遇到没法识别的字符，输出错误信息并退出
                fprintf(stderr, "Unexpected character: %c\n", c);
                exit(1);
        }
        return token;
    }
}
        

    // 请补全代码
    // 如果读取到无法识别的字符，输出错误信息并退出；
    // 输出错误信息具体代码如下： 
    // fprintf(stderr, "Unexpected character: %c\n", c);
    // exit(1);


// 打印token
void print_token(Token token){
    switch (token.type) {
        case NUM:
            printf("[NUM, %s]\n", token.value);
            break;
        case ID:
            printf("[ID, \"%s\"]\n", token.value);
            break;
        case PLUS:
            printf("[PLUS, \"+\"]\n");
            break;
        case MINUS:
            printf("[MINUS, \"-\"]\n");
            break;
        case MUL:
            printf("[MUL, \"*\"]\n");
            break;
        case DIV:
            printf("[DIV, \"/\"]\n");
            break;
        case ASSIGN:
            printf("[ASSIGN, \"=\"]\n");
            break;
        case LPAREN:
            printf("[LPAREN, \"(\"]\n");
            break;
        case RPAREN:
            printf("[RPAREN, \")\"]\n");
            break;
        case SEMI:
            printf("[SEMI, \";\"]\n");
            break;
        case EOF_TOKEN:
            // 不打印结束标记
            break;
    }

    // 释放动态分配的内存
    if (token.value != NULL) {
        free(token.value);
    }
}

int main(){
    char input[INPUT_MAXSIZE];
    memset(input, 0, sizeof(input));
    printf("请输入要进行词法分析的字符串:\n");
    fgets(input, INPUT_MAXSIZE, stdin);
    init_lexer(input); // 初始化输入字符串

    // 读取并输出字符串中对应的token
    Token token;
    do{
        token = get_next_token();
        print_token(token);
    } while(token.type != EOF_TOKEN);

    return 0;
}