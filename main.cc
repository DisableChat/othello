/*************************************************************************
	Wesley Ryder
	11-25-17
	Description: This is the main for the othello game project. Where the
		sole purpose of main is to just make an object game and run it.
*************************************************************************/

#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include "game.h"     // Provides definition of game class
#include "colors.h"
#include "space.h"
#include "othello.h"
#include <cstdlib>
using namespace std;
using namespace main_savitch_14;

int main(){

	game::who winner;
	Othello my_game;
	winner = my_game.play();
	cout << "Two Consecutive Passes: Game Is Over" << endl;
	if(winner == 0){cout << "PLAYER 1 WINS!" << endl;}
	if(winner == 2){cout << "PLAYER 2 WINS!" << endl;}
	if(winner == 1){cout << "IT'S A TIE!" << endl;}
	return 0;
}