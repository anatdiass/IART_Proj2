#include "Board.h"
using namespace std;

/*CONSTRUCTOR*/
Board::Board() {
    this->nRows=0;
    this->nCols=0;
}

Board::Board(int nRows, int nCols) : nRows(nRows), nCols(nCols) {
    for(int i = 0; i < nRows; i++){
        vector<char> temp;
        for(int j = 0; j < nCols; j++){
            temp.push_back(' ');
        }
        board.push_back(temp);
    }
}

int Board::getNumRows() {
    return this->nRows;
}

int Board::getNumCols() {
    return this->nCols;
}

void Board::deleteCell(int row, int col) {
    setPiece(row, col, '-');
}

void Board::printBorderLines() {
    cout << "   .";
    for (int i=0; i<nCols; i++){
        cout << "_____.";
    }
}

void Board::printHorizontalNumbers() {
    cout << "\n ";
    for(int i=0;i<nCols;i++){
        cout << "     "<<i;
    }
    cout << "\n";
}

void Board::printBoard() {

    printHorizontalNumbers();
    printBorderLines();
    cout << "\n";

    for(int i=0;i<nRows;i++){

        //Print row indice
        cout<<"\n" << i;
        cout << ((i) < 10 ? "  |" : " |");

        //Print cell color
        for(int j=0;j<nCols;j++){
            cout << "  "<< getPieceColor(i, j)<<"  |";
        }

        cout << "\n";
        printBorderLines();
        cout << "\n";
    }
}

/*MANAGE BOARD*/

void Board::setPiece(int row, int col, char color){
    if(row>=0 && col>=0 && row<nRows && col<nCols)
        board.at(row).at(col) = color;
}

char Board::getPieceColor(int row, int col) {
    if(row>=0 && col>=0 && row<nRows && col<nCols)
        return board.at(row).at(col);
    else return (char)0;
}

bool Board::blockExists(char index) {
    for(auto & block : blocks){
        if(block.first==index)
            return true;
    }
    return false;
}

void Board::createBlock(char indexChar) {
    pair<char,vector<pair<int,int>>> block;
    vector<pair<char,vector<pair<int,int>>>>blocks_vec = getBlocks();
    block.first=indexChar;

    vector<pair<int,int>> positions;
    for(int i=0;i<nRows;i++){
        for(int j=0;j<nCols;j++){
            char cellContent = getPieceColor(i,j);
            if(cellContent == indexChar){
                pair<int,int> pos;
                pos.first=i;
                pos.second=j;
                positions.push_back(pos);
            }
        }
    }
    block.second=positions;
    blocks_vec.push_back(block);
    setBlocks(blocks_vec);
}

bool Board::existPositionBlock(const vector<pair<int,int>>& positions, int row, int col) {
    pair<int,int>position;
    position.first=row;
    position.second=col;
    for(const auto & i : positions){
        if(i==position)
            return true;
    }
    return false;
}

void Board::updateBlock(char indexChar, int row, int col) {
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

void Board::defineBlocks() {
    for (int row=0;row<nRows;row++){
        for(int col=0;col<nCols;col++){
            char cellContent = getPieceColor(row,col);
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

vector<pair<char, vector<pair<int, int>>>> Board::getBlocks() {
    return this->blocks;
}

pair<char, vector<pair<int,int>>> Board::getBlock(char blockColor){
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

vector<char> Board::getBlocksColors(){
    vector<char> colors;
    for (auto & block : getBlocks()) {
        colors.push_back(block.first);
    }


    return colors;
}


int Board::getMostRightCell(const vector<pair<int,int>>& positions){
    int maxX=0;
    for(auto & position : positions){
        if(position.second>maxX)
            maxX=position.second;
    }
    return maxX;
}

int Board::getMostLeftCell(const vector<pair<int,int>>&positions){
    int minX=positions[0].second;
    for(auto & position : positions){
        if(position.second<minX)
            minX=position.second;
    }
    return minX;
}

int Board::getMostUpCell(const vector<pair<int, int>>& positions) {
    int minY=positions[0].first;
    for(auto &position: positions){
        if(position.first<minY)
            minY=position.first;
    }
    return minY;
}

int Board::getMostDownCell(const vector<pair<int, int>>& positions) {
    int maxY=0;
    for(auto &position: positions){
        if(position.first>maxY)
            maxY=position.first;
    }
    return maxY;
}

/*VERIFY REFLEXION FUNCTIONS*/


bool Board::verifyReflexionBlockRight(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostRightCell = getMostRightCell(block.second);
    int indexMostLeftCell = getMostLeftCell(block.second);
    int compBetweenCells = indexMostRightCell-indexMostLeftCell;

    //verify if the reflexion is possible
    if((indexMostLeftCell+(2*compBetweenCells)+1)>=nCols)
        return false;
    else{
        //Verify the destination pieces are available
        for(int i=0;i<nrPieces;i++){
            pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col
            int pieceColumn = piece.second;
            int distToMRC = indexMostRightCell - pieceColumn;
            int deltaX = (2*distToMRC) + 1;
            char destinationCell = getPieceColor(piece.first,pieceColumn+deltaX);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }

    }
    return true;
}

bool Board::verifyReflexionBlockLeft(char pieceColor) {

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
            pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col
            int pieceColumn=piece.second;
            int distToMLC =  pieceColumn-indexMostLeftCell;
            int deltaX = (2*distToMLC)+1;
            char destinationCell = getPieceColor(piece.first,pieceColumn-deltaX);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }
    }
    return true;
}

bool Board::verifyReflexionBlockUp(char pieceColor) {

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
            pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col
            int pieceRow=piece.first;
            int distToMUC =  pieceRow-indexMostUpCell;
            int deltaY = (2*distToMUC)+1;
            char destinationCell = getPieceColor(pieceRow-deltaY,piece.second);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }
    }
    return true;
}

bool Board::verifyReflexionBlockDown(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();

    int indexMostDownCell = getMostDownCell(block.second);
    int indexMostUpCell = getMostUpCell(block.second);
    int heightBetweenCells = indexMostDownCell-indexMostUpCell;

    //verify if the reflexion is possible
    if((indexMostUpCell+(2*heightBetweenCells)+1)>=nRows)
        return false;
    else{
        //Verify if the destination pieces are available
        for(int i=0;i<nrPieces;i++){
            pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col
            int pieceRow = piece.first;
            int distToMDC = indexMostDownCell - pieceRow;
            int deltaY = (2*distToMDC) + 1;
            char destinationCell = getPieceColor(pieceRow+deltaY,piece.second);
            if(destinationCell != ' ' || destinationCell=='-')
                return false;
        }
    }

    return true;
}

/*DO REFLEXION FUNCTIONS*/

void Board::reflexionBlockRight(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostRightCell = getMostRightCell(block.second);

    for(int i=0; i<nrPieces; i++){
        pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col
        int pieceColumn = piece.second;
        int distToMRC = indexMostRightCell - pieceColumn;
        int deltaX = (2*distToMRC) + 1;
        setPiece(piece.first, pieceColumn+deltaX, pieceColor);
    }
}

void Board::reflexionBlockLeft(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostLeftCell = getMostLeftCell(block.second);

    for(int i=0;i<nrPieces;i++){
        pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col

        int pieceColumn=piece.second;
        int distToMLC =  pieceColumn-indexMostLeftCell;
        int deltaX = (2*distToMLC)+1;

        setPiece(piece.first, pieceColumn-deltaX, pieceColor);
    }
}

void Board::reflexionBlockUp(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostUpCell = getMostUpCell(block.second);

    for(int i=0;i<nrPieces;i++){
        pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col

        int pieceRow=piece.first;
        int distToMUC =  pieceRow-indexMostUpCell;
        int deltaY = (2*distToMUC)+1;

        setPiece(pieceRow-deltaY, piece.second, pieceColor);
    }
}

void Board::reflexionBlockDown(char pieceColor) {

    pair<char, vector<pair<int,int>>> block = getBlock(pieceColor);
    int nrPieces = block.second.size();
    int indexMostDownCell = getMostDownCell(block.second);

    for(int i=0;i<nrPieces;i++){
        pair<int,int>piece = block.second[i];   //piece.first -> row, piece.second->col
        int pieceRow = piece.first;
        int distToMDC = indexMostDownCell - pieceRow;
        int deltaY = (2*distToMDC) + 1;
        setPiece(pieceRow+deltaY, piece.second, pieceColor);
    }
}



