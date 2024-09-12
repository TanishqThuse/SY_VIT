#include<stdio.h>
void game()
{   int key;
    printf("enter the key\n\n");
    scanf("%d",&key);
    
    if(key==1)
    {
        printf("X\n");
    }
    else
    {
        printf("O\n");
    }
    
}

void f1()
{   int key,c,r;
     printf("F1 will play\n");
    printf("Enter the Values of row and column\n");
    printf("Row:\n");
    scanf("%d",&r);
    if(r>3)
    {
        printf("Invalid\n");
    
    }
    printf("Column:\n");
    scanf("%d",&c);
    if(c>3)
    {
        printf("Invalid\nEnter again\n");
        f1();
    }
    game();
}

void f2()
{   int key,c,r;
    printf("F2 will play\n");
    printf("Enter the Values of row and column\n");
    printf("Row:\n");
    scanf("%d",&r);
    if(r>3)
    {
        printf("Invalid\n Enter again\n");
        f2();
     }
    printf("Column:\n");
    scanf("%d",&c);
    if(c>3)
    {
        printf("Invalid\nEnter again\n");
    }
    game();
}
void winner()
{
  
}
void board()
{
    int brd[3][3]={'  ','  ','  ',
                   '  ','  ','  ',
                   '  ','  ','  '}
}
int main()
{
    int n,key,x,y;
    char a,b;
    printf("Instructions:\nPress 1 for X\nOnly 2 frds can play a game at a time\n");
    printf("    Row\n");
    printf("col 1     2      3\n\n");
    printf("    2  |       |\n\n");
    printf("    3  |       |\n\n");
    // printf("Enter your names");
    // scanf("%c\n",&a);
    // scanf("%c\n",&b);
    // printf("%c will play 1st Round\n",a);
    // printf("%c will play 2nd round\n",b);
    //row_column(x,y);
    while(1)
    {
    f1();
    f2();
    }


    //game();
    
    return 0;
}