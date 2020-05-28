# -*- coding: utf-8 -*-
"""
Created on Wed May 27 01:08:53 2020

@author: Maria Caldeira
"""
import numpy as np
import json
import sys

class Agent(object):
    def __init__(self, game, algorithm, q_table=dict(), learning_rate=5e-1, discount=9e-1, epsilon=5e-1):
        """Initialize agent with properties
        - qtable is json table with Q values Q(s,a)
        - game is reference to game being played
        - player -> (color, move)
        - learning_rate is alpha value for gradient update
        - discount is discount factor for future expected rewards
        - epsilon is probability of exploration in epsilon greedy strategy
        """
        self.game = game
        self.q_table = q_table
        self.learning_rate = learning_rate
        self.discount = discount
        self.epsilon = epsilon
        self.algorithm = algorithm

        
    def qvalue(self, state):
        if state not in self.q_table:
            # Initialize Q-value at 0
            self.q_table[state] = 0.0
        return self.q_table[state]

    def choose_max_state(self, values):
        if len(values)>0:
            return np.random.choice(values)
        return 0

    def get_state_index(self, state, states):
        for i in range(len(states)):
            st = states[i]
            if state == st:
                return i

    def get_action_move(self, actions, state_index):
        prev_sum = 0
        sum = 0
        action_index = None
        ret_move = None
        for i in range(len(actions)):
            prev_sum = sum
            action = actions[i]
            moves = action[1]
            n_moves = len(moves)
            sum = sum + len(moves)
            if state_index>prev_sum and state_index<=sum:
                action_index = i
                for j in range(n_moves):
                    ret_move = moves[state_index - prev_sum - 1]
        return action_index, ret_move

    def count_pieces_state(self, state):
        count = 0
        for i in range(len(state)):
            for j in range(len(state[i])):
                pos = state[i][j]
                if(pos != " "):
                    count = count + 1
        return count

    def step(self, verbose=True):
        """Agent makes one step."""

        self.game.print_board()

        states, actions, winner  = self.game.get_open_moves()

        
        

        oldBoard = self.game.get_state(self.game.board)
        state, action, move = self.next_move(states, actions)        
        state_index = self.get_state_index(state, states)
        reward = self.reward(winner)
        self.game.print_board()
        #self.update(reward, winner, state, states, actions)

        if verbose:
            print("=========")
            print("Previous state: " + str(oldBoard))
            print("Action: " + str(action))
            print("Move: " + str(move))
            print("Winner: " + str(winner))
            print("Current state: " + str(state))
            print('Q value: {}'.format(self.qvalue(state_index)))
            self.game.print_board()
            print("Reward: " + str(reward))
        return (winner, reward)

    def next_move(self, states, actions):
        
        """Selects next move in MDP following e-greedy strategy."""
        
        for i in range(len(states)):
            state = states[i]
        # Exploit
        i = self.optimal_next(states)
        if np.random.random_sample() < self.epsilon and len(states)>0:
            # Explore
            if len(states) < 1:
                i = np.random.randint(len(states),1)
            elif len(states) == 1:
                i = 1
            else:
                i = np.random.randint(1, len(states))
        action_index, move = self.get_action_move(actions,i)
        
        if states == []:
            return [], [], move
        return states[i-1], actions[action_index], move

    def optimal_next(self, states):
        """Selects optimal next move.
        Input
        - states list of possible next states
        Output
        - index of next state that produces maximum value
        """
        values = []
        max = 0
        for i in range(len(states)):
            if self.count_pieces_state(states[i]) > max:
                values.append(i+1)

        # values = [self.qvalue(s) for s in states]
        return self.choose_max_state(values)

    def reward(self, winner):
        """Calculates reward for different end game conditions.
        - win is 1.0
        - loss is -1.0
        - unfinished is 0.0"""

        if winner == None:   # winner = none --> not endgame
            return 0
        elif winner == True:
            return 1.0
        else:
            return -1.0 

    def update(self, reward, winner, state, states, actions):
        """Updates q-value.
        Update uses recorded observations of performing a
        certain action in a certain state and continuing optimally from there.
        """

        # Finding estimated future value by finding max(Q(s', a'))
        # If terminal condition is reached, future reward is 0
        future_val = 0
        state_index = self.get_state_index(state, states)
        if winner == None:
            future_states = states
            i = self.optimal_next(future_states)
            future_state = future_states[i-1]
            future_st_index = self.get_state_index(future_state, future_states)
            future_val = self.qvalue(future_st_index)
        # Q-value update
        if  self.algorithm is "1":
            self.q_table[state_index] = ((1 - self.learning_rate) * self.qvalue(state_index)) + (self.learning_rate * (reward + self.discount * future_val))

        if  self.algorithm is "2":
            future_state = future_states[0]
            self.q_table[state_index] = ((1 - self.learning_rate) * self.qvalue(state_index)) + (self.learning_rate * (reward + self.discount * future_val))

    def train(self, episodes, history=[]):
        """Trains by playing against self.
        Each episode is a full game
        """
        x = range(episodes)
        cumulative_reward = []
        memory = []

        total_reward = 0.0
        for i in range(episodes):
            episode_reward = 0.0
            game_active = True
            # Rest of game follows strategy
            j = 0
            while(game_active):
                print("\n****STEP " + str(j) + "****\n")
                winner, reward = self.step()
                j = j + 1
                episode_reward += reward
                if winner!=None:
                    game_active = False
                    self.game.reset()
            print("N steps: " + str(j))
            total_reward += episode_reward
            cumulative_reward.append(total_reward)
            memory.append(sys.getsizeof(self.q_table) / 1024)
            # Record total reward agent gains as training progresses
            if (i % (episodes / 10) == 0) and (i >= (episodes / 10)):
               print('.')
        history.append(x)
        history.append(cumulative_reward)
        history.append(memory)
        return history

    def save_values(self, path='data/qtable.json'):
        """Save Q values to json."""
        with open(path, 'w') as out:
            json.dump(self.q_table, out)

