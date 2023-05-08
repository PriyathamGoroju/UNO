#include <bits/stdc++.h>
#include<random>
#include "CardDeck.h"

using namespace std;

//colors are defined inside this class.

CardDeck::CardDeck(/* args */)
{
    colors={"Blue","Green","Red","Yellow","Orange","Violet","Indigo"};
}

/*
    input: no. of card numbers and no. of colors
    gives deck of cards with given card numbers and colors
*/

CardDeck::CardDeck(int inoOfNumbers,int inoOfColors)
{
    noOfColors=inoOfColors;
    noOfNumbers=inoOfNumbers;
    colors={"Blue","Green","Red","Yellow","Orange","Violet","Indigo"};

// creates two number cards for each color for given numbers and add to DRAWPile.

    for(int i=0;i<noOfColors;i++){
        string color=colors[i];
        for(int j=1;j<=noOfNumbers;j++){
            drawPile.push(new Card(colors[i],j,false,false,false,false,false));
            drawPile.push(new Card(colors[i],j,false,false,false,false,false));
        }

    //there is only one '0' card for every color.
        drawPile.push(new Card(colors[i],0,false,false,false,false,false));

    //adds two +2 cards for every color to DRAWPile.
        drawPile.push(new Card(colors[i],-1,true,false,false,false,false));
        drawPile.push(new Card(colors[i],-1,true,false,false,false,false));

    //reverse cards
        drawPile.push(new Card(colors[i],-1,false,false,false,true,false));
        drawPile.push(new Card(colors[i],-1,false,false,false,true,false));

    //skip cards
        drawPile.push(new Card(colors[i],-1,false,false,false,false,true));
        drawPile.push(new Card(colors[i],-1,false,false,false,false,true));

    //wild card
        drawPile.push(new Card("NULL",-1,false,false,true,false,false));

    //+4 card
        drawPile.push(new Card("NULL",-1,false,true,false,false,false));
    }
    cout<<"Card Deck Initialised"<<endl;
}
/*
    input: no. of times to shuffle
    shuffles the whole card deck
*/
void CardDeck::shuffle(int numberOfTimes){

    Card* topCard=NULL;

    if(!discardPile.empty()){
        topCard=discardPile.top();
        discardPile.pop();
    }

//adding cards to vector
    vector<Card*> cards;
    while(!discardPile.empty()){
        cards.push_back(discardPile.top());
        discardPile.pop();
    }
    while(!drawPile.empty()){
        cards.push_back(drawPile.top());
        drawPile.pop();
    }

//shuffling cards
    std::random_device rd;
    std::shuffle(cards.begin(),cards.end(),rd);

//adding cards to DISCARDPile
    if(topCard){
        discardPile.push(topCard);
    }
    for(auto card:cards){
        drawPile.push(card);
    }
    cout<<"Cards Shuffled 🔀"<<endl;
}

//Gives top card for DRAWPile
Card* CardDeck::getCard(){
    if(drawPile.empty()){
        shuffle(10000);
    }
    Card* topCard= drawPile.top();
    drawPile.pop();
    return topCard;
}

//gets top card for DISCARDPile
Card* CardDeck::getTopCard(){
    if(discardPile.empty()){
        return NULL;
    }
    
    return discardPile.top();
}

/*  input : card
    puts card in DRAWPile   */
  
void CardDeck::putCardInDrawPile(Card* card){
    drawPile.push(card);

}

/*  input : card
    puts card in DISCARDPile    */

void CardDeck::putCardInDiscardPile(Card* card){
    discardPile.push(card);
}
vector<string> CardDeck::getColors(){
    vector<string> ans;
    for(int i=0;i<noOfColors;i++){
        ans.push_back(colors[i]);
    }
    return ans;
}

CardDeck::~CardDeck()
{
    while(!drawPile.empty()){
        Card* t=drawPile.top();
        drawPile.pop();
        delete t;
    }
    while(!discardPile.empty()){
        Card* t=discardPile.top();
        discardPile.pop();
        delete t;
    }
}
