#include<bits/stdc++.h>

#ifndef CARD_H
#define CARD_H
using namespace  std;
class Card
{
private:
    string color;
    int number;
    bool plus2;
    bool plus4;
    bool wild;
    bool reverse;
    bool skip;

public:
    Card();
    Card(string,int,bool,bool,bool,bool,bool);
    string getColor();
    int getNumber();
    bool isPlus2();
    bool isPlus4();
    bool isWild();
    bool isReverse();
    bool isSkip();
    bool isPowerCard();
    void show();
    void setColor(string);
    ~Card();
};
#endif
