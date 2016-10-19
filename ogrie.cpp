#include "ogrie.h"

//FOR FILE
#include <fstream>
#include <iostream>
#include <stdlib.h>

Ogrie::Ogrie()
{
}

//25.03.2016 12:42
void OgrieParty::createByRangedValues(std::stack<int> currentValues, Ogrie currentRezult, unsigned short nextElement, unsigned short N){
    if (currentValues.empty() && nextElement > N){
        this->push_back(currentRezult);
    }else{
        if (currentValues.empty()){
            currentRezult.addAction(1);
            currentValues.push(nextElement);
            createByRangedValues(currentValues, currentRezult, nextElement+1, N);
        }else if (nextElement > N && !currentValues.empty()){
            currentRezult.addAction(0);
            currentRezult.addRezult(currentValues.top());
            currentValues.pop();
            createByRangedValues(currentValues, currentRezult, nextElement, N);
        }else{//TWO WAYS
            currentRezult.addAction(1);
            currentValues.push(nextElement);
            createByRangedValues(currentValues, currentRezult, nextElement+1, N);

            //GET NORMAL STATE
            currentValues.pop();
            currentRezult.deleteAction();

            currentRezult.addAction(0);
            currentRezult.addRezult(currentValues.top());
            currentValues.pop();
            createByRangedValues(currentValues, currentRezult, nextElement, N);

        }

    }
}

void OgrieParty::createByRangedValues(std::deque<int> currentValues, Ogrie currentRezult, unsigned short nextElement, unsigned short N){
    if (currentValues.empty() && nextElement > N){
        this->push_back(currentRezult);
    }else{
        if (currentValues.empty()){
            currentRezult.addAction(3);
            currentValues.push_back(nextElement);
            createByRangedValues(currentValues, currentRezult, nextElement+1, N);
        }else if (nextElement > N && !currentValues.empty()){

            //POP FRONT
            int x = currentValues.front();
            currentRezult.addAction(0);
            currentRezult.addRezult(x);
            currentValues.pop_front();
            createByRangedValues(currentValues, currentRezult, nextElement, N);

            //GET NORMAL STATE
            currentValues.push_front(x);
            currentRezult.deleteAction();
            currentRezult.deleteRezult();

            //POP BACK
            x = currentValues.back();
            currentRezult.addAction(2);
            currentRezult.addRezult(x);
            currentValues.pop_back();
            createByRangedValues(currentValues, currentRezult, nextElement, N);



        }else{//4 WAYS
            //POP FRONT 0
            int x = currentValues.front();
            currentRezult.addAction(0);
            currentRezult.addRezult(x);
            currentValues.pop_front();
            createByRangedValues(currentValues, currentRezult, nextElement, N);

            //GET NORMAL STATE
            currentValues.push_front(x);
            currentRezult.deleteAction();
            currentRezult.deleteRezult();

            //POP BACK 2
            x = currentValues.back();
            currentRezult.addAction(2);
            currentRezult.addRezult(x);
            currentValues.pop_back();
            createByRangedValues(currentValues, currentRezult, nextElement, N);

            //GET NORMAL STATE
            currentValues.push_back(x);
            currentRezult.deleteAction();
            currentRezult.deleteRezult();

            //PUSH FRONT 1
            currentRezult.addAction(1);
            currentValues.push_front(nextElement);
            createByRangedValues(currentValues, currentRezult, nextElement+1, N);

            //GET NORMAL
            currentValues.pop_front();
            currentRezult.deleteAction();

            //PUSH BACK 3
            currentRezult.addAction(3);
            currentValues.push_back(nextElement);
            createByRangedValues(currentValues, currentRezult, nextElement+1, N);
        }

    }
}

std::string Ogrie::toString(int){
    std::string strRezult;
    char number[8];
    int min = rezult[0];
    for (unsigned short i = 0; i < rezult.size(); ++i){
        itoa(rezult[i], number, 10);
        strRezult+=std::string(number) + ' ';
        if (min > rezult[i]){
            min = rezult[i];
        }
    }
    strRezult+=": ";
    for ( unsigned short i = 0; i < actions.size(); ++i){
        switch(actions[i]){
        case 0:
            strRezult+="pop_front();";
            break;
        case 1:
            strRezult+="push_front(";
            itoa(min++, number, 10);
            strRezult+=number;
            strRezult+=");";
            break;
        case 2:
            strRezult+="pop_back();";
            break;
        case 3:
            strRezult+="push_back(";
            itoa(min++, number, 10);
            strRezult+=number;
            strRezult+=");";
            break;

        }
    }
    return strRezult;
}

std::string Ogrie::toString(){
    std::string strRezult;
    char number[8];
    int min = rezult[0];
    for (unsigned short i = 0; i < rezult.size(); ++i){
        itoa(rezult[i], number, 10);
        strRezult+=std::string(number) + ' ';
        if (min > rezult[i]){
            min = rezult[i];
        }
    }
    return strRezult;
}
/*
void OgrieParty::toFile(std::string fileName){
    std::ofstream file(fileName);
    for (unsigned int i = 0; i < size(); ++i){
        file<<'[';
        file<<i;
        file<<']';
        file<<(*this)[i].toString();
        file<<'\n';
    }
}
*/
