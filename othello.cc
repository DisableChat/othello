/*************************************************************************
	Wesley Ryder
	11-25-17
	Description: This is the implementation file for the Othello class.
		again wrapped in the namespace of savitch. 
*************************************************************************/

#include <iostream>
#include "game.h"
#include "space.h"
#include "othello.h"
#include "colors.h"
using namespace std;
namespace main_savitch_14
{
void Othello::compute_moves(std::queue<std::string>& moves) const{
	string tmp = "  ";
	for(char i = 'A'; i <= 'H'; i++){
		for(char j = '1'; j <= '8'; j++){
			tmp[0] = i;
			tmp[1] = j;
			if(is_legal(tmp)){moves.push(tmp);}
		}
	}
	if(moves.empty()){moves.push("xx");}
}

// restart function allows us to set all the pieces to empty besides middle four that need to be the dufualt
// for when starting a new game.
void Othello::restart(){
	for(int i = 0; i < 8; i++){
		for(int j= 0; j < 8; j++){
			bd[i][j].set_empty();
		}
	}
	bd[3][4].set_black();
	bd[4][3].set_black();
	bd[4][4].set_white();
	bd[3][3].set_white();
}

// display status shows the board by maxing a grid of the whole board with the corrispoinding numbers for rows and letters
// for the columns while also displaying the pieces dpending on if theyre empty, white or black and then setting those 
// corosponding possitions. 
void Othello::display_status()const{
	cout << endl;
	// note the reason for putting ERROR and then MENU color is that ERROR actually makes lettering more white(Bold white). 
	cout << ERROR << MENU <<"    A B C D E F G H   " << RESET << endl;
	cout << ERROR << MENU << "   -----------------  " << RESET << endl;
	for(int j = 0; j < 8; j++){
		if(j == 0){cout << ERROR << MENU << "1 |" << RESET;}
		else if(j == 1){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "2 |" << RESET;}
		else if(j == 2){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "3 |" << RESET;}
		else if(j == 3){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "4 |" << RESET;}
		else if(j == 4){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "5 |" << RESET;}
		else if(j == 5){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "6 |" << RESET;}
		else if(j == 6){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "7 |" << RESET;}
		else if(j == 7){cout << ERROR << MENU << "| "<< RESET << "\n" << ERROR << MENU << "8 |" << RESET;}
		cout << B_MAGENTA;
		cout << WHITE << "|";

		for(int i = 0; i < 8; i++){
			if(bd[i][j].is_empty()){
				cout << " " << "|";
			}
			if(bd[i][j].is_white()){
				cout << WHITE << "@" << WHITE << "|";
			}
			if(bd[i][j].is_black()){
				cout << BLACK << "@" << WHITE << "|";
			}
		}
		cout << B_BLACK;
	} 
	cout << ERROR << MENU << "| " << RESET << "\n";
	cout << ERROR << MENU << "   -----------------  " << RESET << endl;

}

// make move function breaks apart the move string and translates it into the grid terms
// of x direction  and y direction on the grid.
void Othello::make_move(const std::string& move){
	int x, y;
	int i, j;
	x = char_to_int(move.substr(0,1));
	y = atoi(move.substr(1,2).c_str());
	y--;
	bool up, down, left, right, up_left, up_right, down_left, down_right;
	bool flag = false;

	if(move == "xx"){
		return;
	}


	//BLACK: Checks all directions in relation to piece being set, if it finds oppisite color in a certain direction
	// it will return true for the corrosponding direction. Ie, up down left right upleft upright downleft downright
	if(last_mover() == COMPUTER){
		if(bd[x][y - 1].is_white() && y - 1 >= -1){up = true;}
		if(bd[x][y + 1].is_white() && y + 1 <= 8){down = true;}
		if(bd[x - 1][y].is_white() && x - 1 >= -1){left = true;}
		if(bd[x + 1][y].is_white() && x + 1 <= 8){right = true;}
		if(bd[x - 1][y - 1].is_white() && x - 1 >= -1 && y - 1 >= -1){up_left = true;}
		if(bd[x + 1][y - 1].is_white() && x + 1 <= 8 && y - 1 >= -1){up_right = true;}
		if(bd[x - 1][y + 1].is_white() && x - 1 >= -1 && y + 1 <= 8){down_left = true;}
		if(bd[x + 1][y + 1].is_white() && x + 1 <= 8 && y + 1 <= 8){down_right = true;}
	}
	//WHITE: Checks all directions in relation to piece being set, if it finds oppisite color in a certain direction
	// it will return true for the corrosponding direction. Ie, up down left right upleft upright downleft downright
	else{
		if(bd[x][y - 1].is_black() && y - 1 >= -1){up = true;}
		if(bd[x][y + 1].is_black() && y + 1 <= 8){down = true;}
		if(bd[x - 1][y].is_black() && x - 1 >= -1){left = true;}
		if(bd[x + 1][y].is_black() && x + 1 <= 8){right = true;}
		if(bd[x - 1][y - 1].is_black() && x - 1 >= -1 && y - 1 >= -1){up_left = true;}
		if(bd[x + 1][y - 1].is_black() && x + 1 <= 8 && y - 1 >= -1){up_right = true;}
		if(bd[x - 1][y + 1].is_black() && x - 1 >= -1 && y + 1 <= 8){down_left = true;}
		if(bd[x + 1][y + 1].is_black() && x + 1 <= 8 && y + 1 <= 8){down_right = true;}	
	}
	//BLACK: if black piece it will go in the direction corrosponding to the  directions that register true from the step above
	// and will continue in that direction untill it finds the original piece being laid down. If it finds it it will flip the 
	// pieces untill it gets back to original piece being laid. This happens in all directions hence the 8 possibilties. if not 
	// it will not flip the pieces.
	if(last_mover() == COMPUTER){
		// Up Direction
		if(up){
			int y1 = y;
			y1--;
			while(bd[x][y1].is_white() && y1 - 1 >= -1){
				y1--;
				if(bd[x][y1].is_black() && y1 - 1 >= -1){
					y1++;
					while(y1 < y){
						bd[x][y1].flip();
						y1++;
					}
				}
			}
		}
		// Down Direction
		if(down){
			int y2 = y;
			y2++;
			while(bd[x][y2].is_white() && y2 + 1 <= 8){
				y2++;
				if(bd[x][y2].is_black() && y2 + 1 <= 8){
					y2--;
					while(y2 > y){
						bd[x][y2].flip();
						y2--;
					}
				}
			}
		}
		// Left Direction
		if(left){
			int x1 = x;
			x1--;
			while(bd[x1][y].is_white() && x1 - 1 >= -1){
				x1--;
				if(bd[x1][y].is_black() && x1 - 1 >= -1){
					x1++;
					while(x1 < x){
						bd[x1][y].flip();
						x1++;
					}
				}
			}
		}
		// Right Direction
		if(right){
			int x2 = x;
			x2++;
			while(bd[x2][y].is_white() && x2 + 1 <= 8){
				x2++;
				if(bd[x2][y].is_black() && x2 + 1 <= 8){
					x2--;
					while(x2 > x){
						bd[x2][y].flip();
						x2--;
					}
				}
			}
		}
		// Up Left Direction
		if(up_left){
			int x3 = x, y3 = y;
			x3--;
			y3--;
			while(bd[x3][y3].is_white() && x3 - 1 >= -1 && y3 - 1 >= -1){
				x3--;
				y3--;
				if(bd[x3][y3].is_black() && x3 - 1 >= -1 && y3 - 1 >= -1){
					x3++;
					y3++;
					while(x3 < x && y3 < y){
						bd[x3][y3].flip();
						x3++;
						y3++;
					}
				}
			}
		}
		// Up Right Direction
		if(up_right){
			int x4 = x, y4 = y;
			x4++;
			y4--;
			while(bd[x4][y4].is_white() && x4 + 1 <= 8 && y4 - 1 >= -1){
				x4++;
				y4--;
				if(bd[x4][y4].is_black() && x4 + 1 <= 8 && y4 - 1 >= -1){
					x4--;
					y4++;
					while(x4 > x && y4 < y){
						bd[x4][y4].flip();
						x4--;
						y4++;
					}
				}
			}
		}
		// Down Left Direction
		if(down_left){
			int x5 = x, y5 = y;
			x5--;
			y5++;
			while(bd[x5][y5].is_white() && x5 - 1  >= -1 && y5 + 1 <= 8){
				x5--;
				y5++;
				if(bd[x5][y5].is_black() && x5 - 1  >= -1 && y5 + 1 <= 8){
					x5++;
					y5--;
					while(x5 < x && y5 > y){
						bd[x5][y5].flip();
						x5++;
						y5--;
					}
				}
			}
		}
		// Down Right Direction 
		if(down_right){
			int x6 = x, y6 = y;
			x6++;
			y6++;
			while(bd[x6][y6].is_white() && x6 + 1 <= 8 && y6 <= 8){
				x6++;
				y6++;
				if(bd[x6][y6].is_black() && x6 + 1 <= 8 && y6 <= 8){
					x6--;
					y6--;
					while(x6 > x && y6 > y){
						bd[x6][y6].flip();
						x6--;
						y6--;
					}
				}
			} 
		}
	}
	//WHITE: if White piece it will go in the direction corrosponding to the  directions that register true from the step above
	// and will continue in that direction untill it finds the original piece being laid down. If it finds it it will flip the 
	// pieces untill it gets back to original piece being laid. This happens in all directions hence the 8 possibilties. if not
	// it will not flip pieces.
	else{
		// UP Direction
		if(up){
			int y1 = y;
			y1--;
			while(bd[x][y1].is_black() && y1 - 1 >= -1){
				y1--;
				if(bd[x][y1].is_white() && y1 - 1 >= -1){
					y1++;
					while(y1 < y){
						bd[x][y1].flip();
						y1++;
					}
				}
			}
		}
		// Down Direction
		if(down){
			int y2 = y;
			y2++;
			while(bd[x][y2].is_black() && y2 + 1 <= 8){
				y2++;
				if(bd[x][y2].is_white() && y2 + 1 <= 8){
					y2--;
					while(y2 > y){
						bd[x][y2].flip();
						y2--;
					}
				}
			}
		}
		// Left Direction
		if(left){
			int x1 = x;
			x1--;
			while(bd[x1][y].is_black() && x1 - 1 >= -1){
				x1--;
				if(bd[x1][y].is_white() && x1 - 1 >= -1){
					x1++;
					while(x1 < x){
						bd[x1][y].flip();
						x1++;
					}
				}
			}
		}
		// Right Direction
		if(right){
			int x2 = x;
			x2++;
			while(bd[x2][y].is_black() && x2 + 1 <= 8){
				x2++;
				if(bd[x2][y].is_white() && x2 + 1 <= 8){
					x2--;
					while(x2 > x){
						bd[x2][y].flip();
						x2--;
					}
				}
			}
		}
		// Up Left Direction
		if(up_left){
			int x3 = x, y3 = y;
			x3--;
			y3--;
			while(bd[x3][y3].is_black() && x3 - 1 >= -1 && y3 - 1 >= -1){
				x3--;
				y3--;
				if(bd[x3][y3].is_white() && x3 - 1 >= -1 && y3 - 1 >= -1){
					x3++;
					y3++;
					while(x3 < x && y3 < y){
						bd[x3][y3].flip();
						x3++;
						y3++;
					}
				}
			}
		}
		// Up Right Direction
		if(up_right){
			int x4 = x, y4 = y;
			x4++;
			y4--;
			while(bd[x4][y4].is_black() && x4 + 1 <= 8 && y4 - 1 >= -1){
				x4++;
				y4--;
				if(bd[x4][y4].is_white() && x4 + 1 <= 8 && y4 - 1 >= -1){
					x4--;
					y4++;
					while(x4 > x && y4 < y){
						bd[x4][y4].flip();
						x4--;
						y4++;
					}
				}
			}
		}
		// Down Left Direction
		if(down_left){
			int x5 = x, y5 = y;
			x5--;
			y5++;
			while(bd[x5][y5].is_black() && x5 - 1  >= -1 && y5 + 1 <= 8){
				x5--;
				y5++;
				if(bd[x5][y5].is_white() && x5 - 1  >= -1 && y5 + 1 <= 8){
					x5++;
					y5--;
					while(x5 < x && y5 > y){
						bd[x5][y5].flip();
						x5++;
						y5--;
					}
				}
			}
		}
		// Down Right Direction
		if(down_right){
			int x6 = x, y6 = y;
			x6++;
			y6++;
			while(bd[x6][y6].is_black() && x6 + 1 <= 8 && y6 <= 8){
				x6++;
				y6++;
				if(bd[x6][y6].is_white() && x6 + 1 <= 8 && y6 <= 8){
					x6--;
					y6--;
					while(x6 > x && y6 > y){
						bd[x6][y6].flip();
						x6--;
						y6--;
					}
				}
			} 
		}
	}

	// Depending on colors turn set piece in target location and increment turn counter.
	if(last_mover() == COMPUTER){bd[x][y].set_black();}
	if(last_mover() == HUMAN){bd[x][y].set_white();}	
}

// is_legal function returns whether the move is legal or not. Again looking in all possible directions.
bool Othello::is_legal(const std::string& move)const{
	int x, y;
	int i, j;
	if(move == "xx"){return true;}
	x = char_to_int(move.substr(0,1));
	if(x == 10){return false;}
	y = atoi(move.substr(1,2).c_str());
	y--;	
	bool check = false;
	if(bd[x][y].is_black() || bd[x][y].is_white()){return false;}

	if(check == false){
		if(last_mover() == COMPUTER){
			// Up Direction
			if(bd[x][y-1].is_white() && y - 1 >= -1){
				int y1 = y;
				y1--;
				while(bd[x][y1].is_white() && y1 - 1 >= -1){
					y1--;
					if(bd[x][y1].is_black() && y1 -1 >= -1){check = true;}
				}
			}
			// Down Direction
			if(bd[x][y + 1].is_white() && y + 1 <= 8){
				int y2 = y;
				y2++;
				while(bd[x][y2].is_white() && y2 + 1 <= 8){
					y2++;
					if(bd[x][y2].is_black() && y2 + 1 <= 8){check = true;}
				}
			}
			// Left Direction
			if(bd[x - 1][y].is_white() && x - 1 >= -1){
				int x1 = x;
				x1--;
				while(bd[x1][y].is_white() && x1 - 1 >= -1){
					x1--;
					if(bd[x1][y].is_black() && x1 - 1 >= -1){check = true;}
				}
			}
			// Right Direction
			if(bd[x + 1][y].is_white() && x + 1 <= 8){
				int x2 = x;
				x2++;
				while(bd[x2][y].is_white() && x2 + 1 <= 8){
					x2++;
					if(bd[x2][y].is_black() && x2 + 1 <= 8){check = true;}
				}
			}
			// Up Left Direction
			if(bd[x - 1][y - 1].is_white() && x - 1 >= -1 && y - 1 >= -1){
				int x3 = x, y3 = y;
				x3--;
				y3--;
				while(bd[x3][y3].is_white() && x3 - 1 >= -1 && y3 - 1 >= -1){
					x3--;
					y3--;
					if(bd[x3][y3].is_black() && x3 - 1 >= -1 && y3 - 1 >= -1){check = true;}
				}
			}
			// Up Right Direction
			if(bd[x + 1][y - 1].is_white() && x + 1 <= 8 && y - 1 >= -1){
				int x4 = x, y4 = y;
				x4++;
				y4--;
				while(bd[x4][y4].is_white() && x4 + 1 <= 8 && y4 - 1 >= -1){
					x4++;
					y4--;
					if(bd[x4][y4].is_black() && x4 + 1 <= 8 && y4 - 1 >= -1){check = true;}
				}
			}
			// Down Left Direction
			if(bd[x - 1][y + 1].is_white() && x - 1 >= -1 && y + 1 <= 8){
				int x5 = x, y5 = y;
				x5--;
				y5++;
				while(bd[x5][y5].is_white() && x5 - 1 >= -1 && y5 + 1 <= 8){
					x5--;
					y5++;
					if(bd[x5][y5].is_black() && x5 - 1 >= -1 && y5 + 1 <= 8){check = true;}
				}
			}
			// Down Right Direction
			if(bd[x + 1][y + 1].is_white() && x + 1 <= 8 && y + 1 <= 8){
				int x6 = x, y6 = y;
				x6++;
				y6++;
				while(bd[x6][y6].is_white() && x6 + 1 <= 8 && y6 + 1 <= 8){
					x6++;
					y6++;
					if(bd[x6][y6].is_black() && x6 + 1 <= 8 && y6 + 1 <= 8){check = true;}
				}
			}
		}
		else{
			// Up Direction
			if(bd[x][y - 1].is_black() && y - 1 >= -1){
				int y1 = y;
				y1--;
				while(bd[x][y1].is_black() && y1 - 1 >= -1){
					y1--;
					if(bd[x][y1].is_white() && y1 - 1 >= -1){check = true;}
				}
			}
			// Down Direction
			if(bd[x][y + 1].is_black() && y + 1 <= 8){
				int y2 = y;
				y2++;
				while(bd[x][y2].is_black() && y2 + 1 <= 8){
					y2++;
					if(bd[x][y2].is_white() && y2 + 1 <= 8){check = true;}
				}
			}
			// Left Direction
			if(bd[x - 1][y].is_black() && x - 1 >= -1){
				int x1 = x;
				x1--;
				while(bd[x1][y].is_black() && x1 - 1 >= -1){
					x1--;
					if(bd[x1][y].is_white() && x1 - 1 >= -1){check = true;}
				}
			}
			// Right Direction
			if(bd[x + 1][y].is_black() && x + 1 <= 8){
				int x2 = x;
				x2++;
				while(bd[x2][y].is_black() && x2 + 1 <= 8){
					x2++;
					if(bd[x2][y].is_white() && x2 + 1 <= 8){check = true;}
				}
			}
			// Up Left Direction
			if(bd[x - 1][y - 1].is_black() && x - 1 >= -1 && y - 1 >= -1){
				int x3 = x, y3 = y;
				x3--;
				y3--;
				while(bd[x3][y3].is_black() && x3 - 1 >= -1 && y3 - 1 >= -1){
					x3--;
					y3--;
					if(bd[x3][y3].is_white() && x3 - 1 >= -1 && y3 - 1 >= -1){check = true;}
				}
			}
			// Up Right Direction
			if(bd[x + 1][y - 1].is_black() && x + 1 <= 8 && y - 1 >= -1){
				int x4 = x, y4 = y;
				x4++;
				y4--;
				while(bd[x4][y4].is_black() && x4 + 1 <= 8 && y4 - 1 >= -1){
					x4++;
					y4--;
					if(bd[x4][y4].is_white() && x4 + 1 <= 8 && y4 - 1 >= -1){check = true;}
				}
			}
			// Down Left Direction
			if(bd[x - 1][y + 1].is_black() && x - 1 >= -1 && y + 1 <= 8){
				int x5 = x, y5 = y;
				x5--;
				y5++;
				while(bd[x5][y5].is_black() && x5 - 1 >= -1 && y5 + 1 <= 8){
					x5--;
					y5++;
					if(bd[x5][y5].is_white() && x5 - 1 >= -1 && y5 + 1 <= 8){check = true;}
				}
			}
			// Down Right Direction
			if(bd[x + 1][y + 1].is_black() && x + 1 <= 8 && y + 1 <= 8){
				int x6 = x, y6 = y;
				x6++;
				y6++;
				while(bd[x6][y6].is_black() && x6 + 1 <= 8 && y6 + 1 <= 8){
					x6++;
					y6++;
					if(bd[x6][y6].is_white() && x6 + 1 <= 8 && y6 + 1 <= 8){check = true;}
				}
			}			
		}
	}

	if(check == true){return true;}
	else{return false;}
}

// Evaluate function
int Othello::evaluate()const{
	int x = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(bd[i][j].is_black()){x++;}
			if(bd[i][j].is_white()){x--;}
		}
	}
	return x;
}
// Game over function
bool Othello::is_game_over()const{
	int pass;
	pass = game::get_pass_count();
	if(pass == 2){return true;}
	else{return false;}
}

// char_to_int allows us to take the letter for the x axis and convert it to the actual
// corrosoponding x int value.
int Othello::char_to_int(std::string c)const{ 
	int s = 10;
	if(c == "A" || c =="a"){s = 0;}
    if(c == "B" || c =="b"){s = 1;}
    if(c == "C" || c =="c"){s = 2;}
    if(c == "D" || c =="d"){s = 3;}
    if(c == "E" || c =="e"){s = 4;}
   	if(c == "F" || c =="f"){s = 5;}
    if(c == "G" || c =="g"){s = 6;}
    if(c == "H" || c =="h"){s = 7;}
    return s;
}

game::who Othello::winning()const{
	int b = 0;
	int w = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(bd[i][j].is_black()){b++;}
			if(bd[i][j].is_white()){w++;}
		}
	}
	cout << "Player 1 Piece Count: " << b << endl;
	cout << "Computer Piece Count: " << w << endl;
	if(b > w){return HUMAN;}
	else if(b < w){return COMPUTER;}
	else if(b == w){return NEUTRAL;}
}

}