# -*- coding: utf-8 -*-
"""
Created on Wed May 27 17:57:40 2020

@author: Maria Caldeira
"""

import sys
import matplotlib.pyplot as plt
import ujson as json


from foldingblocks import FoldingBlocks
from agent import Agent


def play(algorithm):
        game = FoldingBlocks()
        agent = Agent(game, algorithm)
        history = agent.train(1)
        print('After 1 Episodes')
"""
        rfig, raxs = plt.subplots(nrows=3, ncols=1)
        rax_reward1 = raxs[0]
        rax_reward1.grid()
        rax_reward2 = raxs[1]
        rax_reward2.grid()
        rax_reward3 = raxs[2]
        rax_reward3.grid()

        rax_reward1.plot(history[0][:100], history[1][:100])
        rax_reward1.set(ylabel='Cumulative Reward', title='Folding Blocks Cumulative Reward Episodes')

        rax_reward2.plot(history[0][:1000], history[1][:1000], color='g')
        rax_reward2.set(ylabel='Cumulative Reward')

        rax_reward3.plot(history[0][:10000], history[1][:10000], color='r')
        rax_reward3.set(xlabel='Episode', ylabel='Cumulative Reward')

        rfig.savefig('foldingblocks_reward.png')

        # Plot Qtable Memory Usage Stats
        memfig, memaxs = plt.subplots(nrows=3, ncols=1)
        memax_reward1 = memaxs[0]
        memax_reward1.grid()
        memax_reward2 = memaxs[1]
        memax_reward2.grid()
        memax_reward3 = memaxs[2]
        memax_reward3.grid()

        memax_reward1.plot(history[0][:100], history[2][:100])
        memax_reward1.set(ylabel='Size (KB)', title='Folding Blocks QTable Size Episodes')

        memax_reward2.plot(history[0][:1000], history[2][:1000], color='g')
        memax_reward2.set(ylabel='Size (KB)')

        memax_reward3.plot(history[0][:10000], history[2][:10000], color='r')
        memax_reward3.set(xlabel='Episode', ylabel='Size (KB)')

        memfig.savefig('foldingblocks_memory.png')
        plt.show()

        agent.save_values(path='data/foldingblocks_qtable.json')
"""
        # agent.stats()

def main():
        print("FOLDING BLOCKS")
        print("Choose an algoritm:")
        print("(1) Q-Learning")
        print("(2) Sarsa")
        alg = input()

        while(alg!="1" and alg!="2"):
                print("Choose again:")
                alg = input()
        
        play(alg)


if __name__ == '__main__':
    main()
