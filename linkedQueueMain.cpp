//
//  linkedQueueMain.cpp
//  CSS342A Assignment4
//
//  Created by Jayda  on 11/15/25.
//

#include <iostream>
#include "linkedqueue.h"
#include <cstring>
#include <ctime>

using namespace std;
using namespace lqueue;

class HotPotatoGame {
    public:
        string playGame(int n, LinkedQueue<string>& Q, LinkedQueue<string>& L, int maxPasses);
    
};

string playGame(int n, LinkedQueue<string>& Q, LinkedQueue<string>& L, int maxPasses) {
    int numPasses = (rand() % maxPasses) + 1;
    int numPassesReset = numPasses;
    
    while(n != 1){
        if(numPasses == 1) {
            string loser = Q.front();
            L.enqueue(loser);
            Q.dequeue();
            n--;
            numPasses = numPassesReset;
        }
        
        string tmp = Q.front();
        Q.dequeue();
        Q.enqueue(tmp);
        
        numPasses--;
        
    }
    
    string winner = Q.front();
    
    return winner;
}


int main() {
    srand(time(0));
    bool play = true;
    
    while(play) {
        LinkedQueue<string> Q;
        LinkedQueue<string> L;
        int n = 0;
        bool done = false;
        string name;
        int maxPasses;
        string choice;
        
        cout << "Enter player names (type 'done' to finish): ";
        while (done == false) {
            cin >> name;
            
            if(name == "done") {
                done = true;
            } else {
                Q.enqueue(name);
                n++;
            }
        }
        cout << endl;
        
        cout << "Enter maximum number of passes: ";
        cin >> maxPasses;
        cout << endl;
        
        string winner = playGame(n, Q, L, maxPasses);
        
        while(!L.empty()) {
            cout << "Eliminating: " << L.front() << endl;
            L.dequeue();
        }
        cout << endl;
        
        cout << "Winner is: " << winner << endl;
        cout << endl;
        
        cout << "Would you like to play again? (Y)es/(N)o ";
        cin >> choice;
        
        if(choice == "n") {
            play = false;
        }
        
    }
    return 0;
}
