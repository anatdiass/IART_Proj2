#include <sstream>
#include "Game.h"

Game::Game() {
    this->board=Board();
    this->validMoves=0;
}

int Game::nrValidMoves(){
    return validMoves;
}

void Game::calculateValidMoves(){
    this->validMoves=0;
    vector<pair<char, vector<int>>> validMoves = getNextValidMoves();
    for (auto & c : validMoves) {
        this->validMoves+=c.second.size();
    }
}

void Game::setBoard(Board board) {
    this->board = board;
}

Board Game::getBoard(){
    return this->board;
}

vector<int> Game::getBlockNextValidMoves(char color){
    vector<int> validMoves;
    Board b = getBoard();

    if(b.verifyReflexionBlockRight(color)){
        validMoves.push_back(RIGTH);
    }
    if(getBoard().verifyReflexionBlockLeft(color)){
        validMoves.push_back(LEFT);
    }
    if(getBoard().verifyReflexionBlockDown(color)){
        validMoves.push_back(DOWN);
    }
    if(getBoard().verifyReflexionBlockUp(color)){
        validMoves.push_back(UP);
    }
    return validMoves;
}

vector<pair<char, vector<int>>> Game::getNextValidMoves(){
    vector<pair<char, vector<int>>> validMoves;

    vector<char> colors = getBoard().getBlocksColors();
    vector<int> colorMoves;
    pair<char, vector<int>> colorPair;

    for (auto & color : colors) {
        colorMoves = getBlockNextValidMoves(color);

        if(!colorMoves.empty()){
            colorPair = make_pair(color,colorMoves);
            validMoves.push_back(colorPair);
        }
    }


    return validMoves;
}

void Game::printValidMoves(){

    vector<pair<char, vector<int>>> validMoves = getNextValidMoves();

    //PRINT VALID MOVES
    cout << "VALID MOVES " <<endl;

    for (auto & c : validMoves) {
        cout << "Color: " << c.first << endl;

        for (auto & d : c.second) {
            cout << "\tMove: " << d << endl;
        }
        cout << endl;
    }
}

bool Game::verifyPlay(char color, int move){
    vector<pair<char, vector<int>>> allMoves = getNextValidMoves();

    for (auto & blockMoves : allMoves) {

        if (blockMoves.first == color){

            bool found;

            for (auto & currMove : blockMoves.second) {
                if(currMove == move){
                    found = true;
                }
            }

            if(!found){
                cout << "Move not possible " << endl;
                return false;
            }
            else return true;
        }

    }
    cout << "Color not found " << endl;
    return false;
}

void Game::play(char color, int move){

    switch(move){
        case RIGTH:
            board.reflexionBlockRight(color);
            break;
        case LEFT:
            board.reflexionBlockLeft(color);
            break;
        case DOWN:
            board.reflexionBlockDown(color);
            break;
        case UP:
            board.reflexionBlockUp(color);
            break;
        default:
            break;
    }
    board.defineBlocks();
    calculateValidMoves();
}

bool Game::checkVictory() {
    for(int i=0;i<board.getNumRows();i++){
        for(int j=0;j<board.getNumCols();j++){
            char cellContent = board.getPieceColor(i,j);
            if(cellContent==' ')
                return false;
        }
    }
    return true;
}

bool Game::endGame() {
    if(getNextValidMoves().empty()){

        if(checkVictory()){
            cout << "YOU WON!!!" << endl;
        }
        else cout << "YOU LOST!!!" << endl;
        return true;

    }

    return false;
}

void Game::level1() {
    this->board=Board(4,4);
    this->board.setPiece(3,0,'R');
    board.defineBlocks();
}

void Game::level2(){
    this->board=Board(4,4);

    //Null cells
    board.deleteCell(0,1);
    board.deleteCell(0,2);
    board.deleteCell(1,0);
    board.deleteCell(1,3);
    board.deleteCell(2,0);
    board.deleteCell(2,3);
    board.deleteCell(3,1);
    board.deleteCell(3,2);

    board.setPiece(3,0,'A');
    board.setPiece(2,1,'A');

    board.defineBlocks();
}

void Game::level3(){
    this->board=Board(5,4);

    board.deleteCell(0,2);
    board.deleteCell(0,3);
    board.deleteCell(4,0);
    board.deleteCell(4,1);

    board.setPiece(0,0,'V');
    board.setPiece(4,2, 'A');

    board.defineBlocks();
}

void Game::level4(){
    this->board=Board(8,4);

    board.deleteCell(2,0);
    board.deleteCell(3,0);
    board.deleteCell(0,2);
    board.deleteCell(1,2);
    board.deleteCell(4,2);
    board.deleteCell(5,2);
    board.deleteCell(0,3);
    board.deleteCell(1,3);
    board.deleteCell(4,3);
    board.deleteCell(5,3);

    //Yellow pieces
    board.setPiece(0,0,'A');
    board.setPiece(0,1,'A');
    board.setPiece(1,0,'A');
    board.setPiece(1,1,'A');
    board.setPiece(2,3,'A');

    //Blue piece
    board.setPiece(2,2,'B');

    //Red piece
    board.setPiece(6,3,'V');

    board.defineBlocks();
}

void Game::level5(){
    this->board=Board(8,4);

    //Yellow piece
    board.setPiece(0,0,'A');

    //Blue pieces
    board.setPiece(1,0,'B');
    board.setPiece(2,0,'B');

    //Green piece
    board.setPiece(3,0,'G');

    //Red pieces
    board.setPiece(6,3,'V');
    board.setPiece(7,3,'V');

    board.defineBlocks();
}

void Game::level6(){
    board=Board(8,7);

    //Blue piece
    board.setPiece(0,2,'B');

    //Yellow piece
    board.setPiece(3,1,'A');

    //Cyan piece
    board.setPiece(5,1,'C');

    //Green pieces
    board.setPiece(0,4,'G');
    board.setPiece(1,3,'G');
    board.setPiece(1,4,'G');
    board.setPiece(1,5,'G');

    //Red pieces
    board.setPiece(4,3,'R');
    board.setPiece(4,5,'R');
    board.setPiece(4,6,'R');
    board.setPiece(5,6,'R');

    board.defineBlocks();
}

void Game::level7(){
    board=Board(7,6);

    board.deleteCell(0,0);
    board.deleteCell(0,0);
    board.deleteCell(0,2);
    board.deleteCell(0,3);
    board.deleteCell(0,4);
    board.deleteCell(0,5);
    board.deleteCell(1,5);
    board.deleteCell(2,5);
    board.deleteCell(3,5);
    board.deleteCell(6,5);
    board.deleteCell(6,4);

    //Yellow
    board.setPiece(0,1,'A');
    board.setPiece(1,0,'A');
    //Green
    board.setPiece(3,0,'G');
    //Blue
    board.setPiece(2,2,'B');
    //Purple
    board.setPiece(4,2,'P');
    //Cyan
    board.setPiece(3,4,'C');
    board.setPiece(4,4,'C');
    board.setPiece(4,5,'C');
    board.setPiece(5,3,'C');
    board.setPiece(5,4,'C');
    board.setPiece(5,5,'C');

    //Red
    board.setPiece(6,1,'R');

    board.defineBlocks();
}


void Game::level8(){
    board=Board(10,8);

    board.deleteCell(0,0);
    board.deleteCell(1,0);
    board.deleteCell(2,0);
    board.deleteCell(3,0);
    board.deleteCell(2,1);
    board.deleteCell(2,2);
    board.deleteCell(4,2);
    board.deleteCell(5,2);
    board.deleteCell(6,0);
    board.deleteCell(7,0);
    board.deleteCell(7,1);
    board.deleteCell(7,2);
    board.deleteCell(0,7);
    board.deleteCell(1,7);
    board.deleteCell(2,7);
    board.deleteCell(3,7);
    board.deleteCell(4,7);
    board.deleteCell(5,7);
    board.deleteCell(6,7);
    board.deleteCell(7,7);

    //Green
    board.setPiece(1,3,'G');

    //Purple
    board.setPiece(2,6,'P');

    //Cyan
    board.setPiece(2,3,'C');
    board.setPiece(3,3,'C');

    //Red
    board.setPiece(3,1,'R');
    board.setPiece(3,2,'R');
    board.setPiece(4,0,'R');
    board.setPiece(4,1,'R');

    //Yellow
    board.setPiece(5,3,'A');

    //Blue
    board.setPiece(8,7,'B');

    board.defineBlocks();
}

void Game::chooseLevel() {
    int choice;
    cout << " ______________________________________ " << endl;
    cout << "|- Choose one of the available levels -|" << endl;
    cout << "| Level 1 (Warm Up)                    |" << endl;
    cout << "| Level 2 (Beginner)                   |" << endl;
    cout << "| Level 3 (Beginner)                   |" << endl;
    cout << "| Level 4 (Easy)                       |" << endl;
    cout << "| Level 5 (Easy)                       |" << endl;
    cout << "| Level 6 (Intermediate)               |" << endl;
    cout << "| Level 7 (Medium)                     |" << endl;
    cout << "| Level 8 (Hard)                       |" << endl;
    cout << "|______________________________________|" << endl;
    cout << "\nChoice: ";
    cin>>choice;

    switch(choice){
        case 1:
            level1();
            break;
        case 2:
            level2();
            break;
        case 3:
            level3();
            break;
        case 4:
            level4();
            break;
        case 5:
            level5();
            break;
        case 6:
            level6();
            break;
        case 7:
            level7();
            break;
        case 8:
            level8();
            break;
        default:
            break;
    }

}

void Game::loopGame(bool tips) {

    char color;
    int  move;

    board.defineBlocks();
    do{

        board.printBoard();
        calculateValidMoves();
        if(tips) {
            cout << "Possible moves: " << nrValidMoves() << endl;
            printValidMoves();
        }
        //Gets block by color
        cout << "\nChoose the color of your block: "; cin.ignore(1000, '\n');
        cin >> color;

        //check if color is valid
        while(!board.blockExists(color))
        {
            cin.clear();
            cin.ignore();
            cout << "Color does not exist!" << endl << "Choose the color of your block: ";
            cin>>color;
        }

        cout << "Choose one move\n";
        cout << RIGTH << " - Reflexion right\n";
        cout << LEFT << " - Reflexion left\n";
        cout << DOWN << " - Reflexion down\n";
        cout << UP << " - Reflexion up\n";
        cout << "Move: ";
        cin>>move;

        //check if move is valid
        while (!cin.good() || move < 1 || move > 4)
        {
            cin.clear();
            cin.ignore(INT8_MAX, '\n');
            cout << "Not an option" << endl << "Choose one move: ";
            cin>>move;
        }

        if(verifyPlay(color,move)){
            play(color,move);
        }

    }while(!endGame());

    board.printBoard();
    cout << "\nEnd of game!\n";
}
