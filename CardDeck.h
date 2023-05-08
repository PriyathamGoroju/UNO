#include <bits/stdc++.h>
#ifndef CARDDECK_H
#define CARDDECK_H
#include "Card.h"
using namespace std;
class CardDeck
{
private:
    /* data */
    vector<string> colors;
    int noOfColors;
    int noOfNumbers;
    stack<Card*> drawPile;
    stack<Card*> discardPile;

public:
    CardDeck();
    CardDeck(int,int);
    void shuffle(int);
    Card* getCard();
    Card* getTopCard();
    void putCardInDrawPile( Card*);
    void putCardInDiscardPile( Card*);
    vector<string> getColors();
    ~CardDeck();
};
#endif

