#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

class Node {
    public:
        int value;
        Node* next;

        Node(int val) : value(val), next(NULL) {}
};

class PuzzleGame {
    private:
        Node* puzzle;
        int x = 2, y = 2;
        int steps = 0, temp = 0;

        Node* getNodeAtPosition(int position) {
            Node* current = puzzle;
            for (int i = 0; i < position; i++) {
                if (current == NULL) {
                    // Handle an invalid position
                    return NULL;
                }
                current = current->next;
            }
            return current;
        }

    public:
        PuzzleGame() : puzzle(NULL) {
            int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

            Node* prev = NULL;
            for (int i = 8; i >= 0; i--) {
                Node* newNode = new Node(values[i]);
                newNode->next = prev;
                prev = newNode;
            }

            puzzle = prev;
        }

        ~PuzzleGame() {
            Node* current = puzzle;
            Node* next;

            while (current != NULL) {
                next = current->next;
                delete current;
                current = next;
            }
        }

        void gotoxy(int x, int y);

        int puzzleFrame();

        void printBoard();

        bool checkGameEnd();

        int getEmptyCellIndex();

        void swapCells(int i);

        void moveUp();

        void moveDown();

        void moveLeft();

        void moveRight();

        void initializeGame();

        void playGame();

        void handleInput(int input);

        void loadingBar();

};

void PuzzleGame::gotoxy(int x, int y) {
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

int PuzzleGame::puzzleFrame() {
    int i;
    for (i = 0; i <= 28; i++) {
        gotoxy(50, i);
        cout << char(186);
    }

    gotoxy(55, 8);
    cout << "\tUsing W A S D \n\t\t\t\t\t\t\tto move the numbers";
    // gotoxy(55, 12);
    // cout << "\tSteps: " << temp << endl;

    gotoxy(55, 8);
}

void PuzzleGame::printBoard() {
    system("cls");
    puzzleFrame();
    
    cout << endl;
    Node* current = puzzle;
    for (int i = 0; i < 9; i++) {
        int value = current->value;
        if (value) {
            cout << " | " << value << " | ";
        }
            
        else {
            cout << "       ";
        }

        if ((i + 1) % 3 == 0) {
            cout << "\n\n\n";
        }

        current = current->next;
    }
}

bool PuzzleGame::checkGameEnd() {
    Node* current = puzzle;
    for (int i = 0; i < 8; i++) {
        if (current->value != i + 1)
            return false;
        current = current->next;
    }
    return true;
}

int PuzzleGame::getEmptyCellIndex() {
    return x * 3 + y;
}

void PuzzleGame::swapCells(int i) {
    int emptyCellIndex = getEmptyCellIndex();
    Node* emptyCellNode = getNodeAtPosition(emptyCellIndex);
    Node* targetNode = getNodeAtPosition(emptyCellIndex + i);

    if (emptyCellNode != NULL && targetNode != NULL) {
        swap(emptyCellNode->value, targetNode->value);
    }
}

void PuzzleGame::moveUp() {
    
    if (x > 0) {
        swapCells(-3);
        steps++;
        x--;
    }
}
void PuzzleGame::moveDown() {
    
    if (x < 2) {
        swapCells(3);
        steps++;
        x++;
    }
}
void PuzzleGame::moveLeft() {
    
    if (y > 0) {
        swapCells(-1);
        steps++;
        y--;
    }
}
void PuzzleGame::moveRight() {
    
    if (y < 2) {
        swapCells(1);
        steps++;
        y++;
    }
}

void PuzzleGame::initializeGame() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i <= 200; i++) {
        int random = rand() % 4;
        if (random == 0) {
            moveUp();
        }
        if (random == 1) {
            moveDown();
        };
        if (random == 2) {
            moveLeft();
        };
        if (random == 3) {
            moveRight();
        };
    }
}

void PuzzleGame::playGame() {
    gotoxy(10, 10);
    while (true) {
        printBoard();
        if (checkGameEnd()) {
            cout << "\n\tCongratulations! You have won.\n";
            cout << "The number of Steps you have made: " << temp << endl;
            cout << endl;
            break;
        }
        int input = getch();
        handleInput(input);
        printBoard();
    }
}

void PuzzleGame::handleInput(int input) {
    if (input == 75) {
        moveRight();
        temp++;
    }
    
    if (input == 77) {
        moveLeft();
        temp++;
    }
    
    if (input == 72) {
        moveDown();
        temp++;
    }
    
    if (input == 80) {
        moveUp();
        temp++;
    }
    
}

void PuzzleGame::loadingBar() {
	system("cls");
    char a = 177, b = 219;
    cout << "\n\n\n\n";
    cout << "\n\n\n\n\t\t\t\t\t       Loading...\n\n";
    cout << "\t\t\t\t\t";
    for (int i = 0; i < 34; i++)
        cout << a;
    cout << "\r";
    cout << "\t\t\t\t\t";
    for (int i = 0; i < 34; i++) {
        cout << b;
        Sleep(10);
    }
}


int main() {
    int choice;
    do {
        PuzzleGame game;
        while (1) {
            do {
                system("cls");
                game.gotoxy(57, 5);
                cout << "    ___  _  _ ___  ___  _    ____    ____ ____ _  _ ____  \n";
                game.gotoxy(57, 6);
                cout << "    |__] |  |   /    /  |    |___ __ | __ |__| |\\/| |___ \n";
                game.gotoxy(57, 7);
                cout << "    |    |__|  /__  /__ |___ |___    |__] |  | |  | |___  \n";

                game.gotoxy(30, 3);
                cout << "\n\t__________________MENU_________________\n";
                game.gotoxy(0, 5);
                cout << "\t|          1. New Game                |\n";
                game.gotoxy(0, 6);
                cout << "\t|          2. Instructions            |\n";
                game.gotoxy(0, 7);
                cout << "\t|          0. Exit                    |\n";
                game.gotoxy(0, 8);
                cout << "\t|_____________________________________|\n";
                game.gotoxy(0, 9);
                cout << "\n\tEnter your choice: ";
                cin >> choice;
            } while (choice != 1 && choice != 2 && choice != 0);

            switch (choice) {
                case 1:
                    game.loadingBar();
                    game.initializeGame();
                    game.playGame();
                    char c;
                    cout << "Returning to the Main Menu!\n";
                    system("pause");
                    break;
                    
                case 2:
                    system("cls");
                    cout << "Use arrow keys to move the numbers.\n";
                    cout << "Arrange the numbers to form a sequence:\n";
                    cout << "\t1, 2, 3\n\t4, 5, 6\n\t7, 8   \n";
                    system("pause");
                    break;

                case 0:
                    exit(0);
                    break;
            }
        }
        

    } while (choice != 1 && choice != 2 && choice != 0);

    return 0;
}
