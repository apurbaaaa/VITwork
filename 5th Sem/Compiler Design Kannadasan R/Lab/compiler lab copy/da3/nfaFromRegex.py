def print_transition_table(q):
    print("\n\tTransition Table \n")
    print("_____________________________________\n")
    print("Current State |\tInput |\tNext State")
    print("\n_____________________________________\n")
    for i in range(len(q)):
        if q[i][0] != 0:
            print(f" q[{i}]\t\t| a\t| q[{q[i][0]}]")
        if q[i][1] != 0:
            print(f" q[{i}]\t\t| b\t| q[{q[i][1]}]")
        if q[i][2] != 0:
            if q[i][2] < 10:
                print(f" q[{i}]\t\t| e\t| q[{q[i][2]}]")
            else:
                print(f" q[{i}]\t\t| e\t| q[{q[i][2] // 10}] , q[{q[i][2] % 10}]")
    print("\n_____________________________________\n")

def convert_regex_to_dfa(regex):
    q = [[0, 0, 0] for _ in range(20)]
    j = 0
    i = 0
    len_reg = len(regex)
    
    while i < len_reg:
        if regex[i] == 'a' and (i + 1 >= len_reg or regex[i + 1] not in ['|', '*']):
            q[j][0] = j + 1
            j += 1
        elif regex[i] == 'b' and (i + 1 >= len_reg or regex[i + 1] not in ['|', '*']):
            q[j][1] = j + 1
            j += 1
        elif regex[i] == 'e' and (i + 1 >= len_reg or regex[i + 1] not in ['|', '*']):
            q[j][2] = j + 1
            j += 1
        elif regex[i] == 'a' and i + 2 < len_reg and regex[i + 1] == '|' and regex[i + 2] == 'b':
            q[j][2] = ((j + 1) * 10) + (j + 3)
            j += 1
            q[j][0] = j + 1
            j += 1
            q[j][2] = j + 3
            j += 1
            q[j][1] = j + 1
            j += 1
            q[j][2] = j + 1
            j += 1
            i += 2
        elif regex[i] == 'b' and i + 2 < len_reg and regex[i + 1] == '|' and regex[i + 2] == 'a':
            q[j][2] = ((j + 1) * 10) + (j + 3)
            j += 1
            q[j][1] = j + 1
            j += 1
            q[j][2] = j + 3
            j += 1
            q[j][0] = j + 1
            j += 1
            q[j][2] = j + 1
            j += 1
            i += 2
        elif regex[i] == 'a' and i + 1 < len_reg and regex[i + 1] == '*':
            q[j][2] = ((j + 1) * 10) + (j + 3)
            j += 1
            q[j][0] = j + 1
            j += 1
            q[j][2] = ((j + 1) * 10) + (j - 1)
            j += 1
        elif regex[i] == 'b' and i + 1 < len_reg and regex[i + 1] == '*':
            q[j][2] = ((j + 1) * 10) + (j + 3)
            j += 1
            q[j][1] = j + 1
            j += 1
            q[j][2] = ((j + 1) * 10) + (j - 1)
            j += 1
        elif regex[i] == ')' and i + 1 < len_reg and regex[i + 1] == '*':
            q[0][2] = ((j + 1) * 10) + 1
            q[j][2] = ((j + 1) * 10) + 1
            j += 1
        i += 1
    
    print(f"Given regular expression: {regex}")
    print_transition_table(q)

# Example usage
regex = "(a|b)*"
convert_regex_to_dfa(regex)
