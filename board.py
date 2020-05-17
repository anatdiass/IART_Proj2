class Board:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.board = [[" " for y in range(height)] for x in range(width)]

    def create(self):
        for y in range(self.height):
            for x in range(self.width):
                self.board[x][y] = " "

        self.board[0][2] = "c"
        self.board[3][1] = "f"

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


board = Board(5, 5)
board.create()
board.show()
