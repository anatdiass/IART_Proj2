class Board:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.board = [[" " for y in range(height)] for x in range(width)]
        self.blocks = []

    def create(self):
        for y in range(self.height):
            for x in range(self.width):
                self.board[x][y] = " "
        # TODO -> tirar
        self.board[0][0] = "c"
        self.board[0][1] = "c"
        self.board[2][2] = "f"
        self.board[3][1] = "f"
        self.board[3][3] = "a"
        self.board[3][0] = "a"
        self.board[4][2] = "d"

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

    def show(self):
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
            for color in self.blocks[i]:
                if color == index_char:
                    pos = (x, y)
                    block_positions = [x[1] for x in self.blocks if x[0] == index_char]
                    if not self.exist_position_block(block_positions, x, y):
                        [x[1] for x in self.blocks if x[0] == index_char].append(pos)

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
        # print("indexMostRightCell:" + str(index_most_right_cell))
        index_most_left_cell = self.get_most_left_cell(block[1])
        # print("indexMostLeftCell:" + str(index_most_left_cell))
        comp_between_cells = index_most_right_cell - index_most_left_cell
        # print("width:" + str(self.width))
        if (index_most_left_cell + (2 * comp_between_cells) + 1) >= self.width:
            # print("No reflection")
            return False

        else:
            # Verify the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                # print("piece:" + str(piece))
                piece_x = piece[0]
                # print("pieceRow:" + str(piece_x))
                dist_to_mrc = index_most_right_cell - piece_x
                # print("distToMRC:" + str(dist_to_mrc))
                delta_x = abs((2 * dist_to_mrc) + 1)
                # print("deltaX:" + str(delta_x))
                destination_cell = self.get_color(piece_x + delta_x, piece[1])
                # print("destinationCell:" + str(destination_cell))
                if destination_cell != ' ' or destination_cell == '-':
                    # print("no reflection")
                    return False
        # print(" reflection")
        return True

    def verify_reflexion_block_left(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])
        index_most_right_cell = self.get_most_right_cell(block[1])
        index_most_left_cell = self.get_most_left_cell(block[1])
        comp_between_cells = index_most_right_cell - index_most_left_cell

        # verify if the reflexion is possible
        if (index_most_right_cell - (2 * comp_between_cells) + 1) < 0:
            # print("No reflection")
            return False
        else:
            # Verify the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                # print("piece:" + str(piece))
                piece_x = piece[0]
                # print("pieceRow:" + str(piece_x))
                dist_to_mlc = piece_x - index_most_left_cell
                # print("index_most_left_cell:" + str(index_most_left_cell))
                delta_x = abs((2 * dist_to_mlc) + 1)
                # print("delta_x:" + str(delta_x))
                # print("Cena:" + str(piece_x - delta_x))
                destination_cell = self.get_color(piece_x - delta_x, piece[1])
                if destination_cell != ' ' or destination_cell == '-':
                    # print("no reflection")
                    return False
        # print(" reflection")
        return True

    def verify_reflexion_block_up(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])

        index_most_down_cell = self.get_most_down_cell(block[1])
        index_most_up_cell = self.get_most_up_cell(block[1])
        height_between_cells = index_most_down_cell - index_most_up_cell

        # print("index_most_down_cell:" + str(index_most_down_cell))
        # print("index_most_up_cell:" + str(index_most_up_cell))

        # verify if the reflexion is possible
        if (index_most_down_cell - (2 * height_between_cells + 1)) < 0:
            # print("No reflection")
            return False
        else:
            # Verify if the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                # print("piece:" + str(piece))
                piece_y = piece[1]
                # print("piece_y:" + str(piece_y))
                dist_to_muc = piece_y - index_most_up_cell
                delta_y = (2 * dist_to_muc) + 1
                destination_cell = self.get_color(piece[0], piece_y - delta_y)
                if destination_cell != ' ' or destination_cell == '-':
                    # print("no reflection")
                    return False
        # print(" reflection")
        return True

    def verify_reflexion_block_down(self, piece_color):
        block = self.get_block(piece_color)
        nr_pieces = len(block[1])

        index_most_down_cell = self.get_most_down_cell(block[1])
        index_most_up_cell = self.get_most_up_cell(block[1])
        height_between_cells = index_most_down_cell - index_most_up_cell

        # print("index_most_down_cell:" + str(index_most_down_cell))
        # print("index_most_up_cell:" + str(index_most_up_cell))

        # verify if the reflexion is possible
        if (index_most_up_cell + (2 * height_between_cells) + 1) >= self.height:
            # print("No reflection")
            return False
        else:
            # Verify if the destination pieces are available
            for i in range(nr_pieces):
                piece = block[1][i]  # piece.first -> x, piece.second->y
                # print("piece:" + str(piece))
                piece_y = piece[1]
                # print("piece_y:" + str(piece_y))
                dist_to_mdc = index_most_down_cell - piece_y
                # print("dist_to_mdc:" + str(dist_to_mdc))
                delta_y = (2 * dist_to_mdc) + 1
                # print("delta_y:" + str(delta_y))
                destination_cell = self.get_color(piece[0], piece_y + delta_y)
                # print("destination_cell:" + str(destination_cell))
                if destination_cell != ' ' or destination_cell == '-':
                    # print("no reflection")
                    return False
        # print(" reflection")
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


board = Board(6, 5)
board.create()
board.define_blocks()

print("nr blocos: " + str(len(board.blocks)))
board.show()

if board.verify_reflexion_block_down("d"):
    board.reflexion_block_down("d")
if board.verify_reflexion_block_up("d"):
    board.reflexion_block_up("d")
if board.verify_reflexion_block_right("d"):
    board.reflexion_block_right("d")
if board.verify_reflexion_block_left("d"):
    board.reflexion_block_left("d")

if board.verify_reflexion_block_left("f"):
    board.reflexion_block_left("f")

board.show()