// IrmaMoves.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IrmaMoves.h"
//Done by Alejandro Cabrera
//Florida Poly Id: 8370
//Full ID: U0000008370

int charToInt(char newCase){//This auxillary Function helps with making the
	//char for location on the board become turned into an int for computing purposes
	switch (newCase){
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	default:
		return 0;
	}
}

char **createMapBoard(void) {//This function creates the map board
	char** board = malloc(sizeof(char*) * 8);//Memory allocation for the board
	for (int i = 0; i < 8; i++) {
		board[i] = (char*)malloc(sizeof(char) * 8);//Memory allocation for specific elements in board
	}
	strncpy(board[0], "FF      ", 8);//Setting the Land and Ocean pieces
	strncpy(board[1], " F      ", 8);
	strncpy(board[2], " FF     ", 8);
	strncpy(board[3], "  F     ", 8);
	strncpy(board[4], "  K     ", 8);
	strncpy(board[5], "C  B    ", 8);
	strncpy(board[6], " CC D   ", 8);
	strncpy(board[7], "  C  DD ", 8);
	return board;
};

char** destroyMapBoard(char** board) {//Destroys a precreated board
	for (int i = 0; i < 8; i++) {
		free(board[i]);//Frees each individual node
	}
	free(board);//Frees the whole board from memory
	return NULL;
}

void printMapBoard(char** board) {//Prints out the a precreated board
	printf("========\n");
	for (int i = 0; i < 8; i++) {
		printf("%s", board[i]);//Prints out each individual row
		printf("\n");
	}
	printf("========\n");
	printf("\n");
}

char** predictIrmaChange(char* str, Move* irmaMove) {//Predicts the changes in Irma
	char** board = createMapBoard();
	printMapBoard(board);//Creates and prints a map board
	parseNotationString(str, irmaMove);//Receives the info for the prediction calculation
	board[irmaMove->from_loc.row][charToInt(irmaMove->from_loc.col)] = 'I';//Creates the Irma in the board
	printMapBoard(board);
	irmaMove->current_loc.col = irmaMove->from_loc.col; //Sets Irmas current Location
	irmaMove->current_loc.row = irmaMove->from_loc.row;
	board[irmaMove->from_loc.row][charToInt(irmaMove->from_loc.col)] = ' ';//Takes the I out of the map to not cause bugs
	if (charToInt(irmaMove->from_loc.col) > charToInt(irmaMove->to_loc.col)) {
		for (int i = 0; i < (charToInt(irmaMove->from_loc.col) - charToInt(irmaMove->to_loc.col)); i++) {
			if (board[irmaMove->current_loc.row][irmaMove->current_loc.col]!= ' '){
				irmaMove->irma.ws -= 15;//Case when Irma is moving upwards through land
				irmaMove->irma.wg -= 10;
				irmaMove->current_loc.col -= 1;
			}
			else {
				irmaMove->irma.ws += 10;//Case when Irma is moving upwards through sea
				irmaMove->irma.wg += 5;
				irmaMove->current_loc.col -= 1;
			}
		}
	}
	else if (charToInt(irmaMove->from_loc.col) < charToInt(irmaMove->to_loc.col)) {
		for (int i = 0; i < (charToInt(irmaMove->to_loc.col) - charToInt(irmaMove->from_loc.col)); i++) {
			if (board[irmaMove->current_loc.row][irmaMove->current_loc.col]!=' ') {
				irmaMove->irma.ws -= 15;//Case when Irma is moving downwards through land
				irmaMove->irma.wg -= 10;
				irmaMove->current_loc.col += 1;
			}
			else {
				irmaMove->irma.ws += 10;//Case when Irma is moving downwards through sea
				irmaMove->irma.wg += 5;
				irmaMove->current_loc.col += 1;
			}
		}
	}

	if (irmaMove->from_loc.row > irmaMove->to_loc.row) {
		if (board[irmaMove->current_loc.row][irmaMove->current_loc.col]!=' ') {
			irmaMove->irma.ws -= 2;//Case when Irma is moving left through land
			irmaMove->irma.wg -= 1;
			irmaMove->current_loc.row -= 1;
		}
		else {
			irmaMove->irma.ws += 6;//Case when Irma is moving left through Sea
			irmaMove->irma.wg += 3;
			irmaMove->current_loc.row -= 1;
		}
	}
	else if (irmaMove->from_loc.row < irmaMove->to_loc.row) {
		if (board[irmaMove->current_loc.row][irmaMove->current_loc.col]!=' ') {
			irmaMove->irma.ws -= 2;//Case when Irma is moving right through land
			irmaMove->irma.wg -= 1;
			irmaMove->current_loc.row += 1;
		}
		else {
			irmaMove->irma.ws += 6;//Case when Irma is moving right through Sea
			irmaMove->irma.wg += 3;
			irmaMove->current_loc.row += 1;
		}
	}
	board[irmaMove->current_loc.row][charToInt(irmaMove->current_loc.col)] = 'I';//Set the location of Irma on the board
	printMapBoard(board);//Print current board
	return board;
}

void parseNotationString(char* str, Move* Irma) {//Divides the string into seperate pieces of data
	sscanf(str, "%c%d %d %d %c%d", &Irma->from_loc.col, &Irma->from_loc.row, &Irma->irma.ws, &Irma->irma.wg, &Irma->to_loc.col, &Irma->to_loc.row);//Breaks the str into proper pieces to be used
	Irma->current_loc.row = -1;//Sets current loc row to an unknown
	Irma->current_loc.col = 'x';//Sets current loc col to an unknown
}

double difficultyRating(void) {//This project was very useful for learning how to properly code
	// and how structs and functions connect properly
	double x = 4.3;
	return x;
}

double hoursSpent(void) { //This was a long one
	double y = 11;
	return y;
}
