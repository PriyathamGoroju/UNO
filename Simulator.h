#include <bits/stdc++.h>
#ifndef SIMULATOR_H
#define SIMULATOR_H
#include"CardDeck.h"
#include"Player.h"
using namespace std;
class Simulator
{
private:
    vector<Player*> players;
    CardDeck* cardDeck;
public:
    Simulator();
    Simulator(int,int,int);
    void simulateManually();
    void simulateAutomatically();

    void distributeCards(int);
    int reversePlayers(int);
    void giveCards(Player*,int);
    bool CheckPlayerWon(Player*,string );
    int findStartingPlayerIndex(Card*,string);
    ~Simulator();
};
#endif
