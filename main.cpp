#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

enum Player{USER,AI}; // This will make it easier to keep track of whose turn it is
enum Winner{PLAYER,COMPUTER,STALEMATE,UNDEF}; //This will help determine what step the code should do next

void PrintCurrentBoard(string currentBoard[][3]);
void PrintDemoBoard();
bool CheckForWin(string currentBoard[][3]);
Winner CheckForEnd(string currentBoard[][3], Player currPlayer, int currTurn);
void InputBoard(string currentBoard[][3], Player currPlayer);
Winner PlayGame(string currentBoard[][3], Player currPlayer);

int main() {
    bool isPlaying = true;
    Player currPlayer;
    char userChoice;
    srand(time(0));

    cout << "Welcome to TicTacToe!" << endl;
    cout << "You'll be playing against me, the computer. You'll be X's and I'll be O's." << endl;
    cout << "You can input your options only from the available spaces." << endl << endl;
    cout << "The options are as follow:" << endl;
    PrintDemoBoard(); //So the player know their options, as they won't be actually typing into the board
    cout << endl;

    do {
        string gameBoard[3][3];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                gameBoard[i][j] = " ";
            }
        } //Initiates and restarts the board

        cout << "Would you like to go first, or would you rather go second?" << endl;
        cout << "A: First\tB: Second\t(A/B): ";
        cin >> userChoice;
        while (userChoice != 'A' && userChoice != 'B') {
            cout << endl;
            cout << "Please enter a valid option. (A/B): ";
            cin >> userChoice;
        }
        cout << endl;
        if (userChoice == 'A') {
            cout << "You'll go first!" << endl;
            currPlayer = USER;
        }
        else if (userChoice == 'B') {
            cout << "I'll go first, then!" << endl;
            currPlayer = AI;
        }
        PrintCurrentBoard(gameBoard);

        switch (PlayGame(gameBoard, currPlayer)) {
            case PLAYER:
                cout << "You win! Congratulations!" << endl << endl;
                break;
            case COMPUTER:
                cout << "I win! Better luck next time." << endl << endl;
                break;
            case STALEMATE:
                cout << "It's a tie. How did this happen?" << endl << endl;
                break;
            case UNDEF:
                cout << "If you reach this, my code is broken or you're doing something way wrong." << endl << endl;
        }

        cout << "Do you want to play again? (Y/N): ";
        cin >> userChoice;
        while (userChoice != 'Y' && userChoice != 'N') {
            cout << endl;
            cout << "Please enter a valid option. (Y/N): ";
            cin >> userChoice;
        }
        cout << endl;
        if (userChoice == 'Y') {
            isPlaying = true;
        }
        else if (userChoice == 'N') {
            isPlaying = false;
        }
    } while (isPlaying);
    cout << "Thanks for playing! XO" << endl;
    return 0;
}

void PrintCurrentBoard(string currentBoard[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << " " << currentBoard[i][j] << " ";
            if (j < 2) {
                cout << "|";
            }
        }
        cout << endl;
        if (i < 2) {
            cout << "---+---+---" << endl;
        }
    }
}

void PrintDemoBoard() {
    cout << " 1 | 2 | 3 " << endl;
    cout << "---+---+---" << endl;
    cout << " 4 | 5 | 6 " << endl;
    cout << "---+---+---" << endl;
    cout << " 7 | 8 | 9 " << endl;
}

bool CheckForWin(string currentBoard[][3]) {
    string A1 = currentBoard[0][0];
    string A2 = currentBoard[0][1];
    string A3 = currentBoard[0][2];

    string B1 = currentBoard[1][0];
    string B2 = currentBoard[1][1];
    string B3 = currentBoard[1][2];

    string C1 = currentBoard[2][0];
    string C2 = currentBoard[2][1];
    string C3 = currentBoard[2][2];

    if ((A1 == A2 && A2 == A3) && A1 != " ") { //All folow the same syntax: if the first, second, and third are all equal, but if any (and therefor all) are empty, ignore it.
        return true;
    }
    else if (B1 == B2 && B2 == B3 && B1 != " ") {
        return true;
    }
    else if (C1 == C2 && C2 == C3 && C1 != " ") {
        return true;
    }
    else if (A1 == B1 && B1 == C1 && A1 != " ") {
        return true;
    }
    else if (A2 == B2 && B2 == C2 && A2 != " ") {
        return true;
    }
    else if (A3 == B3 && B3 == C3 && A3 != " ") {
        return true;
    }
    else if (A1 == B2 && B2 == C3 && A1 != " ") {
        return true;
    }
    else if (A3 == B2 && B2 == C1 && A3 != " ") {
        return true;
    }
    else {
        return false;
    }
}

Winner CheckForEnd(string currentBoard[][3], Player currPlayer, int currTurn) {
    if (CheckForWin(currentBoard)) {
        switch (currPlayer) {
            case USER:
                return PLAYER;
            case AI:
                return COMPUTER;
        } //Translates current player into winning player
    }
    else if (!CheckForWin(currentBoard) && currTurn == 8) { //If no winner but board full
        return STALEMATE;
    }
    else {
        return UNDEF; //Undefined; the game continues
    }
}

void InputBoard(string currentBoard[][3], Player currPlayer) {
    vector<int> availablePositions;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (currentBoard[i][j] == " ") {
                availablePositions.push_back(1+j+(3*i));
            }
        }
    } //Lists the available (if they're empty) spots
    bool validChoice = false;

    if (currPlayer == USER) {
        cout << " Available positions: ";
        for (int i = 0; i < availablePositions.size(); ++i) {
            cout << availablePositions.at(i) << " ";
        }
        cout << endl;
        cout << "Your choice: ";
        int userChoice;
        cin >> userChoice;


        for (int i = 0; i < availablePositions.size(); ++i) {
            if (availablePositions.at(i) == userChoice) {
                validChoice = true;
            }
        }

        while (!validChoice) {
            cout << endl;
            cout << "Please enter a valid option. Your choice: ";
            cin >> userChoice;
            for (int i = 0; i < availablePositions.size(); ++i) {
                if (availablePositions.at(i) == userChoice) {
                    validChoice = true;
                }
            }
        }
        cout << endl;

        switch (static_cast<int>(userChoice)) {
            case 1:
                currentBoard[0][0] = "X";
                return;
            case 2:
                currentBoard[0][1] = "X";
                return;
            case 3:
                currentBoard[0][2] = "X";
                return;
            case 4:
                currentBoard[1][0] = "X";
                return;
            case 5:
                currentBoard[1][1] = "X";
                return;
            case 6:
                currentBoard[1][2] = "X";
                return;
            case 7:
                currentBoard[2][0] = "X";
                return;
            case 8:
                currentBoard[2][1] = "X";
                return;
            case 9:
                currentBoard[2][2] = "X";
                return;
        }
    }
    else if (currPlayer == AI) {
        int AIChoice;
        while (!validChoice) {
            AIChoice = (rand()%9)+1; //I haven't delved much into AI, so for now the computer is randomized
            for (int i = 0; i < availablePositions.size(); ++i) {
                if ((availablePositions.at(i)) == AIChoice) {
                    validChoice = true;
                }
            }
        }

        switch (AIChoice) {
            case 1:
                currentBoard[0][0] = "O";
                return;
            case 2:
                currentBoard[0][1] = "O";
                return;
            case 3:
                currentBoard[0][2] = "O";
                return;
            case 4:
                currentBoard[1][0] = "O";
                return;
            case 5:
                currentBoard[1][1] = "O";
                return;
            case 6:
                currentBoard[1][2] = "O";
                return;
            case 7:
                currentBoard[2][0] = "O";
                return;
            case 8:
                currentBoard[2][1] = "O";
                return;
            case 9:
                currentBoard[2][2] = "O";
                return;
        }
    }
}

Winner PlayGame(string currentBoard[][3], Player currPlayer) {
    int currTurn = 0;
    while (currTurn <=8) {
        if (currTurn <= 8 && currPlayer == AI) {
            cout << "My turn!" << endl;
            InputBoard(currentBoard, currPlayer);
            cout << endl;
            PrintCurrentBoard(currentBoard);
            if (CheckForEnd(currentBoard, currPlayer, currTurn) != UNDEF) {
                return CheckForEnd(currentBoard, currPlayer, currTurn);
            }
            else {
                currTurn++;
                currPlayer = USER;
            } //Counts the turn as passed and changes to user; both follow the same format with a few exceptions
        }

        if (currTurn <= 8 && currPlayer == USER) {
            cout << "Where will you place your X?" << endl;
            InputBoard(currentBoard, currPlayer);
            cout << endl;
            PrintCurrentBoard(currentBoard);
            if (CheckForEnd(currentBoard, currPlayer, currTurn) != UNDEF) {
                return CheckForEnd(currentBoard, currPlayer, currTurn);
            } else {
                currTurn++;
                currPlayer = AI;
            } //
        }
    }
}
