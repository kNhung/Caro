﻿#include "header.h"

_POINT _A[BOARD_SIZE][BOARD_SIZE];
_POINT _MENU[MENU_SIZE] = {
	_POINT{CENTER_X,CENTER_Y - 3,1},
	_POINT{CENTER_X,CENTER_Y + 1,2},
	_POINT{CENTER_X,CENTER_Y + 5,3},
	_POINT{CENTER_X,CENTER_Y + 9,4},
	_POINT{CENTER_X,CENTER_Y + 13,5},
};
_POINT _LAST_POINT;

bool isLoad = 0;
bool isMenu = 0;
string _file_name = "";
string PLAYER1, PLAYER2;
int SCORE_X, SCORE_O;
int _MODEPLAY;
bool _TURN;
int _COMMAND;
int _X, _Y;
int MODE; 
bool NEW_GAME;
fstream _MATCH_LIST_FILE;
int MATCH_LIST_SIZE = 0;
vector<_LIST> _MATCH_LIST;
int SUB_ML_SIZE;
vector<_LIST> _SUB_ML;
int SOUND;
bool _EXIT;