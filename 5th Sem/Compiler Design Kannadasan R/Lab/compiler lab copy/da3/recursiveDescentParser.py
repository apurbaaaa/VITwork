SUCCESS = 1
FAILED = 0
cursor = 0
string = ""

def E():
    global cursor
    print(f"{string[cursor:]} E -> T E'")
    if T():
        if Edash():
            return SUCCESS
    return FAILED

def Edash():
    global cursor
    if cursor < len(string) and string[cursor] == '+':
        print(f"{string[cursor:]} E' -> + T E'")
        cursor += 1
        if T():
            if Edash():
                return SUCCESS
    else:
        print(f"{string[cursor:]} E' -> ε")
        return SUCCESS
    return FAILED

def T():
    global cursor
    print(f"{string[cursor:]} T -> F T'")
    if F():
        if Tdash():
            return SUCCESS
    return FAILED

def Tdash():
    global cursor
    if cursor < len(string) and string[cursor] == '*':
        print(f"{string[cursor:]} T' -> * F T'")
        cursor += 1
        if F():
            if Tdash():
                return SUCCESS
    else:
        print(f"{string[cursor:]} T' -> ε")
        return SUCCESS
    return FAILED

def F():
    global cursor
    if cursor < len(string) and string[cursor] == '(':
        print(f"{string[cursor:]} F -> ( E )")
        cursor += 1
        if E():
            if cursor < len(string) and string[cursor] == ')':
                cursor += 1
                return SUCCESS
    elif cursor < len(string) and string[cursor] == 'i':
        print(f"{string[cursor:]} F -> i")
        cursor += 1
        return SUCCESS
    return FAILED

if __name__ == "__main__":
    string = input("Enter the string: ")
    cursor = 0
    print("\nInput\t\tAction")
    print("--------------------------------")
    if E() and cursor == len(string):
        print("--------------------------------")
        print("String is successfully parsed")
    else:
        print("--------------------------------")
        print("Error in parsing String")
