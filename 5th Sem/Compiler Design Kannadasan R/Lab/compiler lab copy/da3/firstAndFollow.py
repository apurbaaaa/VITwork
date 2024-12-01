productions = {}
firsts = {}
follows = {}

def find_first(symbol):
    # If symbol is a terminal, return it as the first set
    if not symbol.isupper():
        return {symbol}
    
    # If already computed, return cached result
    if firsts[symbol]:
        return firsts[symbol]
    
    first = set()
    
    # Iterate through each production for the given non-terminal symbol
    for production in productions[symbol]:
        if production == 'ε':
            first.add('ε')
        else:
            for char in production:
                first_of_char = find_first(char)
                first.update(first_of_char - {'ε'})
                if 'ε' not in first_of_char:
                    break
            else:
                first.add('ε')
    
    firsts[symbol] = first
    return first

def find_follow(symbol):
    # If follow is already computed, return it
    if follows[symbol]:
        return follows[symbol]
    
    follow = set()

    # Add $ to the follow of the start symbol
    if symbol == start_symbol:
        follow.add('$')

    # Iterate through the productions to compute the follow set
    for lhs, rhs_list in productions.items():
        for rhs in rhs_list:
            for i, char in enumerate(rhs):
                if char == symbol:
                    if i + 1 < len(rhs):
                        follow_of_next = find_first(rhs[i + 1])
                        follow.update(follow_of_next - {'ε'})
                        if 'ε' in follow_of_next:
                            follow.update(find_follow(lhs))
                    else:
                        if lhs != symbol:
                            follow.update(find_follow(lhs))

    follows[symbol] = follow
    return follow

def compute_firsts_and_follows():
    # Compute firsts and follows for each non-terminal
    for non_terminal in productions:
        find_first(non_terminal)
        find_follow(non_terminal)

# Input the number of productions
num_productions = int(input("Enter the number of productions: "))
for _ in range(num_productions):
    lhs, rhs = input("Enter production (A=BC|d): ").split('=')
    productions[lhs] = rhs.split('|')
    firsts[lhs] = set()
    follows[lhs] = set()

# Set the start symbol (usually the first non-terminal)
start_symbol = list(productions.keys())[0]

# Compute the first and follow sets
compute_firsts_and_follows()

# Output the computed first and follow sets
for non_terminal in productions:
    print(f"First({non_terminal}) = {{ {', '.join(sorted(firsts[non_terminal]))} }}")
    print(f"Follow({non_terminal}) = {{ {', '.join(sorted(follows[non_terminal]))} }}")
