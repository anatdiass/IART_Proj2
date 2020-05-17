#include "State.h"
#include <stdexcept>
#include <algorithm>

State::State(Environment initBoard, Agent initRobot) : board(initBoard), robot(initRobot) {
	if (initRobot.getX() >= initBoard.width())
		throw invalid_argument("Out of bounds x position.");

	if (initRobot.getY() >= initBoard.height())
		throw invalid_argument("Out of bounds y position.");
}

State::State(Environment initBoard, unsigned int x, unsigned int y) : board(initBoard) {
	if (x >= initBoard.width())
		throw invalid_argument("Out of bounds x position.");

	if (y >= initBoard.height())
		throw invalid_argument("Out of bounds y position.");

	robot = Agent(x, y);
}

State::State(Environment board) : State(board, 0u, 0u) {}

void State::updateEnvironment(Environment newBoard){
	board = newBoard;
}


void State::showBoard() const
{
	board.show();
}

unsigned int State::getBoardWidth() const
{
	return board.width();
}

unsigned int State::getBoardHeight() const
{
	return board.height();
}

char State::getBoardCell(unsigned int x, unsigned int y) const
{
	return board.getCell(x, y);
}

unsigned int State::getRobotX() const
{
	return robot.getX();
}

unsigned int State::getRobotY() const
{
	return robot.getY();
}

tuple<State, double, bool> State::doReflexion(DIRECTION direction)
{
	double reward;
	bool done;

	char cell  = board.getCell(robot.getX(), robot.getY());

	// update position of agent and board
	switch (direction) {
	case UP:
	/*
		if (robot.getY() > 0)
			newRobot.setY(robot.getY() - 1);*/
		if(board.verifyReflexionBlockUp(cell))
			board.reflexionBlockUp(cell);
		break;
	case DOWN:
	/*
		if (robot.getY() < board.height() - 1)
			newRobot.setY(robot.getY() + 1);*/
		if(board.verifyReflexionBlockDown(cell))
			board.reflexionBlockDown(cell);
		break;
	case LEFT:
	/*
		if (robot.getX() > 0)
			newRobot.setX(robot.getX() - 1);*/
		if(board.verifyReflexionBlockLeft(cell))
			board.reflexionBlockLeft(cell);
		break;
	case RIGHT:
	/*
		if (robot.getX() < board.width() - 1)
			newRobot.setX(robot.getX() + 1);*/
		if(board.verifyReflexionBlockRight(cell))
			board.reflexionBlockRight(cell);
		break;
	}

	// update blocks
	board.defineBlocks();

	//new variables
	Environment newBoard = board;
	Agent newRobot = robot;
	

	//TODO -> substituir pelas opcoes
	//char cell = board.getCell(newRobot.getX(), newRobot.getY()); 


/*
	switch (cell) {

		//TODO

	}*/

	// return new State + reward
	State new_State = State(newBoard, newRobot);

	return tuple<State, double, bool>(new_State, reward, done);
}

bool State::operator==(const State & rhs) const
{
	return (board == rhs.board) && (robot == rhs.robot);
}

State::~State() {}