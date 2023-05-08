#include <bits/stdc++.h>
#include"Card.h"

/*
This Class provides different attributes for a card.
cards are divided into two groups 'numbers' and 'Power' cards.
Power cards contain +2,+4,skip,reverse,wild cards.
All the numerical cards are numbers cards.
Every card contains color except for wild and +4 cards.
*/

Card::Card()
{
    color;
    number=0;
    plus2=false;
    plus4=false;
    wild=false;
    reverse=false;
    skip=false;
}
Card::Card(std::string inputColor,int num,bool isPlusTwo,bool isPlusFour,bool isWild,bool isReverse,bool isSkip)
{
    color=inputColor;
    number=num;
    plus2=isPlusTwo;
    plus4=isPlusFour;
    wild=isWild;
    reverse=isReverse;
    skip=isSkip;
}
bool Card::isPlus2(){
    return plus2;
}
bool Card::isPlus4(){
    return plus4;
}
bool Card::isWild(){
    return wild;
}
bool Card::isReverse(){
    return reverse;
}
bool Card::isSkip(){
    return skip;
}

//returns if the card is a power card.

bool Card::isPowerCard(){
    return plus2||plus4||reverse||skip||wild;
}

/*
    input: color 
    set the color of a card
*/
void Card::setColor(string s){
    color=s;
}
string Card::getColor(){
    return color;
}
int Card::getNumber(){
    return number;
}
void Card::show(){
    if(plus2){
        cout<<"["<<color<<","<<"+2"<<"]";
    } 
    else if(plus4){
        cout<<"["<<color<<","<<"+4"<<"]";
    } 
    else if(wild){
        cout<<"["<<color<<","<<"Wild"<<"]"; 
    } 
    else if(reverse){
        cout<<"["<<color<<","<<"Reverse"<<"]";
    } 
    else if(skip){
        cout<<"["<<color<<","<<"Skip"<<"]";
    } 
    else {
        cout<<"["<<color<<","<<number<<"]";
    } 
}
Card::~Card()
{

}
