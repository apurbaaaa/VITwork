MAX = 100
NUM_STATES = 5
NUM_SYMBOLS = 4

# Action Table
action = [
    [2, 3, -1, -1],
    [-1, -1, -1, 0],
    [2, 3, -1, -1],
    [-2, -2, -2, -2],
    [-1, -1, -1, -1],
]

# Goto Table
goto_table = [
    [1],
    [-1],
    [4],
    [-1],
    [-1],
]

# Symbol Constants
C, D, B, DOLLAR = 0, 1, 2, 3

class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        if len(self.items) < MAX:
            self.items.append(item)
        else:
            print("Stack overflow")

    def pop(self):
        if self.items:
            return self.items.pop()
        else:
            print("Stack underflow")
            return -1

    def peek(self):
        if self.items:
            return self.items[-1]
        else:
            return -1

    def display(self):
        print("Stack:", self.items)

def print_parsing_table():
    print("Parsing Action Table:")
    print("State | c | d | b | $")
    print("---------------------")
    for i in range(NUM_STATES):
        print(f"{i:2d}", end="")
        for j in range(NUM_SYMBOLS):
            if action[i][j] == -1:
                print("   . ", end="")
            elif action[i][j] < 0:
                print(f" R{-action[i][j]} ", end="")
            else:
                print(f" S{action[i][j]} ", end="")
        print()

    print("\nParsing Goto Table:")
    print("State | A")
    print("-------------")
    for i in range(NUM_STATES):
        print(f"{i:2d}", end="")
        if goto_table[i][0] == -1:
            print("   . ")
        else:
            print(f" {goto_table[i][0]:2d} ")

def LALR_parser(input_string):
    s = Stack()
    s.push(0)
    i = 0

    while i < len(input_string):
        # Map the input characters to symbol codes (C, D, B, DOLLAR)
        symbol = C if input_string[i] == 'c' else D if input_string[i] == 'd' else B if input_string[i] == 'b' else DOLLAR
        state = s.peek()
        action_code = action[state][symbol]

        if action_code > 0:  # Shift operation
            print(f"Shift: {input_string[i]}")
            s.push(action_code)
            i += 1
        elif action_code < 0:  # Reduce operation
            prod = -action_code
            print("Reduce by ", end="")
            if prod == 1:
                print("S -> A b")
            elif prod == 2:
                print("A -> c A")
            elif prod == 3:
                print("A -> d")
            
            # Pop two elements (based on the production rules)
            s.pop()
            s.pop()
            # Push the goto state (if any)
            s.push(goto_table[s.peek()][0])
        elif action_code == 0:  # Accept input
            print("Input accepted.")
            return
        else:  # Error in parsing
            print(f"Error: Unexpected symbol {input_string[i]}")
            return

    s.display()
    if s.peek() == 0:
        print("Input accepted.")
    else:
        print("Input rejected.")

if __name__ == "__main__":
    print_parsing_table()
    input_string = input("Enter the input string (e.g., cd or cdcdb): ")
    input_string += "$"  # Append the dollar symbol
    LALR_parser(input_string)
