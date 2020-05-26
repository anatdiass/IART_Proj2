# from game.game import Game
import sys

# class FoldingBlocks(Game):
class FoldingBlocks():
    def __init__(self):
        self.width = 5
        self.height = 5
        self.board = [[" " for y in range(self.height)] for x in range(self.width)]
        self.blocks = []
        self.winner = None
        self.create()

    def reset(self):
        self.board = [[" " for y in range(self.height)] for x in range(self.width)]
        self.winner = None

    def create(self):
        for y in range(self.height):
            for x in range(self.width):
                self.board[x][y] = " "
                
        # LEVEL 1      
        self.width = 4
        self.height = 4
        self.board[0][3] = "R"
        self.define_blocks()

    def borderlines(self):
        string = "   ."
        for i in range(self.width):
            string += "_____."
        print(string)

    def x_indexes(self):
        print("\n ")
        string = ""
        for i in range(self.width):
            string += "     "
            string += str(i)
        print(string)

    def print_board(self):
        self.x_indexes()
        self.borderlines()
        for y in range(self.height):
            line = ""
            line += str(y)

            for x in range(self.width):
                if x < 10:
                    line += "  |  "
                else:
                    line += " |"
                line += str(self.board[x][y])
            line += "  |"
            print(line)
            self.borderlines()

    def get_color(self, x, y):
        if y >= 0 & x >= 0 & y <= self.height & x <= self.width:
            return self.board[x][y]
        else:
            return 0

    def set_piece(self, x, y, color):
        if 0 <= x < self.width and 0 <= y < self.height:
            self.board[x][y] = color

    def block_exists(self, index_char):
        for i in range(len(self.blocks)):
            for color in self.blocks[i]:
                if color == index_char:
                    return True
        return False

    def create_block(self, index_char):
        blocks = self.blocks
        positions = []
        for y in range(self.height):
            for x in range(self.width):
                cell_content = self.get_color(x, y)
                if cell_content == index_char:
                    pos = (x, y)
                    positions.append(pos)
        new_block = (index_char, positions)
        blocks.append(new_block)
        self.blocks = blocks

    @staticmethod
    def exist_position_block(positions, x, y):
        position = (x, y)
        for i in positions:
            if i == position:
                return True
        return False

    def update_block(self, index_char, x, y):
        for i in range(len(self.blocks)):
            for block in self.blocks[i]:
                if block[0] == index_char:
                    x_pos = x
                    pos = (x_pos, y)
                    block_positions = [x[1] for x in self.blocks if x[0] == index_char][0]
                    if not self.exist_position_block(block_positions, x_pos, y):
                        [x[1] for x in self.blocks if x[0] == index_char][0].append(pos)
                        print(str(self.blocks))

    def define_blocks(self):
        for y in range(self.height):
            for x in range(self.width):
                cell_content = self.get_color(x, y)
                if cell_content != ' ':
                    if not self.block_exists(cell_content):
                        self.create_block(cell_content)
                    else:
                        self.update_block(cell_content, x, y)

    def get_block(self, block_color):
        if self.block_exists(block_color):
            for i in range(len(self.blocks)):
                for color in self.blocks[i]:
                    if color == block_color:
                        return self.blocks[i]

    def get_blocks_colors(self):
        for i in range(len(self.blocks)):
            return [k[0] for k in self.blocks]

    @staticmethod
    def get_most_right_cell(positions):
        max_x = 0
        for pos in positions:
            if pos[0] > max_x:
                max_x = pos[0]
        return max_x

    @staticmethod
    def get_most_left_cell(positions):
        min_x = positions[0][0]
        for pos in positions:
            if pos[0] < min_x:
                min_x = pos[0]
        return min_x

    @staticmethod
    def get_most_up_cell(positions):
        min_y = positions[0][1]
        for pos in positions:
            if pos[1] < min_y:
                min_y = pos[1]
        return min_y

    @staticmethod
    def get_most_down_cell(positions):
        max_y = 0
        for pos in positions:
            if pos[1] > max_y:
                max_y = pos[1]
        return max_y

    def verify_reflexion_block_right(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])
        index_most_right_cell = self.get_most_right_cell(block[1])
        index_most_left_cell = self.get_most_left_cell(block[1])
        comp_between_cells = index_most_right_cell - index_most_left_cell

        if (index_most_left_cell + (2 * comp_between_cells) + 1) >= self.width:
            return False

        else:
            # Verify the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                piece_x = piece[0]
                dist_to_mrc = index_most_right_cell - piece_x
                delta_x = abs((2 * dist_to_mrc) + 1)
                destination_cell = self.get_color(piece_x + delta_x, piece[1])
                if destination_cell != ' ' or destination_cell == '-':
                    return False
        return True

    def verify_reflexion_block_left(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])
        index_most_right_cell = self.get_most_right_cell(block[1])
        index_most_left_cell = self.get_most_left_cell(block[1])

        comp_between_cells = index_most_right_cell - index_most_left_cell

        # verify if the reflexion is possible
        if (index_most_right_cell - (2 * comp_between_cells) + 1) < 0:
            return False
        else:
            # Verify the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                piece_x = piece[0]
                dist_to_mlc = piece_x - index_most_left_cell
                delta_x = abs((2 * dist_to_mlc) + 1)
                destination_cell = self.get_color(piece_x - delta_x, piece[1])
                if destination_cell != ' ' or destination_cell == '-' or (piece_x-delta_x)<0:
                    return False
        return True

    def verify_reflexion_block_up(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])

        index_most_down_cell = self.get_most_down_cell(block[1])
        index_most_up_cell = self.get_most_up_cell(block[1])
        height_between_cells = index_most_down_cell - index_most_up_cell

        # verify if the reflexion is possible
        if (index_most_down_cell - (2 * height_between_cells + 1)) < 0:
            return False
        else:
            # Verify if the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                piece_y = piece[1]
                dist_to_muc = piece_y - index_most_up_cell
                delta_y = (2 * dist_to_muc) + 1
                destination_cell = self.get_color(piece[0], piece_y - delta_y)
                if destination_cell != ' ' or destination_cell == '-' or (piece_y-delta_y)<0:
                    return False
        return True

    def verify_reflexion_block_down(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])

        index_most_down_cell = self.get_most_down_cell(block[1])
        index_most_up_cell = self.get_most_up_cell(block[1])
        height_between_cells = index_most_down_cell - index_most_up_cell

        # verify if the reflexion is possible
        if (index_most_up_cell + (2 * height_between_cells) + 1) >= self.height:
            return False
        else:
            # Verify if the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                piece_y = piece[1]
                dist_to_mdc = index_most_down_cell - piece_y
                delta_y = (2 * dist_to_mdc) + 1
                destination_cell = self.get_color(piece[0], piece_y + delta_y)
                if destination_cell != ' ' or destination_cell == '-':
                    return False
        return True

    def reflexion_block_right(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])
        index_most_right_cell = self.get_most_right_cell(block[1])

        for i in range(nr_pieces):
            piece = block[1][i]  # piece.first -> x, piece.second->y
            piece_x = piece[0]
            dist_to_mrc = index_most_right_cell - piece_x
            delta_x = (2 * dist_to_mrc) + 1
            self.set_piece(piece_x + delta_x, piece[1], piece_color)

    def reflexion_block_left(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])
        index_most_left_cell = self.get_most_left_cell(block[1])

        for i in range(nr_pieces):
            piece = block[1][i]  # piece.first -> x, piece.second->y
            piece_x = piece[0]
            dist_to_mlc = piece_x - index_most_left_cell
            delta_x = (2 * dist_to_mlc) + 1
            self.set_piece(piece_x - delta_x, piece[1], piece_color)

    def reflexion_block_up(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])

        index_most_up_cell = self.get_most_up_cell(block[1])

        for i in range(nr_pieces):
            piece = block[1][i]  # piece.first -> x, piece.second->y
            piece_y = piece[1]
            dist_to_muc = piece_y - index_most_up_cell
            delta_y = (2 * dist_to_muc) + 1
            self.set_piece(piece[0], piece_y - delta_y, piece_color)

    def reflexion_block_down(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])

        index_most_down_cell = self.get_most_down_cell(block[1])

        for i in range(nr_pieces):
            piece = block[1][i]  # piece.first -> x, piece.second->y
            piece_y = piece[1]
            dist_to_muc = index_most_down_cell - piece_y
            delta_y = (2 * dist_to_muc) + 1
            self.set_piece(piece[0], piece_y + delta_y, piece_color)

    def get_state(self, board):
        state = ""
        for y in range(self.height):
            for x in range(self.width):
                if board[x][y] == " ":
                    state += "-"
                else:
                    state += board[x][y]
        return state

    def get_block_next_valid_moves(self, color):
        valid_moves = []
        if self.verify_reflexion_block_right(color):
            valid_moves.append(1)
        if self.verify_reflexion_block_left(color):
            valid_moves.append(2)
        if self.verify_reflexion_block_down(color):
            valid_moves.append(3)
        if self.verify_reflexion_block_up(color):
            valid_moves.append(4)

        return valid_moves

    def get_next_valid_moves(self):
        valid_moves = []
        colors = self.get_blocks_colors()
        color_moves = []

        for color in colors:
            color_moves = self.get_block_next_valid_moves(color)

            if len(color_moves) > 0:
                color_pair = (color, color_moves)
                valid_moves.append(color_pair)

        return valid_moves

    def is_valid_move(self, color, move):
        all_moves = self.get_next_valid_moves()
        for i in range(len(all_moves)):
            for block_move in all_moves[i]:
                found = False
                if block_move[0] == color:
                    block_positions = [x[1] for x in all_moves if x[0] == color]
                    if move in block_positions[0]:
                        found = True
        
                if found == False:
                    return False
                else:
                    return True
        
        return False
    
    def make_move(self, color, move):
        if move == 1:
            if self.is_valid_move(color,move):
                self.reflexion_block_right(color)
        if move == 2:
            if self.is_valid_move(color,move):
                self.reflexion_block_left(color)
        if move == 3:
            if self.is_valid_move(color, move):
                self.reflexion_block_down(color)
        if move == 4:
            if self.is_valid_move(color, move):
                self.reflexion_block_up(color)
        
        self.define_blocks()

    def print_instructions(self):
        print('=======================================================\n'
            'How to play:\n\n'
            '--> Selection of the color (corresponding to block color)\n\n'
            '--> Possible moves:\n'
            '1 - Right reflexion\n'
            '2 - Left reflexion\n'
            '3 - Down reflexion\n'
            '4 - Up reflexion\n'
            '=======================================================\n') 

    def read_input(self):
        return int(sys.stdin.readline()[:-1])

    def read_color(self):
        return (sys.stdin.read(1))

fold = FoldingBlocks()

fold.print_instructions()

fold.print_board()
state = fold.get_state(fold.board)
# print("State: " + state)

next_moves = fold.get_next_valid_moves()
print("next moves: " + str(next_moves))

fold.make_move("R",1)
fold.print_board()
print("Color")
color = fold.read_color()
print("Color choosen:" + color)
print("Move: ")
move = fold.read_input()
fold.make_move("R", move)
fold.print_board()


# fold.make_move(3)
# state2 = fold.get_state(fold.board)
# print("State: " + state2)
# print("\n\nBOARD\n")
# fold.print_board()