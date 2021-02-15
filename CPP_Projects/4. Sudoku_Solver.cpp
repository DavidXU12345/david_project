#include <cstdio>
#include <iostream>
using namespace std;
#define N 9

bool FindUnassignedLocation(int board[N][N], int &row, int &col) 
{ 
	for (row = 0; row < N; row++) 
		for (col = 0; col < N; col++) 
			if (board[row][col] == 0) 
				return true; 
	return false; 
} 

bool isOk (int board[N][N], int row, int col, int num) //constraints
{	
	//whether it is available
	if (board[row][col]!=0)
	return false;
	
	//check column & row
	for (int i=0; i<N; ++i){
		if (board[row][i]==num || board[i][col]==num)
		return false;
	}
	
	
	//check 3x3 box
	for (int i=0; i<3; ++i){
		for (int j=0; j<3; ++j){
			if (board[row-row%3][col-col%3]==num)
			return false;
		}
	}
		
	return true;		
}


bool SolveSudoku(int board[N][N]) 
{ 
	int row, col; 

	if (FindUnassignedLocation(board, row, col)==false) //it will return next unassigned location
	return true;

	for (int num = 1; num <= 9; num++) 
	{ 
		if (isOk(board, row, col, num)) 
		{ 
			board[row][col] = num; 
			if (SolveSudoku(board)) 
				return true; 
			board[row][col] = 0; 
		} 
	} 
	return false; 
} 

void printBoard(int board[N][N]) 
{ 
	for (int row = 0; row < N; row++) 
	{ 
	for (int col = 0; col < N; col++) 
			cout << board[row][col] << " "; 
		cout << endl; 
	} 
} 

int main() 
{ 
	int board[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 0, 0},  
					{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 0, 0},  
					{0, 0, 0, 0, 0, 0, 0, 0, 0}}; 
	if (SolveSudoku(board) == true) 
		printBoard(board); 
	else
		cout << "No solution exists"; 

	return 0; 
} 
