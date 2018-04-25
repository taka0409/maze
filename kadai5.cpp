#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<list>
#include<algorithm>
#include <numeric>
using namespace std;
int cnt,max_memory;
typedef struct node{
    bool goal;
    bool search;
    node *next[4];//ENWS
}node;
list <node*> que,st;
list<int> D_cnt,D_mem,B_cnt,B_mem;
node maze[99][99];

void DFS(node *root){
    if(!st.empty())
        st.pop_back();
    if(root->goal){
        D_cnt.push_back(cnt);
        D_mem.push_back(max_memory);
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
        B_cnt.push_back(cnt);
        B_mem.push_back(max_memory);
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
    char map[101][102];
    int i,j,k,n,num;
    string buf,fname;
    for(n=0;n<100;n++){
        fname="./8024/map"+to_string(n);
        ifstream ifs;
        ifs.open(fname);
        for(i=0;i<101;i++){
            getline(ifs,buf);
            buf.copy(map[i],101);
        }
        for(i=1;i<100;i++){
            for(j=1;j<100;j++){
                if(map[i][j]=='1')
                    continue;
                for(k=0;k<4;k++){
                    if(map[i-(int)sin(pi*k)][j+(int)cos(pi*k)]=='0')
                        maze[i-1][j-1].next[k]=&maze[i-1-(int)sin(pi*k)][j-1+(int)cos(pi*k)];
                    else
                        maze[i-1][j-1].next[k]=NULL;
                }
                if(i==99 && j==99)
                    maze[i-1][j-1].goal=true;
                else
                    maze[i-1][j-1].goal=false;
                maze[i-1][j-1].search=false;
            }
        }
        ifs.close();
        max_memory=0;
        cnt=0;
        BFS(&maze[0][0]);
        max_memory=0;
        cnt=0;
        for(i=0;i<99;i++)
            for(j=0;j<99;j++)
                maze[i][j].search=false;
        DFS(&maze[0][0]);
    }
    cout<<"min"<<endl;
    cout<<"D_cnt:"<<*min_element(D_cnt.begin(),D_cnt.end())<<endl;
    cout<<"B_cnt:"<<*min_element(B_cnt.begin(),B_cnt.end())<<endl;
    cout<<"D_mem:"<<*min_element(D_mem.begin(),D_mem.end())<<endl;
    cout<<"B_mem:"<<*min_element(B_mem.begin(),B_mem.end())<<endl;
    cout<<"max"<<endl;
    cout<<"D_cnt:"<<*max_element(D_cnt.begin(),D_cnt.end())<<endl;
    cout<<"B_cnt:"<<*max_element(B_cnt.begin(),B_cnt.end())<<endl;
    cout<<"D_mem:"<<*max_element(D_mem.begin(),D_mem.end())<<endl;
    cout<<"B_mem:"<<*max_element(B_mem.begin(),B_mem.end())<<endl;
    cout<<"ave"<<endl;
    cout<<"D_cnt:"<<accumulate(D_cnt.begin(),D_cnt.end(),0)/D_cnt.size()<<endl;
    cout<<"B_cnt:"<<accumulate(B_cnt.begin(),B_cnt.end(),0)/B_cnt.size()<<endl;
    cout<<"D_mem:"<<accumulate(D_mem.begin(),D_mem.end(),0)/D_mem.size()<<endl;
    cout<<"B_mem:"<<accumulate(B_mem.begin(),B_mem.end(),0)/B_mem.size()<<endl;
}