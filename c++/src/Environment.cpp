#include "Environment.h"
#include <iostream>

Environment::Environment(vector<vector<char>> board) : board(board) {
    defineBlocks();
}

void Environment::printBorderLines() const{
    cout << "   .";
    for (unsigned int i=0; i<width(); i++){
        cout << "_____.";
    }
}

void Environment::printHorizontalNumbers() const {
    cout << "\n ";
    for(unsigned int i=0;i<width();i++){
        cout << "     "<<i;
    }
    cout << "\n";
}

void Environment::show() const {

    this->printHorizontalNumbers();
    this->printBorderLines();
    cout << "\n";

    for(unsigned int y=0;y<height();y++){

        //Print row indice
        cout<<"\n" << y;
        cout << ((y) < 10 ? "  |" : " |");

        //Print cell color
        for(unsigned int x=0;x<width();x++){
            cout << "  "<< getCell(x, y)<<"  |";
        }

        cout << "\n";
        printBorderLines();
        cout << "\n";
    }
}

unsigned int Environment::height() const{
	return (unsigned int)board.size();
}

unsigned int Environment::width() const{
	return (unsigned int)board[0].size();
}

char Environment::getCell(unsigned int x, unsigned int y) const{
	if (x >= width())
		cout << ("Invalid x position.");

	if (y >= height())
		cout << ("Invalid y position.");

	return board[y][x];
}

void Environment::setCell(unsigned int x, unsigned int y, char cell){
	if (x >= width())
		cout << ("Invalid x position.");

	else if (y >= height())
		cout << ("Invalid y position.");

	else board[y][x] = cell;
}

bool Environment::operator==(const Environment & rhs) const{
	return board == rhs.board;
}


bool Environment::blockExists(char index) {
    for(auto & block : blocks){
        if(block.first==index)
            return true;
    }
    return false;
}

void Environment::createBlock(char indexChar) {
    pair<char,vector<pair<int,int>>> block;
    vector<pair<char,vector<pair<int,int>>>>blocks_vec = getBlocks();
    block.first=indexChar;

    vector<pair<int,int>> positions;
    for(unsigned int y=0;y<height();y++){
        for(unsigned int x=0;x<width();x++){
            char cellContent = getCell(x,y);
            if(cellContent == indexChar){
                pair<int,int> pos;
                pos.first=y;
                pos.second=x;
                positions.push_back(pos);
            }
        }
    }
    block.second=positions;
    blocks_vec.push_back(block);
    setBlocks(blocks_vec);
}

bool Environment::existPositionBlock(const vector<pair<int,int>>& positions, int row, int col) {
    pair<int,int>position;
    position.first=row;
    position.second=col;
    for(const auto & i : positions){
        if(i==position)
            return true;
    }
    return false;
}

void Environment::updateBlock(char indexChar, int row, int col) {
    for(auto & block : blocks){
        if(block.first==indexChar){
            pair<int,int> pos;
            pos.first=row;
            pos.second=col;
            if(!existPositionBlock(block.second, row, col))
                block.second.push_back(pos);
        }
    }
}

void Environment::defineBlocks() {
    for (unsigned int row=0;row<height();row++){
        for(unsigned int col=0;col<width();col++){
            char cellContent = getCell(col,row);
            if(cellContent!=' '){
                //new block
                if(!blockExists(cellContent)){
                    createBlock(cellContent);
                }
                //Add to existing block
                else{
                    updateBlock(cellContent,row,col);
                }
            }
        }
    }
}

vector<pair<char, vector<pair<int, int>>>> Environment::getBlocks() {
    return this->blocks;
}

pair<char, vector<pair<int,int>>> Environment::getBlock(char blockColor){
    if(blockExists(blockColor)) {
        for (auto & block : blocks) {
            if (block.first == blockColor)
                return block;
        }
    }

    pair<char,vector<pair<int,int>>> nullPair;
    pair<int,int> null;
    null.first=-1;null.second=-1;
    vector<pair<int,int>> nullVec; nullVec.push_back(null);
    nullPair.first=(char)0;
    nullPair.second=nullVec;
    return nullPair;

}

vector<char> Environment::getBlocksColors(){
    vector<char> colors;
    for (auto & block : getBlocks()) {
        colors.push_back(block.first);
    }
    return colors;
}


int Environment::getMostRightCell(const vector<pair<int,int>>& positions){
    int maxX=0;
    for(auto & position : positions){
        if(position.second>maxX)
            maxX=position.second;
    }
    return maxX;
}

int Environment::getMostLeftCell(const vector<pair<int,int>>&positions){
    int minX=positions[0].second;
    for(auto & position : positions){
        if(position.second<minX)
            minX=position.second;
    }
    return minX;
}

int Environment::getMostUpCell(const vector<pair<int, int>>& positions) {
    int minY=positions[0].first;
    for(auto &position: positions){
        if(position.first<minY)
            minY=position.first;
    }
    return minY;
}

int Environment::getMostDownCell(const vector<pair<int, int>>& positions) {
    int maxY=0;
    for(auto &position: positions){
        if(position.first>maxY)
            maxY=position.first;
    }
    return maxY;
}

/*VERIFY REFLEXION FUNCTIONS*/


bool Environment::verifyReflexionBlockRight(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    unsigned int indexMostRightCell = getMostRightCell(block.second);
    unsigned int indexMostLeftCell = getMostLeftCell(block.second);
    unsigned int compBetweenCells = indexMostRightCell-indexMostLeftCell;

    //verify if the reflexion is possible
    if((indexMostLeftCell+(2*compBetweenCells)+1)>=width())
        return false;
    else{
        //Verify the destination pieces are available
        for(int i=0;i<nrPieces;i++){
            pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x
            int pieceColumn = piece.second;
            int distToMRC = indexMostRightCell - pieceColumn;
            int deltaX = (2*distToMRC) + 1;
            char destinationCell = getCell(pieceColumn+deltaX,piece.first);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }

    }
    return true;
}

bool Environment::verifyReflexionBlockLeft(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();

    int indexMostRightCell = getMostRightCell(block.second);
    int indexMostLeftCell = getMostLeftCell(block.second);
    int compBetweenCells = indexMostRightCell-indexMostLeftCell;

    //verify if the reflexion is possible
    if((indexMostRightCell-(2*compBetweenCells+1))<0)
        return false;
    else{
        //Verify the destination pieces are available
        for(int i=0;i<nrPieces;i++){
            pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x
            int pieceColumn=piece.second;
            int distToMLC =  pieceColumn-indexMostLeftCell;
            int deltaX = (2*distToMLC)+1;
            char destinationCell = getCell(pieceColumn-deltaX, piece.first);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }
    }
    return true;
}

bool Environment::verifyReflexionBlockUp(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();

    int indexMostDownCell = getMostDownCell(block.second);
    int indexMostUpCell = getMostUpCell(block.second);
    int heightBetweenCells = indexMostDownCell-indexMostUpCell;

    //verify if the reflexion is possible
    if((indexMostDownCell-(2*heightBetweenCells+1))<0)
        return false;
    else{
        //Verify if the destination pieces are available
        for(int i=0;i<nrPieces;i++){
            pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x
            int pieceRow=piece.first;
            int distToMUC =  pieceRow-indexMostUpCell;
            int deltaY = (2*distToMUC)+1;
            char destinationCell = getCell(piece.second, pieceRow-deltaY);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }
    }
    return true;
}

bool Environment::verifyReflexionBlockDown(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();

    unsigned int indexMostDownCell = getMostDownCell(block.second);
    unsigned int indexMostUpCell = getMostUpCell(block.second);
    unsigned int heightBetweenCells = indexMostDownCell-indexMostUpCell;

    //verify if the reflexion is possible
    if((indexMostUpCell+(2*heightBetweenCells)+1)>=height())
        return false;
    else{
        //Verify if the destination pieces are available
        for(int i=0;i<nrPieces;i++){
            pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x
            int pieceRow = piece.first;
            int distToMDC = indexMostDownCell - pieceRow;
            int deltaY = (2*distToMDC) + 1;
            char destinationCell = getCell(piece.second, pieceRow+deltaY);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }
    }

    return true;
}

/*DO REFLEXION FUNCTIONS*/

void Environment::reflexionBlockRight(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostRightCell = getMostRightCell(block.second);

    for(int i=0; i<nrPieces; i++){
        pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x
        int pieceColumn = piece.second;
        int distToMRC = indexMostRightCell - pieceColumn;
        int deltaX = (2*distToMRC) + 1;
        setCell(pieceColumn+deltaX, piece.first, pieceColor);
    }
}

void Environment::reflexionBlockLeft(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostLeftCell = getMostLeftCell(block.second);

    for(int i=0;i<nrPieces;i++){
        pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x

        int pieceColumn=piece.second;
        int distToMLC =  pieceColumn-indexMostLeftCell;
        int deltaX = (2*distToMLC)+1;

        setCell(pieceColumn-deltaX,piece.first, pieceColor);
    }
}

void Environment::reflexionBlockUp(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostUpCell = getMostUpCell(block.second);

    for(int i=0;i<nrPieces;i++){
        pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x

        int pieceRow=piece.first;
        int distToMUC =  pieceRow-indexMostUpCell;
        int deltaY = (2*distToMUC)+1;

        setCell(piece.second, pieceRow-deltaY,pieceColor);
    }
}

void Environment::reflexionBlockDown(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostDownCell = getMostDownCell(block.second);

    for(int i=0;i<nrPieces;i++){
        pair<int,int>piece = block.second[i];   //piece.first -> y, piece.second->x
        int pieceRow = piece.first;
        int distToMDC = indexMostDownCell - pieceRow;
        int deltaY = (2*distToMDC) + 1;
        setCell(piece.second,pieceRow+deltaY, pieceColor);
    }
}

Environment::~Environment(){}
