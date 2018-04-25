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
public:
    bool goal;
    bool search;
    double dist;
    node *next[4];//ENWS
}node;

list<int> Astar_cnt,Astar_mem;
list<node*> que;
node maze[99][99];
bool desc(node* a,node* b){
    return a->dist < b->dist;
}
void Astar(node *root){
    if(!que.empty())
        que.pop_front();
    if(root->goal){
        Astar_cnt.push_back(cnt);
        Astar_mem.push_back(max_memory);
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
    que.sort(desc);
    if(que.size()>max_memory)
        max_memory=que.size();
    if(!que.empty())
        Astar(*que.begin());
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
                maze[i-1][j-1].dist=pow((99-i),2)+pow((99-j),2);
            }
        }
        ifs.close();
        max_memory=0;
        cnt=0;
        Astar(&maze[0][0]);
    }
    cout<<"min"<<endl;
    cout<<"cnt:"<<*min_element(Astar_cnt.begin(),Astar_cnt.end())<<endl;
    cout<<"mem:"<<*min_element(Astar_mem.begin(),Astar_mem.end())<<endl;
    cout<<"max"<<endl;
    cout<<"cnt:"<<*max_element(Astar_cnt.begin(),Astar_cnt.end())<<endl;
    cout<<"mem:"<<*max_element(Astar_mem.begin(),Astar_mem.end())<<endl;
    cout<<"ave"<<endl;
    cout<<"cnt:"<<accumulate(Astar_cnt.begin(),Astar_cnt.end(),0)/Astar_cnt.size()<<endl;
    cout<<"mem:"<<accumulate(Astar_mem.begin(),Astar_mem.end(),0)/Astar_mem.size()<<endl;
}