#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <iostream>
using namespace std;

class Environment{
	vector<vector<char>> board;

	//char-> cor
	//vector<pair<int,int>> -> vetor com posições <y,x>
	vector<pair<char,vector<pair<int,int>>>>blocks;

public:

	Environment(vector<vector<char>> board);

	void printBorderLines() const;
	void printHorizontalNumbers() const;
	void show() const;

	unsigned int width() const;
	unsigned int height() const;

	char getCell(unsigned int x, unsigned int y) const;
	void setCell(unsigned int x, unsigned int y, char cell);

    void setBlocks(vector<pair<char,vector<pair<int,int>>>> blocks){ this->blocks = blocks;}


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

	bool operator==(const Environment& rhs)const;

	~Environment();
};

#endif