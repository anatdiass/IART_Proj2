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
        self.board[4][4] = "f"
        self.board[2][2] = "f"
        self.board[3][2] = "f"

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


board = Board(5, 5)
board.create()
board.define_blocks()

print("nr blocos: " + str(len(board.blocks)))

print("all blocks: ")
print(board.blocks)

test = board.get_block("f")
print("Bloco f: ")
print(test)

# EXPECTED : NONE
test2 = board.get_block("g")
print("Bloco g: ")
print(test2)

test3 = board.get_block("c")
print("Bloco c: ")
print(test3)

# EXPECTED : ['c','f']
all_colors = board.get_blocks_colors()
print("All colors: ")
print(all_colors)

board.show()
