#include <stdio.h>
#include <stdlib.h>
struct Listnode{
    int a;
    struct Listnode* next;
    
};

struct Listnode* Head = NULL,* Tail =NULL;//未定义的野指针，不占用内存

void initList(){
    Head = (struct Listnode*)malloc(sizeof(struct Listnode));
    Head -> a = 0;
    Head -> next = NULL;//如果没有这句，Head -> next值会是随机的，而且没办法判断结束,Head → 0 → NULL
    Tail = (struct Listnode*)malloc(sizeof(struct Listnode));  
    Tail = Head;  
}
//H操作
void H(int a1,int a2,int a3){
    struct Listnode* n3 = (struct Listnode*)malloc(sizeof(struct Listnode));
    n3 -> a = a3;//n3储存a3
    n3 ->next =Head ->next;//把Head指向的节点的next赋给n3指向的节点的next，即 n3 → a3 → 0 → NULL
    Head -> next = n3;

    struct Listnode* n2 = (struct Listnode*)malloc(sizeof(struct Listnode));
    n2 ->a = a2;
    n2 ->next = Head ->next;
    Head ->next =n2;
    struct Listnode* n1 = (struct Listnode*)malloc(sizeof(struct Listnode));
    n1 -> a = a1;
    n1 ->next =Head ->next;
    Head ->next =n1;
}

// T操作
 
void T(int a1, int a2, int a3){
    struct Listnode* n1 = (struct Listnode*)malloc(sizeof(struct Listnode));  
    n1 -> a = a1;               
    n1 -> next = NULL;//给n1指向的节点的next指针赋值为NULL，它成为新的尾指针     
    Tail -> next = n1; //让Tail指向的节点的next指向n1指向的节点    
    Tail = n1;      //让Tail本身指向n1指向的节点            
    
    struct Listnode* n2 = (struct Listnode*)malloc(sizeof(struct Listnode));  
    n2 -> a = a2;               
    n2 -> next =NULL;         
    Tail -> next = n2;          
    Tail =n2;                  
    
    struct Listnode* n3 = (struct Listnode*)malloc(sizeof(struct Listnode));  
    n3 -> a =a3;               
    n3 ->next = NULL;      
    Tail -> next = n3;         
    Tail =n3;               
}


// D操作
void D(int location){
    //若头节点为删除节点
    if(location == 1){
        struct Listnode* temp = Head;//temp指向要删除的头节点
        Head = Head -> next;//Head指针指向原头节点的下一个节点
        free(temp);//删除头节点
    }
    else{
        // 找到要删除节点的前一个节点
        struct Listnode* current = Head;//current从头节点开始遍历
        for(int i = 1; i < location - 1; i++){
            if (current -> next == NULL)return;
            current = current -> next;//实现遍历，移动current
        }
            if (current -> next == NULL)return;//检查是否越界
        // 删除节点
        struct Listnode* temp = current -> next;//temp指向目标节点
        current -> next = temp -> next;//让要删除节点的前一个节点指向原节点的下一个节点
        free(temp);
    }
}

// R操作
void R(){
    struct Listnode* prev = NULL;      // prev指针，初始为NULL（反转后的尾）
    struct Listnode* current = Head;   
    struct Listnode* next = NULL;      // next指针，用于保存下一个节点
    
    while(current != NULL){
        next = current -> next;        // 保存current的下一个节点
        current -> next = prev;        // 让current指向前一个节点
        prev = current;                // prev移动到current位置
        current = next;                // current移动到下一个节点
    }
    
    Head = prev;                       // 更新Head指向原来的尾节点
}

// 打印链表（用于调试）
void printList(){
    struct Listnode* current = Head;
    while(current != NULL){
        printf("%d -> ", current -> a);
        current = current -> next;
    }
    printf("NULL\n");
}


//为什么没法调用outputToFile()?
void outputToFile() {
    FILE* file = fopen("Numbers.txt", "w");
    if (file == NULL) {
        printf("无法创建文件！\n");
        return;
    }
    
    struct Listnode* current = Head;
    while (current != NULL) {
        fprintf(file, "%d", current->a);
        current = current->next;
    }
    
    fclose(file);
    printf("链表数据已保存到 Numbers.txt\n");
}

int main() {
    initList();
    H(2, 1, 1);
    T(1, 0, 2);
    D(3);
    T(2, 1, 1);
    D(7);
    R();
    D(3);
    T(1, 2, 2);
    R();
    D(1);
    T(1, 2, 2);
    T(1, 1, 1);
    R();
    D(11);
    H(1, 2, 1);
    D(3);
    T(1, 1, 1);
    H(1, 2, 1);
    H(2, 0, 2);
    D(2);
    R();
    

    outputToFile();
    printf("最终链表：");
    printList();
    return 0;
}