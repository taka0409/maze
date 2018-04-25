#include<fstream>
#include<iostream>
#include<cmath>
#include<list>
using namespace std;
int cnt=0,max_memory=0;
typedef struct node{
    bool goal;
    node *next[4];//ENWS
    bool search;
}node;
list <node*> que,st;
void DFS(node *root){
    if(!st.empty())
        st.pop_back();
    if(root->goal){
        cout<<"count:"<<cnt<<" max_memory:"<<max_memory<<endl;
        st.clear();
        return;
    }
    root->search=true;

    //nextここから
    for(int i=0;i<4;i++){
        if(root->next[i]!=NULL && !root->next[i]->search){
            st.push_back(root->next[i]);
        }
    }
    cnt++;
    //ここまで
    
    if(st.size()>max_memory)
        max_memory=st.size();
    if(!st.empty())
        DFS(*--st.end());
}
void BFS(node *root){
    if(!que.empty())
        que.pop_front();
    if(root->goal){
        cout<<"count:"<<cnt<<" max_memory:"<<max_memory<<endl;
        que.clear();
        return;
    }
    root->search=true;

    //nextここから
    for(int i=0;i<4;i++)
        if(root->next[i]!=NULL && !root->next[i]->search)
            que.push_back(root->next[i]);
    cnt++;
    //ここまで

    if(que.size()>max_memory)
        max_memory=que.size();
    if(!que.empty())
        BFS(*que.begin());
}

int main(){
    double pi=M_PI/2;
    char map[11][12];
    int i,j,k;
    string fname="./map1010",buf;
    ifstream ifs;
    ifs.open(fname);
    //課題1ここから
    for(i=0;i<11;i++){
        getline(ifs,buf);
        buf.copy(map[i],11);
        cout<<buf<<endl;
    }
    //ここまで

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
    BFS(&node[0][0]);
    max_memory=0;
    cnt=0;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            node[i][j].search=false;
    DFS(&node[0][0]);
}
