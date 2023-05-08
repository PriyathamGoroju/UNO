#include <bits/stdc++.h>
#include "Simulator.h"
using namespace std;

Simulator::Simulator()
{
}
/*
    input: no. of players,colors and numbers
    functionality: sets the number of players and the deck of cards
*/
Simulator::Simulator(int noOfPlayers, int noOfColors, int noOfNumbers)
{
    for (int i = 0; i < noOfPlayers; i++)
    {
        players.push_back(new Player(i));
    }
    cardDeck = new CardDeck(noOfNumbers, noOfColors);
}
/*
    input: player index
    output/functionality: reverses the list of players and returns the index of the player who will be playing next. 
*/
int Simulator::reversePlayers(int idx)
{
    cout << " direction is reversed 🔁" << endl;
    cout << setfill('-') << setw(38) << '\n';

    // if no. of players is two then return the same index
    if(players.size()==2){
        return idx;
    }
    reverse(players.begin(), players.end());
    if (idx == 0)
    {
        return 0;
    }

    return players.size() - idx;
}

/*
    input: player and no. of cards
   functionality: gives the specified number of cards to the specified player
*/
void Simulator::giveCards(Player *player, int noofCards)
{
    int n = noofCards;
    while (n--)
    {
        player->takeCard(cardDeck->getCard());
    }
    if (noofCards == 1)
    {
        cout << "player With ID: " << player->getId() << " took " << noofCards << " card 😂😂" << endl;
    }
    else
    {
        cout << "player With ID: " << player->getId() << " took " << noofCards << " cards 😂😂" << endl;
    }
    cout << setfill('-') << setw(38) << '\n';
}

void Simulator::simulateManually()
{
    int noOfPlayers = players.size();
    cardDeck->shuffle(10000);               //shuffles the card deck
    distributeCards(7);                     //distribute 7 cards to each player
    Card *topCard = cardDeck->getCard();    //deals the first card if the first card is +4 draw another card from card deck

    while (topCard != NULL && topCard->isPlus4())
    {
        topCard = cardDeck->getCard();
    }
    cardDeck->putCardInDiscardPile(topCard);
    int i = findStartingPlayerIndex(cardDeck->getTopCard(), "Manual");

    //---GAME STARTS---

    while (true)
    {
        topCard = cardDeck->getTopCard();         //get top card from DISCARDPile
        Card *playedCard = players[i]->putCardManual(topCard);
        cout << "Played Card : ";
        if (playedCard)
        {
            playedCard->show();
        }
        else
            cout << "No Card Played";
        cout << endl;

        //If a player has no cards to play, they must draw a card from the DRAWPile and continue their turn.
        if (playedCard == NULL)
        {
            giveCards(players[i], 1);
            cout << "player with id : " << players[i]->getId() << " continuing turn " << endl;
            playedCard = players[i]->putCardManual(topCard);
            cout << "Played Card : ";
            if (playedCard)
                playedCard->show();
            else
                cout << "No Card Played";
            cout << endl;
        }

        //If the played card is a +4, the player is given the option of selecting the colour of the card.
        if (playedCard != NULL && playedCard->isPlus4())
        {
            cout << "player with "<< players[i % noOfPlayers]->getId() << " Played + 4️⃣" << endl;
            string chosenColor = players[i]->getColorChoice(cardDeck->getColors());
            playedCard->setColor(chosenColor);

            /*
            Ask the next-player[ players[(i + 1) % noOfPlayers] ] whether they want to challenge; if yes, the player must show their cards in hand [filtered cards].
            If there is a card that matches the colour of the top card, the challenger wins the challenge, and the player must draw 4 cards.
            If not then the challenger lose the challenge and they must draw 6 cards
            */
        
            if (players[(i + 1) % noOfPlayers]->doYouWantToChallengeManual())  //Ask the next player whether they want to challenge the use of +4.
            {
                cout << players[(i + 1) % noOfPlayers]->getId() << " challenged " << players[i]->getId() << " for use of +4 " << endl;

                //gives no.of same colored cards as the top card, if it is greater than zero then the player draws four cards.
                if (players[i]->getNoOfColorCards(topCard) > 0)             
                {
                    cout << players[(i + 1) % noOfPlayers]->getId() << " Won Challenge" << endl;
                    giveCards(players[i], 4);
                    i = (i + 1) % noOfPlayers;
                }

                //if there is no colored card same as the top card then challenger draws six cards
                else
                {
                    cout << players[(i + 1) % noOfPlayers]->getId()  << " lost challenge " << endl;
                    giveCards(players[(i + 1) % noOfPlayers], 6);
                    i = (i + 2) % noOfPlayers;
                }
            }

            //if there is no challenge then next player draws four cards and their turn is skipped.
            else
            {
                if (CheckPlayerWon(players[i],"Manual"))
                    break;
                i = (i + 1) % noOfPlayers;          //index of next player
                giveCards(players[i], 4);           //gives 4 cards to the player
                i = (i + 1) % noOfPlayers;
            }
        }

        
        // If played card is +2 then next player draws 2 cards and their turn is skipped.
        if (playedCard != NULL && playedCard->isPlus2())
        {
            cout << "player with "<< players[i % noOfPlayers]->getId() << " Played + 2️⃣" << endl;
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            i = (i + 1) % noOfPlayers;       //index of next player 
            giveCards(players[i], 2);        //gives 2 cards to the player
            i = (i + 1) % noOfPlayers;      
        }

        //If the played card is wild, then the player gets to choose the color.
        if (playedCard != NULL && playedCard->isWild())
        {
            cout << "player with "<< players[i % noOfPlayers]->getId() << " Played wild card 🔴🔵🟢🟡" << endl;
            string chosenColor = players[i]->getColorChoice(cardDeck->getColors());   //shows no.of color options to the player
            playedCard->setColor(chosenColor);                                        //chosen color is applied to the card
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            i = (i + 1) % noOfPlayers;
        }

        //If the played card is skip, then the next player is skipped.
        if (playedCard != NULL && playedCard->isSkip())
        {
            if (CheckPlayerWon(players[i],"Manual"))
                break;
            cout << "Player " << players[(i + 1) % noOfPlayers]->getId() << "'s turn Skipped 🚫" << endl;
            std::cout << std::setfill('-') << std::setw(38) << '\n';

            //The next player is skipped, and the index of the next next player is returned.
            i = (i + 2) % noOfPlayers;         
        }

        //If the played card is reverse, then the direction of play is reversed.
        if (playedCard != NULL && playedCard->isReverse())
        {
            if (CheckPlayerWon(players[i],"Manual"))        //check if the player won the game
                break;
            i = reversePlayers(i);                          //reverses the direction of the play
        }

        //checks whether the played card is an action card.
        if (playedCard != NULL && !playedCard->isPowerCard())
        {
            if (CheckPlayerWon(players[i],"Manual"))        //checks if the player won the game
                break;
            i = (i + 1) % noOfPlayers;
        }

        //If no card is played, then play continues to the next player.
        if (playedCard == NULL)
        {
            i = (i + 1) % noOfPlayers;                     //index of the next player
            std::cout << std::setfill('-') << std::setw(38) << '\n';
        }

        //set color to NULL for wild and +4 cards
        if (playedCard != NULL)
        {
            if (cardDeck->getTopCard()->isPlus4() || cardDeck->getTopCard()->isWild())
            {
                cardDeck->getTopCard()->setColor("NULL");
            }
            cardDeck->putCardInDiscardPile(playedCard);
        }
    }
}
void Simulator::simulateAutomatically()
{
    int noOfPlayers = players.size();
    cardDeck->shuffle(10000);                               //shuffles the card deck
    distributeCards(7);                                     //distribute 7 cards to each player
    Card *topCard = cardDeck->getCard();                    //deals the first card if the first card is +4 draw another card from card deck
    while (topCard != NULL && topCard->isPlus4())
    {
        topCard = cardDeck->getCard();
    }
    cardDeck->putCardInDiscardPile(topCard);            
    int i = findStartingPlayerIndex(cardDeck->getTopCard(), "Automatic");
    while (true)
    {
        topCard = cardDeck->getTopCard();                   //get top card from DISCARDPile
        Card *playedCard = players[i]->putCardAutomatically(topCard);
        cout << "Played Card : ";
        if (playedCard)
        {
            playedCard->show();
        }
        else
            cout << "No Card Played";
        cout << endl;

        //If a player has no cards to play, they must draw a card from the DRAWPile and continue their turn.
        if (playedCard == NULL)
        {
            giveCards(players[i], 1);
            cout << "player with id : " << players[i]->getId() << " continuing turn " << endl;
            playedCard = players[i]->putCardAutomatically(topCard);                     //gives the randomly picked a card from the filtered list
            cout << "Played Card : ";
            if (playedCard)
                playedCard->show();
            else
                cout << "No Card Played";
            cout << endl;
        }

        //If the played card is a +4, the player is given the option of selecting the colour of the card.
        if (playedCard != NULL && playedCard->isPlus4())
        {
            cout << "player with "<< players[i % noOfPlayers]->getId() << "  Played +4️⃣" << endl;
            string chosenColor = players[i]->getColorChoiceAutomatic(cardDeck->getColors());
            playedCard->setColor(chosenColor);

            //asks whether the next player wants to challenge
            if (players[(i + 1) % noOfPlayers]->doYouWantToChallenge())
            
            {
                cout << players[(i + 1) % noOfPlayers]->getId() << " challenged " << players[i]->getId() << " for use of +4 " << endl;

                //gives no.of same colored cards as the top card, if it is greater than zero then the player draws four cards.
                if (players[i]->getNoOfColorCards(topCard) > 0)
                {
                    cout << players[i]->getId() << " lost challenge and picked 4 cards " << endl;
                    giveCards(players[i], 4);
                    i = (i + 1) % noOfPlayers;
                }

                //if there is no colored card same as the top card then challenger draws six cards
                else
                {
                    cout << players[(i + 1) % noOfPlayers] << " lost challenge and picked 6 cards " << endl;
                    giveCards(players[(i + 1) % noOfPlayers], 6);
                    i = (i + 2) % noOfPlayers;
                }
            }

            //if there is no challenge then next player draws four cards and their turn is skipped.
            else
            {
                if (CheckPlayerWon(players[i],"Automatic"))
                    break;
                i = (i + 1) % noOfPlayers;          //index of the next player
                giveCards(players[i], 4);           //gives 4 cards to next player
                i = (i + 1) % noOfPlayers;          //next player turn is skipped
            }
        }

        // If played card is +2 then next player draws 2 cards and their turn is skipped.
        if (playedCard != NULL && playedCard->isPlus2())
        {
            cout <<"player with "<< players[i % noOfPlayers]->getId() << "  Played  +2️⃣ " << endl;
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = (i + 1) % noOfPlayers;              //index of the next player
            giveCards(players[i], 2);               //gives 2 cards to next player
            i = (i + 1) % noOfPlayers;              //next player turn is skipped
        }

        //If the played card is wild, then the player gets to choose the color.
        if (playedCard != NULL && playedCard->isWild())
        {
            cout << "player with "<< players[i % noOfPlayers]->getId() << " Played wild card 🔴🔵🟢🟡" << endl;      //shows no.of color options to the player
            string chosenColor = players[i]->getColorChoiceAutomatic(cardDeck->getColors());        //returns randomly chosen color
            playedCard->setColor(chosenColor);                                                      //chosen color is applied to the card
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = (i + 1) % noOfPlayers;
        }

        //If the played card is skip, then the next player is skipped.
        if (playedCard != NULL && playedCard->isSkip())
        {
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            cout << "Player " << players[(i + 1) % noOfPlayers]->getId() << "'s turn Skipped 🚫" << endl;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
            i = (i + 2) % noOfPlayers;
        }

        
        if (playedCard != NULL && playedCard->isReverse())
        {
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = reversePlayers(i);      //reverses the direction of the play
        }

        //checks whether the played card is an action card.
        if (playedCard != NULL && !playedCard->isPowerCard())
        {
            if (CheckPlayerWon(players[i],"Automatic"))
                break;
            i = (i + 1) % noOfPlayers;          //returns the index of next player
        }

        //If no card is played then it returns the index of next player
        if (playedCard == NULL)
        {
            i = (i + 1) % noOfPlayers;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
        }

        //set color to NULL for wild and +4 cards
        if (playedCard != NULL)
        {
            if (cardDeck->getTopCard()->isPlus4() || cardDeck->getTopCard()->isWild())
            {
                cardDeck->getTopCard()->setColor("NULL");
            }
            cardDeck->putCardInDiscardPile(playedCard);
        }
    }
}

/*
input: player and string [manual or automatic]
functionality: checks if the player won the game
*/
bool Simulator::CheckPlayerWon(Player *player,string s)
{

    //If player won the game return true and stop the game.

    if (player->didWin())
    {
        cout << "Player with ID " << player->getId() << " Won the match 🔥🏳🔥" << endl;
        return true;
    }

    //If player has only one card asks if they will say UNO or not
    if(player->getNoOfCardsRemaining()==1){
        bool uno;
        if(s=="Manual"){
            uno=player->isUNO();
        }
        else{
            uno=player->isUNOAutomatic();
        }
        if(uno){
            cout << "Player " << player->getId() << " Played UNO 👍👍"<<endl;
        }

        //If player didn't say UNO they will get to draw 2 cards
        if(!uno){
            cout << "Player " << player->getId() << " did NOT Play UNO 👎👎👎"<<endl;
            giveCards(player,2);
        }
    }


    //shows the player how many cards are in their respective hands [cards]
    cout << "Player " << player->getId() << "'s Remaining cards are " << player->getNoOfCardsRemaining() << endl;
    cout << "Player " << player->getId() << "'s turn over" << endl;
    std::cout << std::setfill('-') << std::setw(38) << '\n';
    return false;
}

/*
input: no. Of cards
functionality: distributes given no. of cards to all players.
*/
void Simulator::distributeCards(int noOfCards)
{
    for (auto player : players)
    {
        for (int i = 0; i < noOfCards; i++)
        {
            player->takeCard(cardDeck->getCard());          //gives a card to a player from card deck
        }
    }
}

/*
input: top card from DISCARDPile and type of simulation [automatic or manual]
output: gives the index of the next player and shows which action to take based on the top card.
*/
int Simulator::findStartingPlayerIndex(Card *topCard, string typeOfSimulation)
{
    int i = 0;
    int noOfPlayers = players.size();

    //If the first-card (or) top-card is +2 then the first player [player in the '0'th index] draws 2 cards
    if (topCard->isPlus2())
    {
        giveCards(players[i], 2);
        i = (i + 1) % noOfPlayers;
    }

    //If the first-card (or) top-card is wild then the first player [player in the '0'th index] gets to choose the color of the card
    else if (topCard->isWild())
    {
        //gives the color choice if played as manual or else randomly chodses a color
        string chosenColor = typeOfSimulation == "Manual" ? players[i]->getColorChoice(cardDeck->getColors()) : players[i]->getColorChoiceAutomatic(cardDeck->getColors());
        topCard->setColor(chosenColor);
        i = (i + 1) % noOfPlayers;
    }

    //If the first-card (or) top-card is skip then the first player [player in the '0'th index] gets skipped.
    else if (topCard->isSkip())
    {
        cout << "Player " << players[(i) % noOfPlayers]->getId() << "'s first turn Skipped 🚫" << endl;
        std::cout << std::setfill('-') << std::setw(38) << '\n';
        i = (i + 1) % noOfPlayers;          //returns the index of next player
    }

    //If the first-card (or) top-card is reverse then direction of play is reversed and play starts from the last player
    else if (topCard->isReverse())
    {
        if(players.size()==2){
            i=1;
        }
        else{
            i = reversePlayers(i);
        }  
    }
    if (!topCard->isPowerCard())
    {
        i = (i) % noOfPlayers;
    }
    return i;
}
Simulator::~Simulator()
{
    for (auto player : players)
    {
        delete player;
    }
    delete cardDeck;
}
