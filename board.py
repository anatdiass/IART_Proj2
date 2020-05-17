class Board:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.board = [[" " for y in range(height)] for x in range(width)]
        self.blocks = []
        #     vector<pair<char,vector<pair<int,int>>>>blocks;

    def create(self):
        for y in range(self.height):
            for x in range(self.width):
                self.board[x][y] = " "

        self.board[0][0] = "c"
        self.board[4][4] = "f"
        self.board[2][2] = "f"

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
            for a in self.blocks[i]:
                if a == index_char:
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
                    # print("AQUI: " + str(x) + "/" + str(y))
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
            for a, positions in self.blocks[i]:
                if a == index_char:
                    pos = (x, y)
                    if not self.exist_position_block(positions, x, y):
                        cur_pos = positions
                        cur_pos.append(pos)
                        self.blocks[i] = (index_char, cur_pos)

    def define_blocks(self):
        for y in range(self.height):
            for x in range(self.width):
                cell_content = self.get_color(x, y)
                if cell_content != ' ':
                    if not self.block_exists(cell_content):
                        self.create_block(cell_content)
                    else:
                        self.update_block(cell_content, x, y)


board = Board(5, 5)
board.create()
board.define_blocks()

print("nr blocos: " + str(len(board.blocks)))

if board.block_exists("f"):
    print("sim")
if not board.block_exists("d"):
    print("nao")

board.show()
