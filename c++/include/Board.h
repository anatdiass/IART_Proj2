#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Board {
public:
private:
    int nRows;
    int nCols;
    vector<vector<char>> board;
    vector<pair<char,vector<pair<int,int>>>>blocks;
public:

    /**
     * Default constructor
     */
    Board();

    /**
     * Creates an empty board game
     * @param nRows number of rows
     * @param nCols number of colums
     */
    Board(int nRows, int nCols);

    /**
     * Return the number of rows of the board
     * @return Number of rows
     */
    int getNumRows();

    /**
     * Return the number of columns of the board
     * @return Number of columns
     */
    int getNumCols();

    /**
     * Set the color of a piece as '-'
     * @param row Vertical coordinate
     * @param col Horizontal coordinate
     */
    void deleteCell(int row, int col);

    /**
     * Prints all the board horizontal lines
     */
    void printBorderLines();

    /**
     * Print columns indexes
     */
    void printHorizontalNumbers();

    /**
     * Print the entire board with cells content
     */
    void printBoard();

    /**
     * Defines a color for specific position
     * @param row Vertical coordinate
     * @param col Horizontal coordinate
     * @param color Color of piece
     */
    void setPiece(int row, int col, char color);

    /**
     * Returns the color of a specific position
     * @param row Vertical coordinate
     * @param col Horizontal coordinate
     * @return Color of piece
     */
    char getPieceColor(int row, int col);

    /**
     * Verify if the block of a certain color was already created
     * @param index Color of block
     * @return True if the block was already created
     */
    bool blockExists(char index);

    /**
     * Create a new block for the specified color
     * @param indexChar Color of block
     */
    void createBlock(char indexChar);

    /**
     * Verify if a position was already added to the block
     * @param positions Positions of all the block's pieces
     * @param row Vertical coordinate of new piece
     * @param col Horizontal coordinate of new piece
     * @return True if the position of new piece was already added to the block
     */
    static bool existPositionBlock(const vector<pair<int,int>>& positions, int row, int col);

    /**
     * Add a new piece to an existing block
     * @param indexChar Color of block
     * @param row Vertical coordinate of new piece
     * @param col Horizontal coordinate of new piece
     */
    void updateBlock(char indexChar, int row, int col);

    /**
     * Creates all blocks existing on the game board and add them to the blocks structure
     */
    void defineBlocks();

    /**
     * Returns all the blocks of the board
     * @return Board's blocks
     */
    vector<pair<char,vector<pair<int,int>>>> getBlocks();

    void setBlocks(vector<pair<char,vector<pair<int,int>>>> blocks){ this->blocks = blocks;}

    /**
     * Returns the colors of all the blocks of the board
     * @return Board's blocks' colors
     */
    vector<char> getBlocksColors();

    /**
     * Gets the block of a certain color
     * @param blockColor Color of block
     * @return Block
     */
    pair<char, vector<pair<int,int>>> getBlock(char blockColor);

    /**
     * Gets the block's cell with higher horizontal coordinate
     * @param positions All the positions of a block
     * @return Horizontal coordinate of the cell
     */
    static int getMostRightCell(const vector<pair<int,int>>& positions);

    /**
     * Gets the block's cell with lower horizontal coordinate
     * @param positions All the positions of a block
     * @return Horizontal coordinate of the cell
     */
    static int getMostLeftCell(const vector<pair<int,int>>& positions);

    /**
     * Gets the block's cell with lower vertical coordinate
     * @param positions All the positions of a block
     * @return Vertical coordinate of the cell
     */
    static int getMostUpCell(const vector<pair<int,int>>& positions);

    /**
     * Gets the block's cell with higher vertical coordinate
     * @param positions All the positions of a block
     * @return Vertical coordinate of the cell
     */
    static int getMostDownCell(const vector<pair<int,int>>& positions);

    /**
     * Verify if the Right reflexion of a block is possible
     * @param pieceColor Color of the block 
     * @return True if the reflexion is possible
     */
    bool verifyReflexionBlockRight(char pieceColor);

    /**
     * Verify if the Left reflexion of a block is possible
     * @param pieceColor Color of the block 
     * @return True if the reflexion is possible
     */
    bool verifyReflexionBlockLeft(char pieceColor);

    /**
     * Verify if the Up reflexion of a block is possible
     * @param pieceColor Color of the block 
     * @return True if the reflexion is possible
     */
    bool verifyReflexionBlockUp(char pieceColor);

    /**
     * Verify if the Down reflexion of a block is possible
     * @param pieceColor Color of the block 
     * @return True if the reflexion is possible
     */
    bool verifyReflexionBlockDown(char pieceColor);

    /**
     * Right reflexion of a block
     * @param pieceColor Color of the block 
     */
    void reflexionBlockRight(char pieceColor);

    /**
     * Left reflexion of a block
     * @param pieceColor Color of the block 
     */
    void reflexionBlockLeft(char pieceColor);

    /**
     * Up reflexion of all the pieces with the same color of indicated piece
     * @param pieceColor Color of the block 
     */
    void reflexionBlockUp(char pieceColor);

    /**
     * Down reflexion of all the pieces with the same color of indicated piece
     * @param pieceColor Color of the block 
     */
    void reflexionBlockDown(char pieceColor);


};


#endif //UNTITLED_BOARD_H
