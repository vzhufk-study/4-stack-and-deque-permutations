#ifndef OGRIE_H
#define OGRIE_H

#include <iostream>
#include <stack>

class Ogrie
{
    std::deque<int> actions;
    std::deque<int> rezult;
public:
    Ogrie();
    std::string toString();
    std::string toString(int);

    inline unsigned int getActionSize(){
        return actions.size();
    }

    inline int getRezult(){
        int x = rezult.front();
        rezult.pop_front();
        return x;
    }

    inline int getAction(int i){
        return actions[i];
    }

    inline int getActions(){
        int x = actions.front();
        actions.pop_front();
        return x;
    }

    inline void addAction(unsigned int a){
        actions.push_back(a);
    }

    inline void addRezult(unsigned int x){
        rezult.push_back(x);
    }

    inline void deleteAction(){
        actions.pop_back();
    }

    inline void deleteRezult(){
        rezult.pop_back();
    }
};


class OgrieParty: public std::deque<Ogrie>{
public:
    void createByRangedValues(std::stack<int>, Ogrie, unsigned short, unsigned short );
    void createByRangedValues(std::deque<int>, Ogrie, unsigned short, unsigned short );

    void toFile(std::string);
};


#endif // OGRIE_H
