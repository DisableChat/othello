/*************************************************************************
	Wesley Ryder
	11-25-17
	Description: This is the space class that has functions to help
		distinquish if the pieces are black white empty etc. it also has
		functions to flip the pices or set them empty etc.
*************************************************************************/

#include <iostream>
#include <queue>
using namespace std;
#ifndef SPACE_H
#define SPACE_H


class Space{
	public:
		//default constructor
		Space();
		// black piece functions
		bool is_black()const;
		void set_black();
		// white pieces functions
		bool is_white()const;
		void set_white();
		void flip();
		// empty piece functions
		bool is_empty()const;
		void set_empty();
		// accesor function
		int get_value(){return value;}

	private:
		int value;
};

#endif
