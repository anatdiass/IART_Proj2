# -*- coding: utf-8 -*-
"""
Created on Wed May 27 01:08:53 2020

@author: Maria Caldeira
"""

import sys

#class Agent(object):
class Agent():
    """Agent is the reinforcement learning agent that learns optimal state action pairs."""
    def __init__(self, game, qtable=dict(), player='X', learning_rate=5e-1, discount=9e-1, epsilon=5e-1):
        """Initialize agent with properties
        - qtable is json table with Q values Q(s,a)
        - game is reference to game being played
        - player is what player the agent is 'X' or 'O'
        - learning_rate is alpha value for gradient update
        - discount is discount factor for future expected rewards
        - epsilon is probability of exploration in epsilon greedy strategy
        """
        self.game = game
        self.qtable = qtable
        self.player = player
        self.learning_rate = learning_rate
        self.discount = discount
        self.epsilon = epsilon
