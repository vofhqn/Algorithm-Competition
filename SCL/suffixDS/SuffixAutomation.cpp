#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

const int N = 300000 + 10;
const int Mod = 1000000007;


struct State{
    State *son[29], *parent;
    int length, count[3];
    
    State(){
        length = 0;
        for(int i = 0; i < 3; i ++)
            count[i] = 0;
        parent = NULL;
        for(int i = 0; i < 29; i ++)
            son[i] = NULL;
    }
    State(int length): length(length){
        for(int i = 0; i < 3; i ++)
            count[i] = 0;
        parent = NULL;
        for(int i = 0; i < 29; i ++)
            son[i] = NULL;
    }
    
    bool operator < (State const &other) const{
        return length > other.length;
    }
};

bool cmp(State *a, State *b){
    return (*a) < (*b);
}
struct SAM{
    vector<State* > states;
    State *start;
    State *tail;
    
    SAM(){
        tail = new State(0);
        start = tail;
        states.push_back(start);
    }
    
    void extend(int ch){
        State *pointer = tail;
        State *ntail = new State(pointer -> length + 1);
        states.push_back(ntail);
        while(pointer != NULL && pointer -> son[ch] == NULL){
            pointer -> son[ch] = ntail;
            pointer = pointer -> parent;
        }
        
        if(pointer == NULL){
            ntail -> parent = start;
        }else{  
            State *pivot = pointer -> son[ch];
            if(pivot -> length == pointer -> length + 1){
                ntail -> parent = pivot;
            }else{
                
                State *npivot = new State(pointer -> length + 1);
                states.push_back(npivot);
                memcpy(npivot -> son, pivot -> son, sizeof (pivot -> son));
                npivot -> parent = pivot -> parent;
                ntail -> parent = pivot -> parent = npivot;
            
                while(pointer != NULL && pointer -> son[ch] == pivot){
                    pointer -> son[ch] = npivot;
                    pointer = pointer -> parent;
                }
            }
        }
        tail = ntail;
    }
}sam;

