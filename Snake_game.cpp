#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<fstream>
using namespace std;
struct food{
    int x;
    int y;
    char value;
};
struct poison{
    int x;
    int y;
    char value;
};
struct snake{
    int x;
    int y;
    char value;
    snake *next;
};
class linkedlist{
public:
    snake *head=NULL;
    snake *create_node(int a,int b,char ch){
    snake *temp;
    temp=new snake();
    temp->x=a;
    temp->y=b;
    temp->value=ch;
}
void insert_node(int a,int b,char ch){
    snake *ptr,*temp;
    int x=a;
    int y=b;
    char c=ch;
    ptr=create_node(x,y,c);
    temp=head;
    if(head==NULL){
        head=ptr;
    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;
         }
        temp->next=ptr;
        ptr->next=NULL;
        }
        //board[x][y]=ch;
}
void print(food *f,poison *p){
    int maxr=29,maxc=29,minr=0,minc=0;
    char board[maxr][maxc]={' '};
    int i,j;
    snake *temp=head;
    while(temp!=NULL){
        board[temp->x][temp->y]=temp->value;
        temp=temp->next;
    }
    board[f->x][f->y]=f->value;
    board[p->x][p->y]=p->value;
    for(i=0;i<=maxr;i++){
            board[i][0]='\xB3';
            board[i][maxr]='\xB3';
        for(j=0;j<=maxc;j++){
                board[0][j]='\xC4';
                board[maxc][j]='\xC4';
            cout<<board[i][j];
        }
        cout<<endl;
    }
}
void shift(snake *temp,int r,int c){
    int r1,c1;
    while(temp!=NULL){
        r1=temp->x;
        c1=temp->y;
        //board[r1][c1]=' ';
        temp->x=r;
        temp->y=c;
        //board[temp->x][temp->y]=temp->value;
        temp=temp->next;
        r=r1;
        c=c1;
    }
    //board[r1][c1]=' ';
}
void eatfood(food *f){
    snake *temp=head;
    Beep(573,200);
    while(temp->next!=NULL){
        temp=temp->next;
    }
    snake *n;
    n=create_node(temp->x,temp->y+1,'T');
    temp->value='~';
    temp->next=n;
    /*board[temp->x][temp->y+1]='T';
    board[temp->x][temp->y]=temp->value;*/
    generate_food(f);
}
void generate_food(food *f){
    int r,c,a;
    static int l=5;
    r=((++r)+(l--))%(28-2+1)+2;
    c=((c--)-(++l))%(28-2+1)+2;
    l=(++l)+(l--);
    //cout<<"f"<<r<<" "<<c<<endl;
    a=check(r,c);
    if(a==1)
        generate_food(f);
    else{
        f->x=r;
        f->y=c;
        //board[r][c]=f->value;
    }
}
int check(int r,int c){
    snake *temp=head;
    int flag=0;
    while(temp!=NULL){
        if(r==temp->x&&c==temp->y){
            flag=1;
            break;
        }
        else{
            flag=0;
        }
        temp=temp->next;
    }
    if(flag==1)
        return 1;
    else
        return 0;
}
void selfbite(){
    snake *temp=head;
    temp=temp->next;
    int flag=0;
    while(temp!=NULL){
        if(head->x==temp->x&&head->y==temp->y){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1)
            exit(flag);
}
void left(int maxc){
    snake *temp;
    temp=head;
    if(temp->y<=temp->next->y||temp->y==maxc-1){
        int r,c,r1,c1,flag=0;
       r=temp->x;
       c=temp->y;
       if(c-1<=0){
        temp->y=maxc-1;
       }
       else{
         temp->y=(temp->y)-1;
       }
         //board[temp->x][temp->y]=temp->value;
         temp=temp->next;
         shift(temp,r,c);

         selfbite();

    }

}
void right(int minc,int maxc){
    snake *temp;
    temp=head;
    if(temp->y>=temp->next->y||temp->y==minc+1){
    int r,c,r1,c1;
       r=temp->x;
       c=temp->y;
       if(c+1==maxc){
        temp->y=minc+1;
       }
       else{
       temp->y=(temp->y)+1;
       }
       //board[temp->x][temp->y]=temp->value;
       temp=temp->next;
       shift(temp,r,c);

       selfbite();
    }
}
void top(int maxr){
    snake *temp;
    temp=head;
    if(temp->x<=temp->next->x||temp->x==maxr-1){
    int r,c,r1,c1;
       r=temp->x;
       c=temp->y;
       if(r-1==0){
        temp->x=maxr-1;
       }
       else{
       temp->x=(temp->x)-1;
       }
       //board[temp->x][temp->y]=temp->value;
       temp=temp->next;
       shift(temp,r,c);

       selfbite();
    }
}
void bottom(int minr,int maxr){
    snake *temp;
    temp=head;
    if(temp->x>=temp->next->x||temp->x==minr+1){
    int r,c,r1,c1;
       r=temp->x;
       c=temp->y;
       if(r+1==maxr){
        temp->x=minr+1;
       }
       else{
       temp->x=(temp->x)+1;
       }
       //board[temp->x][temp->y]=temp->value;
       temp=temp->next;
       shift(temp,r,c);

       selfbite();
    }
}
void poison_eaten(poison *p){
    snake *temp=head;
    snake *t=head;
    Beep(573,200);
    int c=0;
    while(temp!=NULL){
        c++;
        temp=temp->next;
    }
    if(c==2)
        exit(c);
    else{
    snake *prev;
    while(t->next!=NULL){
        prev=t;
        t=t->next;
    }
    //board[prev->x][prev->y]='T';
    prev->value=t->value;
    prev->next=NULL;
    //board[t->x][t->y]=' ';
    free(t);
    generate_poison(p);
    }
}
void generate_poison(poison *p){
    int r,c,a;
    static int l=5;
    r=((++r)+(l--))%(28-2+1)+2;
    c=((c--)-(++l))%(28-2+1)+2;
    l=(++l)+(l--);
    //cout<<"p"<<r<<" "<<c<<endl;
    a=check(r,c);
    if(a==1)
        generate_poison(p);
    else{
    //board[r][c]=p.value;
    p->x=r;
    p->y=c;
    }
}
void save_game(food *f,poison *p){
    FILE *fp;
    fp=fopen("Snake.txt","w");
    fprintf(fp,"%d,%d,%c$",f->x,f->y,f->value);
    snake *temp=head;
    fprintf(fp,"%d,%d,%c",temp->x,temp->y,temp->value);
    temp=temp->next;
    while(temp!=NULL){
        fprintf(fp,",%d,%d,%c",temp->x,temp->y,temp->value);
        temp=temp->next;
    }
    fprintf(fp,"$");
    fprintf(fp,"%d,%d,%c",p->x,p->y,p->value);
    fclose(fp);
}
void previous_game(food *f,poison *p){
    int j=0,i=0,n=0;
    int x,y;
    char ch;
    string str;
    ifstream infile;
    infile.open("Snake.txt");
    getline(infile,str);
    ifstream f2;
    f2.open("Snake.txt");
    while(str[i]!=','){
            n=n*10+(str[i]-'0');
            i++;
        }
    f->x=n;
    i++;
    n=0;
    while(str[i]!=','){
            n=n*10+(str[i]-'0');
            i++;
        }
    f->y=n;
    f->value=str[++i];
    i=i+2;
    //cout<<"head"<<f->x<<" "<<f->y<<" "<<f->value<<endl;
    while(j!=1){
        int n=0;
        while(str[i]!=','){
            n=n*10+(str[i]-'0');
            i++;
        }
        x=n;
        n=0;
        i++;
        while(str[i]!=','){
            n=n*10+(str[i]-'0');
            i++;
        }
        y=n;
        i++;
        ch=str[i];
        i=i+1;
        if(str[i]=='$')
            j=1;
        else
            i++;
        //cout<<x<<y<<ch<<endl;
        insert_node(x,y,ch);
    }
    cout<<str[i]<<endl;
    i++;
    n=0;
    while(str[i]!=','){
            n=n*10+(str[i]-'0');
            i++;
        }
    p->x=n;
    i++;
    n=0;
    while(str[i]!=','){
            n=n*10+(str[i]-'0');
            i++;
        }
    p->y=n;
    i++;
    //cout<<"***"<<str[i];
    p->value=str[i];
    cout<<p->x<<p->y<<p->value<<endl;
    infile.close();
    print(f,p);
}
void initial_values(food *f,poison *p){
    f->x=25;
    f->y=18;
    f->value='+';
    p->x=27;
    p->y=11;
    p->value='-';
}
};

int main(){
    char opt1;
    //system("Color 7E");
    cout<<"Snake Game"<<endl;
    cout<<"Press n for starting a new game and p for opening previous game"<<endl;
    cin>>opt1;
    food *f=(food*)malloc(sizeof(food));
    poison *p=(poison*)malloc(sizeof(poison));
    int maxr=29,maxc=29,minr=0,minc=0;
    linkedlist s;
    if(opt1=='n'||opt1=='N'){
        s.initial_values(f,p);
        int i;
        int x[4]={9,9,9,9};
        int y[4]={4,5,6,7};
        char ch[4]={'H','~','~','T'};
        for(i=0;i<4;i++){
            s.insert_node(x[i],y[i],ch[i]);
        }
        s.print(f,p);
    }
    else if(opt1=='p'||opt1=='P'){
        s.previous_game(f,p);
        cout<<"Here"<<endl;

    }
    cout<<"Enter a for left, d for right, w for top, s for bottom,q for quit"<<endl;
    char c;
    c=getch();
    Sleep(100);
    while(c!='1'){
        if(c=='a'){
            if(s.head->x==f->x&&s.head->y==f->y){
                s.eatfood(f);
            }
            else if(s.head->x==p->x&&s.head->y==p->y){
                s.poison_eaten(p);
            }
            else{
               s.left(maxc);
            }

        }
        else if(c=='d'){
            if(s.head->x==f->x&&s.head->y==f->y){
                s.eatfood(f);
            }
            else if(s.head->x==p->x&&s.head->y==p->y){
                s.poison_eaten(p);
            }
            else{
               s.right(minc,maxc);
            }

        }
        else if(c=='w'){
            if(s.head->x==f->x&&s.head->y==f->y){
                s.eatfood(f);
            }
            else if(s.head->x==p->x&&s.head->y==p->y){
                s.poison_eaten(p);
            }
            else{
               s.top(maxr);
            }

        }
        else if(c=='s'){
            if(s.head->x==f->x&&s.head->y==f->y){
                s.eatfood(f);
            }
            else if(s.head->x==p->x&&s.head->y==p->y){
                s.poison_eaten(p);
            }
            else{
               s.bottom(minr,maxr);
            }

        }
        else if(c=='q'){
            char c1;
            cout<<"Press y for saving game and n for not saving"<<endl;
            cin>>c1;
            if(c1=='y'||c1=='Y'){
                s.save_game(f,p);
                exit(1);
            }
            else if(c1=='n'||c1=='N'){
                exit(1);
            }
        }
        system("cls");
        s.print(f,p);
        if(kbhit())
        c=getch();
        Sleep(100);
    }
    return 0;
}

