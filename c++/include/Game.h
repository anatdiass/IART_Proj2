#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include <string>

#include "Board.h"

int const RIGTH = 1;
int const LEFT = 2;
int const DOWN = 3;
int const UP = 4;

class Game {
private:
    Board board;
    int validMoves;

public:
    /**
     * Default constructor
     */
    Game();

    /**
     * Return the number of valid moves
     * @return Total of valid moves
     */
    int nrValidMoves();

    /**
     * Calculates the number of valid moves
     */
    void calculateValidMoves();

    /**
     * Define the game board
     * @param board Board
     */
    void setBoard(Board board);

    /**
     * Get the current board of the game
     *
     * @return Board
     */

    Board getBoard();

    /**
     * Get the next valid moves for a block
     * @param color Color of the block
     * @return vector with the valid the moves
     */
    vector<int> getBlockNextValidMoves(char color);

    /**
     * Get all the next valid moves
     * @return vector with the valid the moves
     */
    vector<pair<char, vector<int>>> getNextValidMoves();

    /**
     * Prints on the screen the valid moves of the game
     */
    void printValidMoves();

    /**
     * Verify if a play is valid
     * @param color Color of the block
     * @param move type of move
     * @return True if the play is valid
     */
    bool verifyPlay(char color, int move);

    /**
     * Make a play
     * @param color Color of the block
     * @param move type of move
     */
    void play(char color, int move);

    /**
    * Verify if the board is full (all the pieces have a color)
    * @return True if the board is full
    */
    bool checkVictory();

    /**
     * Verify if the game is over (victory or loss)
     * @return True if the game is over
     */
    bool endGame();

    /**
     * Defines the board of first level
     */
    void level1();

    /**
     * Defines the board of second level
     */
    void level2();

    /**
     * Defines the board of third level
     */
    void level3();

    /**
     * Defines the board of fourth level
     */
    void level4();

    /**
     * Defines the board of fifth level
     */
    void level5();

    /**
     * Defines the board of sixth level
    */
    void level6();

    /**
     * Defines the board of seventh level
    */
    void level7();

    /**
     * Defines the board of eigth level
     */
    void level8();

    /**
     * Allows the user to choose which level to play
     */
    void chooseLevel();

    /**
     * Game main loop
     */
    void loopGame(bool tips);
};


#endif //UNTITLED_GAME_H
