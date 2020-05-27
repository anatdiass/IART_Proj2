# -*- coding: utf-8 -*-
"""
Created on Wed May 27 01:08:53 2020

@author: Maria Caldeira
"""
import numpy as np
import json
import sys

#class Agent(object):
class Agent():
    def __init__(self, game, q_table=dict(), player='X', learning_rate=5e-1, discount=9e-1, epsilon=5e-1):
        """Initialize agent with properties
        - qtable is json table with Q values Q(s,a)
        - game is reference to game being played
        - player is what player the agent is 'X' or 'O'
        - learning_rate is alpha value for gradient update
        - discount is discount factor for future expected rewards
        - epsilon is probability of exploration in epsilon greedy strategy
        """
        self.game = game
        self.q_table = q_table
        self.player = player
        self.learning_rate = learning_rate
        self.discount = discount
        self.epsilon = epsilon
        
    def qvalue(self, state):
        if state not in self.q_table:
            # Initialize Q-value at 0
            self.q_table[state] = 0.0
        return self.q_table[state]

    def argmax(self, values):
        """Returns index of max value."""
        vmax = np.max(values)
        max_indices = []
        for i, v in enumerate(values):
            if v == vmax:
                max_indices.append(i)
        return np.random.choice(max_indices)
