#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cstdio>

using namespace std;

class Game
{
    enum class Player
    {
        none = '-',
        human = 'X',
        computer = 'O'
    };

    struct Move
    {
        unsigned int x = 0;
        unsigned int y = 0;
    };

    Player board[3][3];

public:
    Game() 
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                board[i][j] = Player::none;
            }
        }
    }

    void printBoard()
    {
        system("cls");
		cout << "    0     1     2\n +-----------------+";
        for (unsigned int i = 0; i < 3; i++)
        {
            cout << "\n"<<i<<"|";
            for (unsigned int j = 0; j < 3; j++)
            {
                cout << "  " << static_cast<char>(board[i][j]) << "  |";
            }
        }
        cout << "\n +-----------------+\n";
    }

    bool isTie()
    {
        for (unsigned int i = 0; i < 3; i++)
        	for (unsigned int j=0; j<3; j++)
        {
            if (board[i][j] == Player::none)
                return false;
        }
        return true;
    }

    bool checkWin(Player player)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            // Check horizontals
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;

            // Check verticals
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }

    Move minimax() 
    {
        int score = numeric_limits<int>::max();
        Move move;

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;

                    int temp = maxSearch();

                    if (temp < score)
                    {
                        score = temp;
                        move.x = i;
                        move.y = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }

        return move;
    }

    int maxSearch() 
    {
        if (checkWin(Player::human)) { return 10; }
        else if (checkWin(Player::computer)) { return -10; }
        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::min();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::human;
                    score = max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    int minSearch()
    {
        if (checkWin(Player::human)) { return 10; }
        else if (checkWin(Player::computer)) { return -10; }
        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::max();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;
                    score = min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    void getHumanMove()
    {
        bool fail = true;
        unsigned int x = -1, y = -1;

        do
        {
            cout << "Enter your move in coordinate form[row, col]. ex: 02\nEnter your move: ";

            char c;
            cin >> c;
            x = c - '0';
            cin >> c;
            y = c - '0';
			
			if (x>2 || y>2 || x<0 || y<0 || board[x][y]!=Player::none){
				cout<<"Invalid Move, please try again"<<endl;
				continue;
			}
				
			
            fail = board[x][y] != Player::none; 

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (fail);

        board[x][y] = Player::human;
    }

    void play()
    {
       	unsigned int turn = 0;
        bool exit = false;

        

        do
        {	
			printBoard();
            // human move
            if (turn == 0)
            {
                getHumanMove();
				
                if (checkWin(Player::human))
                {	
                	printBoard();
                    cout << "Human Wins\n";
                    exit = true;
                }
            }
            else 
            {
                Move aimove = minimax();
                cout << aimove.x << aimove.y << "\n";
                board[aimove.x][aimove.y] = Player::computer;
				
                if (checkWin(Player::computer))
                {
                    printBoard();
					cout << "Computer Wins\n";
                    exit = true;
                }
            }

            if (isTie())
            {
                printBoard();
				cout << "\n*** Tie ***\n";
                exit = true;
            }

            turn ^= 1;

        } while (!exit);
	
    }
};

int main()
{	
char choice='N';

do
{	Game tictactoe;
    tictactoe.play();
    cout<<"Press Y if you want to play another round, Press any other keys to exit.\n";
	cin>>choice;
}while (choice=='y' || choice=='Y');
    
    return 0;
}
