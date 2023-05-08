#include <bits/stdc++.h>
#include "Simulator.h"
using namespace std;
int main(){
    // Simulator sim=Simulator(2,4,9);
    int noOfPlayers;
    cout<<"Enter No Of Players: ";
    cin>>noOfPlayers;
    char c;
    cout<<"Do You Want To Simulate [Y/N]: ";
    cin>>c;
    Simulator sim=Simulator(noOfPlayers,4,9);
    if(c=='y' || c=='Y'){
        sim.simulateAutomatically();
    }
    else{
        sim.simulateManually();
    }

    
}