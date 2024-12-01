a = "a*a/b"
stk = []
act = "SHIFT"

def check():
    global stk, a
    ac = "REDUCE TO E -> "
    
    # Rule 1: a -> E
    if len(stk) >= 1 and stk[-1] == 'a':
        print(f"${''.join(stk[:-1])}a\t{a}$\t{ac}a")
        stk[-1] = 'E'
        print(f"${''.join(stk)}\t{a}$")
    
    # Rule 2: b -> E
    if len(stk) >= 1 and stk[-1] == 'b':
        print(f"${''.join(stk[:-1])}b\t{a}$\t{ac}b")
        stk[-1] = 'E'
        print(f"${''.join(stk)}\t{a}$")
    
    # Rule 3: E + E -> E
    i = 0
    while i < len(stk) - 2:
        if stk[i] == 'E' and stk[i + 1] == '+' and stk[i + 2] == 'E':
            print(f"${''.join(stk[:i])}E+E{''.join(stk[i+3:])}\t{a}$\t{ac}E+E")
            stk[i] = 'E'
            del stk[i + 1:i + 3]
            print(f"${''.join(stk)}\t{a}$")
            i = max(i - 2, 0)
        else:
            i += 1
    
    # Rule 4: E * E -> E
    i = 0
    while i < len(stk) - 2:
        if stk[i] == 'E' and stk[i + 1] == '*' and stk[i + 2] == 'E':
            print(f"${''.join(stk[:i])}E*E{''.join(stk[i+3:])}\t{a}$\t{ac}E*E")
            stk[i] = 'E'
            del stk[i + 1:i + 3]
            print(f"${''.join(stk)}\t{a}$")
            i = max(i - 2, 0)
        else:
            i += 1
    
    # Rule 5: E / E -> E
    i = 0
    while i < len(stk) - 2:
        if stk[i] == 'E' and stk[i + 1] == '/' and stk[i + 2] == 'E':
            print(f"${''.join(stk[:i])}E/E{''.join(stk[i+3:])}\t{a}$\t{ac}E/E")
            stk[i] = 'E'
            del stk[i + 1:i + 3]
            print(f"${''.join(stk)}\t{a}$")
            i = max(i - 2, 0)
        else:
            i += 1

def main():
    global stk, a, act
    print("stack\tinput\taction")
    
    # Initial state
    print(f"${''.join(stk)}\t{a}$\t{act}")
    
    # Shift operations (Push input to stack)
    for char in a:
        stk.append(char)
        a = a[1:]
        print(f"${''.join(stk)}\t{a}$\t{act}")
        check()  # Check for reductions after each shift
    
    # Check the final acceptance/rejection
    check()  # Final check after all shifts
    if len(stk) == 1 and stk[0] == 'E':
        print(f"${''.join(stk)}\t{a}$\tAccept")
    else:
        print(f"${''.join(stk)}\t{a}$\tReject")

if __name__ == "__main__":
    main()
