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
        
    def getPieceColor(self,row,col):
        if row>=0 and col>=0 and row<self.width and col<self.height:
            return self.board[col][row];
        else: return "0"
        
    def getMostRightCell(self, positions):
        maxX = 0
        for pos in positions:
            if pos[0] > maxX:
                maxX=pos[0]
        return maxX
    
    
    def getMostLeftCell(self,positions):
        minX=positions[0][0]
        for pos in positions:
            if pos[0] < minX:
                minX=pos[0]
        return minX
        
    
    def verifyReflexionBlockRight(self,pieceColor):
        block = self.get_block(pieceColor)
        nrPieces = len(block[1])
        indexMostRightCell = self.getMostRightCell(block[1])
        indexMostLeftCell = self.getMostLeftCell(block[1]);
        compBetweenCells = indexMostRightCell-indexMostLeftCell
        
        if (indexMostLeftCell+(2*compBetweenCells)+1) >= self.height:
            print("No reflection")
            return False
        
        else:
            #Verify the destination pieces are available
            for i in range(nrPieces):
                piece = block[1][i]   #piece.first -> row, piece.second->col
                pieceColumn = piece[1]
                distToMRC = indexMostRightCell - pieceColumn
                deltaX = abs((2*distToMRC) + 1)
                destinationCell = self.getPieceColor(piece[0],pieceColumn+deltaX)
                if destinationCell != ' ' or destinationCell=='-':
                    print("no reflection")
                    return False
        print(" reflection")
        return True
    
        
        

board = Board(5, 5)
board.create()
board.define_blocks()

print("nr blocos: " + str(len(board.blocks)))

board.verifyReflexionBlockRight("c")

board.show()
