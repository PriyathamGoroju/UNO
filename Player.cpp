#include <bits/stdc++.h>
#include <random>
#include "Player.h"

using namespace std;

Player::Player(){}
Player::Player(int ID){
    id=ID;
}
//This function automatically adds the selected card with the player to the 'DISCARDpile'.
Card* Player::putCardAutomatically(Card* topCard){
    cout<<"Player "<<id<<"'s turn"<<endl;
    cout<<"Top Card : ";
    topCard->show();
    cout<<endl;
    Card* selectedCard= getCardChoiceAutomatic(topCard);
    cards.erase(selectedCard);
    return selectedCard;
}
//using this function player can manually add the selected card to the 'DISCARDpile'
Card* Player::putCardManual(Card* topCard){
    cout<<"Player "<<id<<"'s turn"<<endl;
    cout<<"Top Card : ";
    topCard->show();
    cout<<endl;
    Card* selectedCard=getCardChoice(topCard);
    cards.erase(selectedCard);
    return selectedCard;
}
//The function returns the cards after filtering respective to the top card
vector<Card*> Player::filter(Card* topCard){
    vector<Card*> filteredCards;
    int numberOfColorCards=0;
    for(auto card:cards){
        if(card->isWild()||card->isPlus4()){        //if the
                filteredCards.push_back(card);
        }
        else if(topCard->isReverse()&& card->isReverse()){ //if the top card is a reverse and we have a reverse card
                filteredCards.push_back(card);              //the reverse card added to the filtered card 
        }

        else if(topCard->isSkip()&& card->isSkip()){        //if the top card is a skip and we have a skip card
            filteredCards.push_back(card);                   //the skip card added to the filtered card 
        }
        
        else if(topCard->isPlus2()&& card->isPlus2()){        //if the top card is a +2 and we have a +2 card
            filteredCards.push_back(card);                   //the +2 card added to the filtered card 
        }
        
        else if(topCard->getNumber()==card->getNumber() && topCard->getNumber()!=-1 ){
            filteredCards.push_back(card);                  //if the number on top card matches to the number on card we have
        }                                                    //the card added to the filtered card               
        else if((topCard->getColor()==card->getColor() ) && topCard->getColor()!="NULL" ){
                filteredCards.push_back(card);             //if the colour on top card matches to the colour on card we have
                numberOfColorCards++;                       //the card added to the filtered card
        }
    }
    return filteredCards;
}

//This function used if the player wants to take any card from the draw pile
void Player::takeCard(Card* inputCard){
    cards.insert(inputCard);
}

//This function check whether the number of cards remaining with the player are zero or not
bool Player::didWin(){
    return cards.size()==0;
}

//This function returns the number of colour cards
int Player::getNoOfColorCards(Card* topCard){
    int noofcoloredcards=0;
    for(auto c:cards){
        if(topCard->getColor()==c->getColor() && topCard->getColor()!="NULL"){
            noofcoloredcards++;
        }
    }
    return noofcoloredcards;
}

// the player who's turn is next to the player, who played +4 card ,can challenge that he wanted played +4 card even though 
// if he had a card of same colour as  of the top card in discard pile before +4 is played
//Using this function the a player can challenge another player when +4 is played  

bool Player::doYouWantToChallenge(){
    random_device rd;
    uniform_int_distribution<int> distribution(1,100);
    int challengers_num =distribution(rd);
    return challengers_num>=70;
}
//Using this function the player can challenge another player who played +4 card manually 
bool Player::doYouWantToChallengeManual(){
    char a;
    cout<<"Player with id "<<id<<" Wants to Challenge"<<endl;
    cout<<"Player with id  "<<id<<" Do you want to challenge for the use of +4 [Y/N] : ";
    cin >> a;
    while(a!='Y'&&a!='y'&&a!='N'&&a!='n'){
        cout<<"Wrong choice"<<endl;
        cout<<"Input correct choice : ";
        cin>>a;
    }
    return (a=='Y'||a=='y')?1:0;

}
//This function is used to get the id of the respective player 
int Player::getId(){
    return id;
}
//This function is used to get the number of card remaining with the player
int Player::getNoOfCardsRemaining(){
    return cards.size();
}
//This function is used for getting the choice of card we have with respect to top card in 'DISCARDpile'
Card* Player::getCardChoice(Card* topCard){
    vector<Card*> filteredCards=filter(topCard);
    if(filteredCards.size()==0){
        return NULL;
    }
    for(int i=0;i<filteredCards.size();i++){
        cout<<"choice "<<i+1<<" : ";
        filteredCards[i]->show();
        cout<<endl;
    }
    int choice;
    cout<<"Select Card Choice: ";
    cin>>choice;
    while(choice-1>=filteredCards.size()||choice-1<0){
        cout<<"Wrong Choice"<<endl;
        cout<<"Select Correct Card Choice:";
        cin>>choice;
    }
    return filteredCards[choice-1];
}
//using this function we can get the choice of cards we have with respect to top card of the 'DISCARDpile' automatically
Card* Player::getCardChoiceAutomatic(Card* topCard){
    vector<Card*> filteredCards=filter(topCard);
    if(filteredCards.size()==0){
        return NULL;
    }
    for(int i=0;i<filteredCards.size();i++){
        cout<<"choice "<<i+1<<" : ";
        filteredCards[i]->show();
        cout<<endl;
    }
    //random choice generator
    random_device rd;
    uniform_int_distribution<int> distribution(1,filteredCards.size());
    int choice=distribution(rd);
    cout<<"Select Card Choice: ";
    cout<<choice<<endl;
    return filteredCards[choice-1];
}
//this function helps in choosing the colour,by  player after playing wild or +4 card 
string Player::getColorChoice(vector<string> colors){
    cout << "Color Choices: " << endl;
    for (int i = 0; i < colors.size(); i++)
    {
        cout << "choice " << i + 1 << " :";
        cout << colors[i] << endl;
    }
    int choice;
    cout << "Select Color Choices: ";
    cin >> choice;
    while (choice - 1 > colors.size() || choice - 1 < 0)
    {
        cout << "Wrong Choice" << endl;
        cout << "Select Correct colors Choice:";
        cin >> choice;
    }
    cout << endl;
    return colors[choice - 1];
}
//this function helps in choosing the colour,by  player after playing wild or +4 card automatically
string Player::getColorChoiceAutomatic(vector<string> colors){
    cout << "Color Choices: " << endl;
    for (int i = 0; i < colors.size(); i++)
    {
        cout << "choice " << i + 1 << " :";
        cout << colors[i] << endl;
    }
    cout << "Select Color Choices: ";
    random_device rd;
    uniform_int_distribution<int> distribution(1, colors.size());
    int choice = distribution(rd);
    cout << choice << endl;
    return colors[choice - 1];
}
//This function tells us that a player is left with only ONE card by telling "UNO".
bool Player::isUNO(){
    char a;
    cout<<"Do you want to say UNO [Y/N]:";
    cin >> a;
    return (a=='Y'||a=='y')?1:0;
}
//this function tells us that a player is left with only ONE card by telling "UNO" automatically with the probability of 0.9.
bool Player::isUNOAutomatic(){
    random_device rd;
    uniform_int_distribution<int> distribution(0,1);
    int choice = distribution(rd);
    return choice<=0.9;
}  
Player::~Player(){
    for(auto card:cards){
        delete card;
    }
}