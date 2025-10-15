#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000//安全的大

// 栈结构
typedef struct {
    char data[MAX_SIZE];//字符数组存储
    int top;//栈顶指针，指向最后一个元素
} Stack;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;//栈顶指针设为-1，表示空栈，方便后面索引从0开始
}

// 判断栈是否为空，检查，防止越界
int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char c) {
    if (s->top < MAX_SIZE - 1) {
        s->data[++(s->top)] = c;
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '!';  // 栈为空时返回'!'
}

char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '!';
}

int main() {
    Stack s;
    initStack(&s);
    FILE* numFile = fopen("Numbers.txt", "r");//读取之前得到的字符串
    if (!numFile) {
        printf("无法打开 Numbers.txt\n");
        return 1;
    }
    
    char numberStr[MAX_SIZE];
    fscanf(numFile, "%s", numberStr);
    fclose(numFile);
    
    char cipherStr[MAX_SIZE] = "cewlrotemelgmim";
    printf("密文：%s\n",cipherStr);
    
    printf("数字串: %s\n", numberStr);
    printf("密文串: %s\n", cipherStr);
    
    int cipherIndex = 0;  // 密文串当前索引
    int len = strlen(numberStr);
    
    printf("解密过程:\n");
    
    for (int i = 0; i < len; i++) {
        char num = numberStr[i];
        
        switch(num) {
            case '0':
                if (!isEmpty(&s)) {
                    printf("操作0 - 查看栈顶: %c\n", peek(&s));
                }
                break;// 读取栈顶字符并输出（不弹出）
                
            case '1':
                if (cipherIndex < strlen(cipherStr)) {
                    push(&s, cipherStr[cipherIndex]);
                    printf("操作1 - 压入: %c\n", cipherStr[cipherIndex]);
                    cipherIndex++;
                }
                break;// 执行一次压入操作
                
            case '2':
                printf("操作2 - 第一次弹出: ");
                char first = pop(&s);
                printf("%c\n", first);
                
                printf("操作2 - 第二次弹出: ");
                char second = pop(&s);
                printf("%c\n", second);
                break; // 执行两次弹出操作
        }
    }
    
    printf("\n最终栈状态: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");
    
    return 0;
}