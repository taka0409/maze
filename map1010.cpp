#include<iostream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
int count=0,max_memory=0;
typedef struct node{
    bool goal;
    node *next[4];//ENWS
    bool search;
}node;
queue<node*> que;
stack<node*> st;
void search_depth(node *root){
    if(!st.empty())
        st.pop();
    count++;
    if(root->goal){
        cout<<"count "<<count<<" max_memory "<<max_memory<<endl;
        return;
    }
    root->search=true;
    for(int i=0;i<4;i++){
        if(root->next[i]!=NULL && !root->next[i]->search){
            st.push(root->next[i]);
        }
    }
    if(st.size()>max_memory)
        max_memory=st.size();
    if(!st.empty())
        search_depth(st.top());
}
void search_width(node *root){
    if(!que.empty())
        que.pop();    
    count++;
    if(root->goal){
        cout<<"count "<<count<<" max_memory "<<max_memory<<endl;
        return;
    }
    root->search=true;
    for(int i=0;i<4;i++)
        if(root->next[i]!=NULL && !root->next[i]->search)
                que.push(root->next[i]);
    if(que.size()>max_memory)
        max_memory=que.size();
    if(!que.empty())
        search_width(que.front());
}
int main(){
    double pi=M_PI/2;
    char map[11][12];
    int i,j,k;
    for(i=0;i<11;i++)
        for(j=0;j<12;j++)
            scanf("%c",&map[i][j]);
    /*for(i=0;i<11;i++){
        for(j=0;j<12;j++)
            printf("%c",map[i][j]);
    }*/
    node node[9][9];
    for(i=1;i<10;i++){
        for(j=1;j<10;j++){
            if(map[i][j]=='1')
                continue;
            for(k=0;k<4;k++){
                if(map[i-(int)sin(pi*k)][j+(int)cos(pi*k)]=='0')
                    node[i-1][j-1].next[k]=&node[i-1-(int)sin(pi*k)][j-1+(int)cos(pi*k)];
                else
                    node[i-1][j-1].next[k]=NULL;
            }
            if(i==9 && j==9)
                node[i-1][j-1].goal=true;
            else
                node[i-1][j-1].goal=false;
            node[i-1][j-1].search=false;
        }
    }
    search_width(&node[0][0]);
    max_memory=0;
    count=0;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            node[i][j].search=false;
    search_depth(&node[0][0]);
}
