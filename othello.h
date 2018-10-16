/*************************************************************************
	Wesley Ryder
	11-25-17
	Description: This is the Orthello class, It uses the class space for
		the pieces. This class uses fucntions to run the game like
		make move, display_status etc. Othello  makes an 8 by 8 board.
*************************************************************************/

#include <iostream>
#include <cctype>
#include "game.h"
#include "space.h"
#include "colors.h"
#include <stdlib.h>
#ifndef OTHELLO_H
#define OTHELLO_H

//wrapping the class in savitch namespace.
namespace main_savitch_14
{
	class Othello:public game{
		public:
			// functions required to run the game.
			Othello(){restart();}
			Othello* clone()const{return new Othello(*this);}
			void compute_moves(std::queue<std::string>& moves) const;
			void restart();
			void display_status()const;
			bool is_legal(const std::string& move)const;
			int evaluate()const;
			bool is_game_over()const;
			void make_move(const std::string& move);
			int char_to_int(std::string c)const;
			who winning()const;
		private:
			Space bd[8][8];
			//int pass_count = 0;
	};
}

#endif