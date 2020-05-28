# -*- coding: utf-8 -*-
"""
Created on Wed May 27 17:57:40 2020

@author: Maria Caldeira
"""


from foldingblocks import FoldingBlocks
from agent import Agent


def play():
        game = FoldingBlocks()
        agent = Agent(game)
        #agent.step()
        history = agent.train(10)
        print('After 2 Episodes')

        # agent.stats()

def main():
    play()


if __name__ == '__main__':
    main()