#ifndef STATE_H
#define STATE_H

#include "Environment.h"
#include "Agent.h"
#include <tuple>

enum DIRECTION {
	RIGHT,
	LEFT,
	DOWN,
	UP
};


class State{
	Environment board;
	Agent robot;

public:
	State(Environment board, Agent robot);
	State(Environment board, unsigned int x, unsigned int y);
	State(Environment board);

	void showBoard() const;

	unsigned int getBoardWidth() const;
	unsigned int getBoardHeight() const;
	char getBoardCell(unsigned int x, unsigned int y) const;

	unsigned int getRobotX() const;
	unsigned int getRobotY() const;

	void updateEnvironment(Environment newBoard);

	std::tuple<State, double, bool> doReflexion(DIRECTION direction);

	bool operator==(const State& rhs) const;

	~State();
};


/*
namespace std {

	template <>
	struct hash<State> {
		std::size_t operator()(const State& s) const {
			using std::size_t;
			using std::hash;
			using std::string;

			size_t h = 5381;

			h = ((h << 5) + h) + (size_t)s.getRobotX();
			h = ((h << 5) + h) + (size_t)s.getRobotY();

			for (unsigned int row = 0; row < s.getBoardWidth(); row++) {
				for (unsigned int col = 0; col < s.getBoardHeight(); col++) {
					h = ((h << 5) + h) + (size_t)s.getBoardCell(row, col);
				}
			}
			return h;
		}
	};
}*/

#endif