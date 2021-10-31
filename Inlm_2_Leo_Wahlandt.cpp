#include <iostream>
#include <ctime>

using namespace std;

int cardRandomizer(int Values[52]) {
    return  Values[rand() % 51];
}

string suitCalculator(int suitNumber) {
    //The first 13 cards are all Spade and 
    if (suitNumber <= 13) {
        return "Spade";

    }else if(suitNumber > 13 && suitNumber < 28) {
        return "Heart";

    }else if (suitNumber > 27 && suitNumber < 40) {
        return "Diamonds";

    }else {
        return "Clubs";
    }
}

int inputBalance() {
    cout << "Type in how much you want to insert (Min 100 & Max 6000): ";
    
    int playerBalance = 0;

    while (!(cin >> playerBalance) || cin.peek() != '\n' || (playerBalance < 100 || playerBalance > 6001)) {
        cout << "Incorrect value, only accept numbers. Try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return playerBalance;
};

int betting(int* pointerPlayerBalance) {
    //playerBalance is pointing to main{ playerBalance} Which means it uses the same variable and dont need to return a new balance.
    int bet{};
    bool bettingBoolean = true;
    cout << "How much do you want to bet?" << endl << "1. 100 kr" << endl << "2. 300 kr" << endl << "3. 500 kr?" << endl;
    while (bettingBoolean) {

        while (!(cin >> bet) || cin.peek() != '\n') {
            cout << "Incorrect value, only accept number. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        // This if checks how much the bet will be and if  the user has enough Balance. 
        if (bet == 1 && *pointerPlayerBalance >= 100) {
            bet = 100;
            *pointerPlayerBalance -= bet;
            cout << "You bet " << bet << " kr " << endl;
            bettingBoolean = false;
        }
        else if (bet == 2 && *pointerPlayerBalance >= 300) {
            bet = 300;
            *pointerPlayerBalance -= bet;
            cout << "You bet " << bet << " kr " << endl;
            bettingBoolean = false;
        }
        else if (bet == 3 && *pointerPlayerBalance >= 500) {
            bet = 500;
            *pointerPlayerBalance -= bet;
            cout << "You bet " << bet << " kr " << endl;
            bettingBoolean = false;
        }
        else {
            cout << "Invalid option or not enough balance" << endl;
            cout << "try again: ";
            cin.clear();
            bet = 0;
            bettingBoolean = true;
        }
        cin.ignore();
    }
    return bet;
}

int main(){
    //Array with all cards.
    int cardValues[52] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52 };
    int playerCard;
    int computerCard;
    int playerCardResult;
    int computerCardResult;
    int playerScore = 0;
    int computerScore = 0;
    int totalWinnings = 0;

    string playerCardSuit;
    string computerCardSuit;
    string addYesNo;
    string rematch;
    bool cardGame = true;
    bool gameLoop = true;
    bool continuePlaying = true;

    srand(time(NULL));
    
    cout << "Welcome to Valens Duel of cards " << endl;

    int playerBalance = inputBalance();

    while (continuePlaying) {
        
        
       int bet = betting(&playerBalance);
       playerScore = 0;
       computerScore = 0;

        while (gameLoop) {
            
            //The player gets a card  and with that card number the suitCalculator(card) sets the suit of the card.
            playerCard = cardRandomizer(cardValues);
            playerCardSuit = suitCalculator(playerCard);
           
            //The computer gets a card  and with that card number the suitCalculator(card) sets the suit of the card.
            computerCard = cardRandomizer(cardValues);
            computerCardSuit = suitCalculator(computerCard);

            //If they pull the same card the computer needs to take another one because player has already taken it.
            while (playerCard == computerCard) {
                cout << "Computer should reroll" << endl;
                computerCard = cardRandomizer(cardValues);
                cout << computerCard << endl;
            }

            //This convert the high numbercard to the correct card. If the user pulls 14 its actually 1 Heart.
            playerCardResult = 1 + (playerCard % 13);
            computerCardResult = 1 + (computerCard % 13);
            cout << "----------------Your turn----------------" << endl;
            cout << "Presse enter to draw a card ";
            cin.get();
            cout <<"Your card: " <<  playerCardResult << " " << playerCardSuit << endl;
           
            cout << "-------------Computers turn----------------" << endl;
            cout << "Computer draws a card: ";
            cout << computerCardResult << " " << computerCardSuit << endl;

            cout << "Press enter to compare" << endl;
            cin.get();
            
            cout << "-------------Comparing-----------------" << endl;

            //The if checks if the player card is better in modulo of 13 (ex. 20 % 13 = 7)
            if (playerCardResult > computerCardResult) {
                cout << "Player card " << playerCardResult << " " << playerCardSuit <<  " is better than computer card " << computerCardResult << " " << computerCardSuit << endl;
                playerScore++;
            } //If the playercard is lower than computer = computer wins.
            else if (playerCardResult < computerCardResult) {
                cout << "Computer card " << computerCardResult << " " << computerCardSuit << " is better than player card " << playerCardResult << " " << playerCardSuit << endl;
                computerScore++;
            }
            else {
                //The value of the card are the same (modulo 13) and now checks the suit.
                    cout << "The value of the cards are the same. Now check suit.\nThe result: Player " << playerCardResult << " " << playerCardSuit << "\nComputers card " << computerCardResult << " " << computerCardSuit << endl;
                
                    //If the value of the card is low it means that the suit of the card is better. Look at the suitCalculator function.
                    if (playerCard < computerCard) {
                        cout << "Player has the best suit." << endl;
                        playerScore++;
                    }
                    else {
                        cout << "Computer has the best suit." << endl;
                        computerScore++;
                    }
            }
            cout << "The score is: player " << playerScore << " Computer " << computerScore << endl;
            if (playerScore == 2) {
                playerBalance += bet * 2;
                totalWinnings += bet;
                cout << "Player won! This is how much you have now: " << playerBalance << endl;
                break;
            }
            else if (computerScore == 2) {
                totalWinnings -= bet;
                cout << "Computer won! This is how much you have now: " << playerBalance << endl;
                break;
            }
        }
            //This IF checks if the player want to continue playing or quit the game
            cout << "Do you wanna play again (y)?" << endl; cin >> rematch;
            if (rematch == "Y" || rematch == "y") {
                //If the user has less than 100 kr which is the least bet possible, want to add more money.
                if (playerBalance < 100) {
                    cout << "You have not enough money to bet. Do you wanna add more? Yes(Y) or No(N)";
                    cin >> addYesNo;

                    if (addYesNo == "Y" || addYesNo == "y") {
                        playerBalance += inputBalance();
                    }
                    else {
                        cout << "Thank you for playing the game. Hope to see you later aligator" << endl;
                        break;
                    }
                }
            }
            else {
                cout << "Thank you for playing " << endl << "This is how much your betting result for today: " << totalWinnings << endl;
                break;
            }
    }
}
