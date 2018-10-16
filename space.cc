/*************************************************************************
	Wesley Ryder
	11-25-17
	Description: This is the implemenation of the space class which helps
		change the pieces and idetifies if theyre white or black etc or
		empty. as well as the flip function.
*************************************************************************/
#include <iostream>
#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <queue>      // Provides queue<string>
#include <string> 
#include "space.h"
using namespace std;

// defualt constructor
Space::Space(){value = 0;}

// is black function
bool Space::is_black()const{
	if(value == 2){return true;}
	else{return false;}
}

// set piece black function
void Space::set_black(){value = 2;}

// is white function
bool Space::is_white()const{
	if(value == 1){return true;}
	else{return false;}
}

// set piece white function
void Space::set_white(){value = 1;}

// flip piece color function
void Space::flip(){
	if(value == 1){value = 2;}
	else if(value == 2){value = 1;}
}

// is empty function
bool Space::is_empty()const{
	if(value == 0){return true;}
	else{return false;}
}

// set space empty function
void Space::set_empty(){value = 0;}
