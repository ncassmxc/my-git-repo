#include <stdio.c>
int square(int x){
    return x * x;
}
           
void calcpersonscore(int p,int f,int zh,int a,int b,int c){
    p = (a+b+c)/3;
    f = square(p-a)+square(p-b)+square(p-c)/3;
    zh = 3 * p -f/3;
}

void results(int zh1,int zh2,int zh3){
    if (zh1 >= zh2 && zh2 >= zh3) {
      printf("小明 > 小强 > 小林");
  } else if (zh1 >= zh3 && zh3 >= zh2) {
      printf("小明 > 小林 > 小强");
  } else if (zh2 >= zh1 && zh1 >= zh3) {
      printf("小强 > 小明 > 小林");
  } else if (zh2 >= zh3 && zh3 >= zh1) {
      printf("小强 > 小林 > 小明");
  } else if (zh3 >= zh1 && zh1 >= zh2) {
      printf("小林 > 小明 > 小强");
  } else { // zh3 >= zh2 && zh2 >= zh1
      printf("小林 > 小强 > 小明");
}
}

int main(){
  int x1, x2, x3;
  int y1, y2, y3;
  int z1, z2, z3;

  printf("请输入小明的三项成绩（顺序为A B C,以一个空格为间隔）：");
  scanf("%d %d %d", &x1, &x2, &x3);
  printf("请输入小强的三项成绩（顺序为A B C,以一个空格为间隔）：");
  scanf("%d %d %d", &y1, &y2, &y3);
  printf("请输入小林的三项成绩（顺序为A B C,以一个空格为间隔）：");
  scanf("%d %d %d", &z1, &z2, &z3);
  int p1,f1,zhi;
  int p2,f2,zh2;
  int p3,f3,zh3;
  calcpersonscore(p1,f1,zh1,x1,x2,x3);
  calcpersonscore(p2,f2,zh2,y1,y2,y3);
  calcpersonscore(p3,f3,zh3,z1,z2,z3);
  results(zh1,zh2,zh3);
  return 0;
}
