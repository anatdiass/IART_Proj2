#include <iostream>
#include <vector>

#include "Environment.h"
#include "Agent.h"
#include "State.h"
// #include "qlearner.h"

int main() {
	// setup game

	vector<vector<char>> initBoard = {
		{'a', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	};

	Environment environment = Environment(initBoard);
	Agent robot(0, 0);
	State game(environment, robot);

	cout << "Nr blocos: " << environment.getBlocks().size()<<endl;
	if(environment.blockExists('a'))
	cout << "Existe";
	game.showBoard();

	//environment.reflexionBlockRight('a');
	//environment.reflexionBlockLeft('a');
	//environment.reflexionBlockDown('a');
	environment.reflexionBlockUp('a');


	environment.defineBlocks();
	game.updateEnvironment(environment);
	game.showBoard();

	cout << "\nAction enum map:\n"
	 	<< " 1 -> RIGHT\n"
	 	<< " 2 -> LEFT\n"
	 	<< " 3 -> DOWN\n"
	 	<< " 4 -> UP\n";

	// start qlearning
/*
	unsigned int number_actions = 4;
	unsigned int number_episodes = 2000;
	unsigned int number_steps = 100;
	double alpha_initial = 1.0;
	double alpha_final = 0.02;
	double gamma = 1.0;
	double epsilon = 0.1;

	cout << "\nStarting q-learning with:"
		<< "\n number episodes: " << number_episodes
		<< "\n number steps/episode: " << number_steps
		<< "\n initial alpha: " << alpha_initial
		<< "\n final alpha: " << alpha_final
		<< "\n gamma: " << gamma
		<< "\n epsilon (pr. of taking random action): " << epsilon
		<< endl;

	qlearner ql(number_actions, number_episodes, number_steps, alpha_initial, alpha_final, gamma, epsilon);
	ql.qLearn(game, true);

	getchar();*/

	return 0;
}
