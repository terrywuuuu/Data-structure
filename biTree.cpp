#include <iostream>
#include <string>

using namespace std;

void Input(string &T,string &mode){
    string input;

    while(getline(cin,input)){
        if(input=="postfix" || input=="prefix" || input=="infix"){
            mode=input;
            break;
        }
        else{
            for(int i=0;i<input.length();i++){
                if(input[i]==' '){
                    continue;
                }
                else{
                    T+=input[i];
                }
            }

            T+='/';
        }
    }
}

void findAllNode(string T,string &node){
    for(int i=0;i<T.length();i++){
        if(T[i]=='/'){
            continue;
        }

        size_t ptr=node.find(T[i]);

        if(ptr==string::npos){
            node.push_back(T[i]);
        }
    }

    for(int i=0;i<node.length();i++){
        for(int j=i+1;j<node.length();j++){
            if(node[j]<node[i]){
                char tmp=node[i];
                node[i]=node[j];
                node[j]=tmp;
            }
        }
    }

    cout<<node<<endl;
}

void Solve(string T,string node,string &BT){
    bool exist=false;

    for(int i=0;i<node.length();i++){
        BT+=node[i];

        for(int j=0;j<T.length();j++){
            if(T[j]==node[i] && (T[j-1]=='/' || j==0) && T[j+1]!='/'){
                BT+=T[j+1];
                exist=true;
                break;
            }
        }

        if(!exist){
            BT+='0';
        }
        else{
            exist=false;
        }

        for(int j=0;j<T.length();j++){
            if(T[j]==node[i] && T[j-1]!='/' && j!=0 && T[j+1]!='/'){
                BT+=T[j+1];
                exist=true;
                break;
            }
        }

        if(!exist){
            BT+='0';
        }
        else{
            exist=false;
        }

        BT+='/';
    }
}

int findNode(char target,string BT){
    for(int i=0;i<BT.length();i++){
        if(BT[i]==target && (i==0 || BT[i-1]=='/')){
            return i;
        }
    }
}

void Traversal(string BT,string mode,int node,string &tra){
    if(mode=="postfix"){
        if(BT[node+1]!='0'){
            int pos=findNode(BT[node+1],BT);
            Traversal(BT,mode,pos,tra);
        }

        if(BT[node+2]!='0'){
            int pos=findNode(BT[node+2],BT);
            Traversal(BT,mode,pos,tra);
        }

        tra+=BT[node];
        return;
    }
    else if(mode=="prefix"){
        tra+=BT[node];

        if(BT[node+1]!='0'){
            int pos=findNode(BT[node+1],BT);
            Traversal(BT,mode,pos,tra);
        }

        if(BT[node+2]!='0'){
            int pos=findNode(BT[node+2],BT);
            Traversal(BT,mode,pos,tra);
        }

        return;
    }
    else if(mode=="infix"){
        if(BT[node+1]!='0'){
            int pos=findNode(BT[node+1],BT);
            Traversal(BT,mode,pos,tra);
        }

        tra+=BT[node];

        if(BT[node+2]!='0'){
            int pos=findNode(BT[node+2],BT);
            Traversal(BT,mode,pos,tra);
        }

        return;
    }
}

int main(){
    string tree;  // Input tree
    string mode;  // Output mode : postfix, prefix, infix
    string allNode;  // All node and sort
    string Btree;  // Binary tree
    string traversal;

    Input(tree,mode);
    findAllNode(tree,allNode);

    Solve(tree,allNode,Btree);
    Traversal(Btree,mode,0,traversal);

    cout<<traversal;
}